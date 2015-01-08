#include "Services/eosOutputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -En execucio
} ServiceStates;

typedef struct __eosOutput {           // Dates d'una sortida
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    bool inverted;                     // -Senyal invertida
    unsigned tickCount;                // -Tics restant del puls
    eosHOutputService hService;        // -El servei al que pertany
    eosHOutput hNextOutput;            // -Seguent sortida
} Output;

typedef struct __eosOutputService {    // Dades del servei
    ServiceStates state;               // -Estat del servei
    eosHOutput hFirstOutput;           // -Primera sortida
} OutputService;


// Funcions d'acces al hardware
//
static void halPortInitialize(eosHOutput hOutput);
static bool halPortGet(eosHOutput hOutput);
static void halPortSet(eosHOutput hOutput, bool state);
static void halPortToggle(eosHOutput hOutput);

#define MStoTICK(ms)    (ms)          // Converteix milisegons a ticks



/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           eosHPOutputService eosOutputServiceInitialize(
 *               eosOutputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosHOutputService eosOutputServiceInitialize(
    eosOutputServiceParams *params) {

    eosHOutputService hService = (eosHOutputService) eosAlloc(sizeof(OutputService));
    if (hService == NULL)
        return NULL;

    hService->state = serviceInitializing;
    hService->hFirstOutput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHTickService hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, (eosTickCallback) eosOutputServiceTick, hService);

    return hService;
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
        case serviceInitializing:
            hService->state = serviceRunning;
            break;

        case serviceRunning:
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

void eosOutputServiceTick(
    eosHOutputService hService) {

    if (hService->state == serviceRunning) {

        eosHOutput hOutput = hService->hFirstOutput;
        while (hOutput) {

            if (hOutput->tickCount) {
                hOutput->tickCount -= 1;
                if (!hOutput->tickCount)
                    halPortToggle(hOutput);
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
 *           eosHOutput eosOutputsCreate(
 *               eosHOutputService *hService,
 *               eosOutputParams *params)
 *
 *       Entrada:
 *           hService: El handler servei
 *           params  : Parametres d'inicialitzacio de la sortida
 *       Retorn:
 *           El handler de la sortida. NULL en cas d'error
 *
 *************************************************************************/

eosHOutput eosOutputCreate(
    eosHOutputService hService,
    eosOutputParams *params) {

    eosHOutput hOutput = (eosHOutput) eosAlloc(sizeof(Output));
    if (hOutput == NULL)
        return NULL;

    hOutput->hService = hService;   
    hOutput->channel = params->channel;
    hOutput->position = params->position;
    hOutput->inverted = params->inverted;
    hOutput->tickCount = 0;

    bool intFlag = eosGetInterruptState();
    eosDisableInterrupts();

    hOutput->hNextOutput = hService->hFirstOutput;
    hService->hFirstOutput = hOutput;

    if (intFlag)
        eosEnableInterrupts();

    halPortInitialize(hOutput);

    return hOutput;
}


/*************************************************************************
 *
 *       Destrueix una sortida
 *
 *       Funcio:
 *           void eosOutputDestroy(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void eosOutputDestroy(
    eosHOutput hOutput) {

}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           bool eosOutputsGet(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

bool eosOutputGet(
    eosHOutput hOutput) {

    return halPortGet(hOutput);
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           void eosOutputsSet(
 *               eosHOutput hOutput,
 *               bool state)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           state  : L'estat a signar
 *
 *************************************************************************/

void eosOutputSet(
    eosHOutput hOutput,
    bool state) {

    halPortSet(hOutput, state);
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void eosOutputToggle(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void eosOutputToggle(
    eosHOutput hOutput) {

    halPortToggle(hOutput);
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida
 *
 *       Funcio:
 *           void eosOutputsPulse(
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
        halPortToggle(hOutput);
    hOutput->tickCount = MStoTICK(time);

    if (intFlag)
        eosEnableInterrupts();
}


/*************************************************************************
 *
 *       Inicialitza el port de sortida
 *
 *       Funcio:
 *           void halPortInitialize(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

static void halPortInitialize(
    eosHOutput hOutput) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position, FALSE);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, hOutput->channel, hOutput->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port de sortida
 *
 *       Funcio:
 *           bool halPortGet(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           Estat de la sortida
 *
 **************************************************************************/

static bool halPortGet(
    eosHOutput hOutput) {

    bool p = PLIB_PORTS_PinGetLatched(PORTS_ID_0, hOutput->channel, hOutput->position);
    return hOutput->inverted ? !p : p;
}


/*************************************************************************
 *
 *       Asigna l'estat del port de sortida
 *
 *       Funcio:
 *           void halPortSet(
 *               eosHOutput hOutput,
 *               bool state)
 *
 *       Entrada:
 *           hOutput: El handlerd e la sortida
 *           state  : L'estat a asignar
 *
 **************************************************************************/

static void halPortSet(
    eosHOutput hOutput,
    bool state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position,
        hOutput->inverted ? !state : state);
}


/*************************************************************************
 *
 *       Canvia l'estat del port d'entrada
 *
 *       Funcio:
 *           void halPortToggle(
 *               eosHOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 **************************************************************************/

static void halPortToggle(
    eosHOutput hOutput) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->channel, hOutput->position);
}
