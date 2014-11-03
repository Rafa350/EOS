#include "Services/__eosOutputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


static void portInitialize(eosOutput* output);
static BOOL portGet(eosOutput* output);
static void portSet(eosOutput* output, BOOL state);
static void portToggle(eosOutput* output);


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           eosOutputService* eosOutputServiceInitialize(
 *               eosOutputServiceParams *params)
 *
 *       Entrada:
 *           params : Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El servei creat. NULL en cas d'error
 *
 *************************************************************************/

eosOutputService* eosOutputServiceInitialize(eosOutputServiceParams *params) {

    eosOutputService* service = eosAlloc(sizeof(eosOutputService));
    if (service) {

        service->state = SS_INITIALIZING;
        service->firstOutput = NULL;

        // Asigna la funcio d'interrupcio TICK
        //
        eosTickService* tickService = params->tickService;
        if (tickService == NULL)
            tickService = eosGetTickServiceHandle();
        if (tickService != NULL)
            eosTickAttach(tickService, (eosCallback) eosOutputServiceISRTick, (void*) service);
    }
    
    return service;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosOutputServiceTask(
 *               eosOutputService* service)
 * 
 *       Entrada:
 *           service : El servei a procesar
 *
 *************************************************************************/

void eosOutputServiceTask(eosOutputService* service) {

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
 *               void *service)
 *
 *       Entrada:
 *           service: El servei a procesar
 *
 *************************************************************************/

void eosOutputServiceISRTick(eosOutputService *service) {

    if (service->state == SS_RUNNING) {
        eosOutput *output = service->firstOutput;
        while (output) {
            if (output->active && output->time) {
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
 *               eosOutputParams *params)
 *
 *       Entrada:
 *           service : El servei
 *           params  : Parametres d'inicialitzacio de la sortida
 *
 *       Retorn:
 *           La sortida creada, NULL en cas d'error
 *
 *************************************************************************/

eosOutput* eosOutputCreate(eosOutputService *service, eosOutputParams *params) {

    eosOutput *output = eosAlloc(sizeof(eosOutput));
    if (output) {
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
    }

    return output;
}


/*************************************************************************
 *
 *       Destrueix una sortida
 *
 *       Funcio:
 *           void eosOutputDestroy(
 *               eosOutput* output)
 *
 *       Entrada:
 *           output     : La sortida a destruir
 *
 *************************************************************************/

void eosOutputDestroy(eosOutput* output) {

}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputsGet(
 *               eosOutput* output)
 *
 *       Entrada:
 *           output : La sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

BOOL eosOutputsGet(eosOutput* output) {

    return portGet(output);
}


void eosOutputsSet(eosOutput* output, BOOL state) {

    portSet(output, state);
}


void eosOutputsToggle(eosOutput* output) {

    portToggle(output);
}


void eosOutputsPulse(eosOutput* output, unsigned time) {

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
 *               eosOutput* output)
 *
 *       Entrada:
 *           output : El port
 *
 *************************************************************************/

static void portInitialize(eosOutput* output) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, output->channel, output->position, FALSE);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, output->channel, output->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port de sortida
 *
 *       Funcio:
 *           BOOL portGet(
 *               eosOutput* output)
 *
 *       Entrada:
 *           output : El port
 *
 *       Retorn:
 *           Estat de la sortida
 *
 **************************************************************************/

static BOOL portGet(eosOutput* output) {

    BOOL p = PLIB_PORTS_PinGetLatched(PORTS_ID_0, output->channel, output->position);
    return output->inverted ? !p : p;
}


/*************************************************************************
 *
 *       Asigna l'estat del port de sortida
 *
 *       Funcio:
 *           void portSet(
 *               eosOutput* output,
 *               BOOL state)
 *
 *       Entrada:
 *           output : El port
 *           state  : L'estat a asignar
 *
 **************************************************************************/

static void portSet(eosOutput* output, BOOL state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, output->channel, output->position,
        output->inverted ? !state : state);
}


/*************************************************************************
 *
 *       Canvia l'estat del port d'entrada
 *
 *       Funcio:
 *           void portToggle(
 *               eosOutput* output)
 *
 *       Entrada:
 *           output : El port
 *
 **************************************************************************/

static void portToggle(eosOutput* output) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, output->channel, output->position);
}
