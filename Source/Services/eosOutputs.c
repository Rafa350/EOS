#define __EOS_OUTPUTS_INTERNAL
#include "Services/eosOutputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    state_Initializing,                // -Inicialitzant
    state_Running                      // -En execucio
} States;

typedef struct __eosOutput {           // Dates d'una sortida
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Senyal invertida
    unsigned tickCount;                // -Tics restant del puls
    eosHOutputService hService;        // -El servei al que pertany
    eosHOutput hNextOutput;            // -Seguent sortida
} Output;

typedef struct __eosOutputService {    // Dades del servei
    States state;                      // -Estat del servei
    eosHOutput hFirstOutput;           // -Primera sortida
} OutputService;


// Definicions de funcions locals
//
static void portInitialize(eosHOutput hOutput);
static BOOL portGet(eosHOutput hOutput);
static void portSet(eosHOutput hOutput, BOOL state);
static void portToggle(eosHOutput hOutput);

#define MStoTICK(ms)    (ms)          // Converteix milisegons a ticks


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           eosResult eosOutputServiceInitialize(
 *               eosOutputServiceParams *params,
 *               eosUOutputService *service)
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

eosResult eosOutputServiceInitialize(
    eosOutputServiceParams *params,
    eosHOutputService *_hService) {

    eosHOutputService hService = eosAlloc(sizeof(OutputService));
    if (hService == NULL)
        return eos_ERROR_ALLOC;

    hService->state = state_Initializing;
    hService->hFirstOutput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHTickService hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, (eosCallback) eosOutputServiceISRTick, hService);
    
    *_hService = hService;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosOutputServiceTask(
 *               eosHOutputService hService)
 * 
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosOutputServiceTask(
    eosHOutputService hService) {

    switch (hService->state) {
        case state_Initializing:
            hService->state = state_Running;
            break;

        case state_Running:
            break;
    }
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosOutputServiceISRTick(
 *               eosHOutputService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosOutputServiceISRTick(
    eosHOutputService hService) {

    if (hService->state == state_Running) {
        eosHOutput hOutput = hService->hFirstOutput;
        while (hOutput) {
            if (hOutput->tickCount) {
                hOutput->tickCount -= 1;
                if (!hOutput->tickCount)
                    portToggle(hOutput);
            }
            hOutput = hOutput->hNextOutput;
        }
    }
}


/*************************************************************************
 *
 *       Crea una sortida
 *
 *       Funcio:
 *           eosResult eosOutputsCreate(
 *               eosHOutputService *hService,
 *               eosOutputParams *params,
 *               eosHOutput *hOutput)
 *
 *       Entrada:
 *           hService: El handler servei
 *           params  : Parametres d'inicialitzacio de la sortida
 *
 *       Sortida:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosOutputCreate(
    eosHOutputService hService,
    eosOutputParams *params,
    eosHOutput *_hOutput) {

    eosHOutput hOutput = eosAlloc(sizeof(Output));
    if (hOutput == NULL)
        return eos_ERROR_ALLOC;

    hOutput->channel = params->channel;
    hOutput->position = params->position;
    hOutput->inverted = params->inverted;
    hOutput->tickCount = 0;

    BOOL intFlag = eosGetInterruptState();
    eosDisableInterrupts();

    hOutput->hService = hService;
    hOutput->hNextOutput = hService->hFirstOutput;
    hService->hFirstOutput = hOutput;

    if (intFlag)
        eosEnableInterrupts();

    portInitialize(hOutput);

    *_hOutput = hOutput;
    
    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix una sortida
 *
 *       Funcio:
 *           eosResult eosOutputDestroy(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

eosResult eosOutputDestroy(
    eosHOutput hOutput) {

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputsGet(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

BOOL eosOutputGet(
    eosHOutput hOutput) {

    return portGet(hOutput);
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputsSet(
 *               eosHOutput hOutput,
 *               BOOL state)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           state  : L'estat a signar
 *
 *************************************************************************/

void eosOutputSet(
    eosHOutput hOutput,
    BOOL state) {

    portSet(hOutput, state);
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputToggle(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void eosOutputToggle(
    eosHOutput hOutput) {

    portToggle(hOutput);
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutputsPulse(
 *               eosHOutput hOutput,
 *               unsigned time)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           time   : Duracio del puls
 *
 *************************************************************************/

void eosOutputsPulse(
    eosHOutput hOutput,
    unsigned time) {

    BOOL intFlag = eosGetInterruptState();
    eosDisableInterrupts();
    if (!hOutput->tickCount)
        portToggle(hOutput);
    hOutput->tickCount = MStoTICK(time);
    if (intFlag)
        eosEnableInterrupts();
}


/*************************************************************************
 *
 *       Inicialitza el port de sortida
 *
 *       Funcio:
 *           void portInitialize(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

static void portInitialize(
    eosHOutput hOutput) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position, FALSE);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, hOutput->channel, hOutput->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port de sortida
 *
 *       Funcio:
 *           BOOL portGet(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           Estat de la sortida
 *
 **************************************************************************/

static BOOL portGet(
    eosHOutput hOutput) {

    BOOL p = PLIB_PORTS_PinGetLatched(PORTS_ID_0, hOutput->channel, hOutput->position);
    return hOutput->inverted ? !p : p;
}


/*************************************************************************
 *
 *       Asigna l'estat del port de sortida
 *
 *       Funcio:
 *           void portSet(
 *               eosHOutput hOutput,
 *               BOOL state)
 *
 *       Entrada:
 *           hOutput: El handlerd e la sortida
 *           state  : L'estat a asignar
 *
 **************************************************************************/

static void portSet(
    eosHOutput hOutput, BOOL state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position,
        hOutput->inverted ? !state : state);
}


/*************************************************************************
 *
 *       Canvia l'estat del port d'entrada
 *
 *       Funcio:
 *           void portToggle(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 **************************************************************************/

static void portToggle(
    eosHOutput hOutput) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->channel, hOutput->position);
}
