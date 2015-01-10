#include "Services/eosOutput.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -En execucio
} eosOutputServiceState;

typedef struct __eosOutput {           // Dates d'una sortida
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    bool inverted;                     // -Senyal invertida
    unsigned tickCount;                // -Tics restant del puls
    eosOutputServiceHandle hService;   // -El servei al que pertany
    eosOutputHandle hNextOutput;       // -Seguent sortida
} eosOutput;

typedef struct __eosOutputService {    // Dades del servei
    eosOutputServiceState state;       // -Estat del servei
    eosOutputHandle hFirstOutput;      // -Primera sortida
} eosOutputService;


static void portInitialize(eosOutputHandle hOutput);
static bool portGet(eosOutputHandle hOutput);
static void portSet(eosOutputHandle hOutput, bool state);
static void portToggle(eosOutputHandle hOutput);


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           eosOutputServiceHandle eosOutputServiceInitialize(
 *               eosOutputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosOutputServiceHandle eosOutputServiceInitialize(
    eosOutputServiceParams *params) {

    eosOutputServiceHandle hService = (eosOutputServiceHandle) eosAlloc(sizeof(eosOutputService));
    if (hService == NULL)
        return NULL;

    hService->state = serviceInitializing;
    hService->hFirstOutput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosTickServiceHandle hTickService = params->hTickService;
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
 *               eosOutputServiceHandle hService)
 * 
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosOutputServiceTask(
    eosOutputServiceHandle hService) {

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
 *           void eosOutputServiceTick(
 *               eosOutputServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosOutputServiceTick(
    eosOutputServiceHandle hService) {

    if (hService->state == serviceRunning) {

        eosOutputHandle hOutput = hService->hFirstOutput;
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
 *           eosOutputHandle eosOutputsCreate(
 *               eosOutputServiceHandle hService,
 *               eosOutputParams *params)
 *
 *       Entrada:
 *           hService: El handler servei
 *           params  : Parametres d'inicialitzacio de la sortida
 *       Retorn:
 *           El handler de la sortida. NULL en cas d'error
 *
 *************************************************************************/

eosOutputHandle eosOutputCreate(
    eosOutputServiceHandle hService,
    eosOutputParams *params) {

    eosOutputHandle hOutput = (eosOutputHandle) eosAlloc(sizeof(eosOutput));
    if (hOutput == NULL)
        return NULL;

    hOutput->hService = hService;   
    hOutput->channel = params->channel;
    hOutput->position = params->position;
    hOutput->inverted = params->inverted;
    hOutput->tickCount = 0;

    bool intState = eosInterruptDisable();
    hOutput->hNextOutput = hService->hFirstOutput;
    hService->hFirstOutput = hOutput;
    eosInterruptRestore(intState);

    portInitialize(hOutput);

    return hOutput;
}


/*************************************************************************
 *
 *       Destrueix una sortida
 *
 *       Funcio:
 *           void eosOutputDestroy(
 *               eosOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void eosOutputDestroy(
    eosOutputHandle hOutput) {

}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           bool eosOutputsGet(
 *               eosOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

bool __attribute__ ((always_inline)) eosOutputGet(
    eosOutputHandle hOutput) {

    return portGet(hOutput);
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           void eosOutputsSet(
 *               eosOutputHandle hOutput,
 *               bool state)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           state  : L'estat a signar
 *
 *************************************************************************/

void __attribute__ ((always_inline)) eosOutputSet(
    eosOutputHandle hOutput,
    bool state) {

    portSet(hOutput, state);
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void eosOutputToggle(
 *               eosOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void __attribute__ ((always_inline)) eosOutputToggle(
    eosOutputHandle hOutput) {

    portToggle(hOutput);
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida
 *
 *       Funcio:
 *           void eosOutputsPulse(
 *               eosOutput hOutput,
 *               unsigned time)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           time   : Duracio del puls
 *
 *************************************************************************/

void eosOutputsPulse(
    eosOutputHandle hOutput,
    unsigned time) {

    bool intState = eosInterruptDisable();

    if (!hOutput->tickCount)
        portToggle(hOutput);
    hOutput->tickCount = time;

    eosInterruptRestore(intState);
}


/*************************************************************************
 *
 *       Inicialitza el port de sortida
 *
 *       Funcio:
 *           void portInitialize(
 *               eosOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

static void portInitialize(
    eosOutputHandle hOutput) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position, FALSE);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, hOutput->channel, hOutput->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port de sortida
 *
 *       Funcio:
 *           bool portGet(
 *               eosOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           Estat de la sortida
 *
 **************************************************************************/

static bool portGet(
    eosOutputHandle hOutput) {

    bool p = PLIB_PORTS_PinGetLatched(PORTS_ID_0, hOutput->channel, hOutput->position);
    return hOutput->inverted ? !p : p;
}


/*************************************************************************
 *
 *       Asigna l'estat del port de sortida
 *
 *       Funcio:
 *           void portSet(
 *               eosOutputHandle hOutput,
 *               bool state)
 *
 *       Entrada:
 *           hOutput: El handlerd e la sortida
 *           state  : L'estat a asignar
 *
 **************************************************************************/

static void portSet(
    eosOutputHandle hOutput,
    bool state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position,
        hOutput->inverted ? !state : state);
}


/*************************************************************************
 *
 *       Canvia l'estat del port d'entrada
 *
 *       Funcio:
 *           void portToggle(
 *               eosOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 **************************************************************************/

static void portToggle(
    eosOutputHandle hOutput) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->channel, hOutput->position);
}
