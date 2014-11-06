#define __EOS_OUTPUTS_INTERNAL
#include "Services/eosOutputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


// Estats del servei
//
#define SS_INITIALIZING    0           // Inicialitzant
#define SS_RUNNING         1           // En execucio


struct __eosOutput {                   // Dates d'una sortida
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Senyal invertida;
    unsigned time;                     // -Temps restant del puls
    struct __eosOutputService *service;// -El servei al que pertany
    struct __eosOutput *nextOutput;    // -Seguent sortida
};

struct __eosOutputService {            // Dades del servei
    unsigned state;                    // -Estat del servei
    struct __eosOutput *firstOutput;   // -Llista de sortides
};


// Definicions de funcions locals
//
static void portInitialize(eosOutput output);
static BOOL portGet(eosOutput output);
static void portSet(eosOutput output, BOOL state);
static void portToggle(eosOutput output);


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           eosResult eosOutputServiceInitialize(
 *               eosOutputServiceParams *params,
 *               eosOutputService *service)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Sortida:
 *           service: El handler del servei
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosOutputServiceInitialize(eosOutputServiceParams *params, eosOutputService *_service) {

    eosOutputService service = eosAlloc(sizeof(struct __eosOutputService));
    if (service == NULL)
        return eos_ERROR_ALLOC;

    service->state = SS_INITIALIZING;
    service->firstOutput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosTickService tickService = params->tickService;
    if (tickService == NULL)
        tickService = eosGetTickServiceHandle();
    if (tickService != NULL)
        eosTickAttach(tickService, (eosCallback) eosOutputServiceISRTick, service);
    
    *_service = service;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosOutputServiceTask(
 *               eosOutputService service)
 * 
 *       Entrada:
 *           service: El handler del servei
 *
 *************************************************************************/

void eosOutputServiceTask(eosOutputService service) {

    switch (service->state) {
        case SS_INITIALIZING:
            service->state = SS_RUNNING;
            break;

        case SS_RUNNING:
            break;
    }
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosOutputServiceISRTick(
 *               eosOutputService service)
 *
 *       Entrada:
 *           service: El handler del servei
 *
 *************************************************************************/

void eosOutputServiceISRTick(eosOutputService service) {

    if (service->state == SS_RUNNING) {
        eosOutput output = service->firstOutput;
        while (output) {
            if (output->time) {
                output->time -= 1;
                if (!output->time)
                    portToggle(output);
            }
            output = output->nextOutput;
        }
    }
}


/*************************************************************************
 *
 *       Crea una sortida
 *
 *       Funcio:
 *           eosResult eosOutputsCreate(
 *               eosOutputService *service,
 *               eosOutputParams *params,
 *               eosOutput *output)
 *
 *       Entrada:
 *           service: El handler servei
 *           params : Parametres d'inicialitzacio de la sortida
 *
 *       Sortida:
 *           El handler de la sortida
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosOutputCreate(eosOutputService service, eosOutputParams *params, eosOutput *_output) {

    eosOutput output = eosAlloc(sizeof(struct __eosOutput));
    if (output == NULL)
        return eos_ERROR_ALLOC;

    output->channel = params->channel;
    output->position = params->position;
    output->inverted = params->inverted;
    output->time = 0;

    BOOL intFlag = eosGetInterruptState();
    eosDisableInterrupts();

    output->service = service;
    output->nextOutput = service->firstOutput;
    service->firstOutput = output;

    if (intFlag)
        eosEnableInterrupts();

    portInitialize(output);

    *_output = output;
    
    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix una sortida
 *
 *       Funcio:
 *           eosResult eosOutputDestroy(
 *               eosOutput output)
 *
 *       Entrada:
 *           output: El handler de la sortida
 *
 *************************************************************************/

eosResult eosOutputDestroy(eosOutput output) {

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputsGet(
 *               eosOutput output)
 *
 *       Entrada:
 *           output: El handler de la sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

BOOL eosOutputGet(eosOutput output) {

    return portGet(output);
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputsSet(
 *               eosOutput output,
 *               BOOL state)
 *
 *       Entrada:
 *           output: El handler de la sortida
 *           state : L'estat a signar
 *
 *************************************************************************/

void eosOutputSet(eosOutput output, BOOL state) {

    portSet(output, state);
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputToggle(
 *               eosOutput output)
 *
 *       Entrada:
 *           output: El handler de la sortida
 *
 *************************************************************************/

void eosOutputToggle(eosOutput output) {

    portToggle(output);
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputsPulse(
 *               eosOutput output,
 *               unsigned time)
 *
 *       Entrada:
 *           output: El handler de la sortida
 *           time  : Duracio del puls
 *
 *************************************************************************/

void eosOutputsPulse(eosOutput output, unsigned time) {

    BOOL intFlag = eosGetInterruptState();
    eosDisableInterrupts();
    if (!output->time)
        portToggle(output);
    output->time = time;
    if (intFlag)
        eosEnableInterrupts();
}


/*************************************************************************
 *
 *       Inicialitza el port de sortida
 *
 *       Funcio:
 *           void portInitialize(
 *               eosOutput output)
 *
 *       Entrada:
 *           output : El handler de la sortida
 *
 *************************************************************************/

static void portInitialize(eosOutput output) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, output->channel, output->position, FALSE);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, output->channel, output->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port de sortida
 *
 *       Funcio:
 *           BOOL portGet(
 *               eosOutput output)
 *
 *       Entrada:
 *           output: El handlerd e la sortida
 *
 *       Retorn:
 *           Estat de la sortida
 *
 **************************************************************************/

static BOOL portGet(eosOutput output) {

    BOOL p = PLIB_PORTS_PinGetLatched(PORTS_ID_0, output->channel, output->position);
    return output->inverted ? !p : p;
}


/*************************************************************************
 *
 *       Asigna l'estat del port de sortida
 *
 *       Funcio:
 *           void portSet(
 *               eosOutput output,
 *               BOOL state)
 *
 *       Entrada:
 *           output: El handlerd e la sortida
 *           state : L'estat a asignar
 *
 **************************************************************************/

static void portSet(eosOutput output, BOOL state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, output->channel, output->position,
        output->inverted ? !state : state);
}


/*************************************************************************
 *
 *       Canvia l'estat del port d'entrada
 *
 *       Funcio:
 *           void portToggle(
 *               eosOutput output)
 *
 *       Entrada:
 *           output: El handler de la sortida
 *
 **************************************************************************/

static void portToggle(eosOutput output) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, output->channel, output->position);
}
