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


static eosOutputServiceHandle hService = NULL;

static void tickFunction(void *context);
static void portInitialize(eosOutputHandle hOutput);
static bool portGet(eosOutputHandle hOutput);
static void portSet(eosOutputHandle hOutput, bool state);
static void portToggle(eosOutputHandle hOutput);


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           bool eosOutputServiceInitialize(
 *               eosOutputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           True si tot es correcte
 *
 *************************************************************************/

bool eosOutputServiceInitialize(
    eosOutputServiceParams *params) {

    // Comprova si ja esta inicialitzat
    //
    if (hService)
        return false;

    hService = eosAlloc(sizeof(eosOutputService));
    if (!hService)
        return false;

    // Inicialitza les dades internes del servei
    //
    hService->state = serviceInitializing;
    hService->hFirstOutput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosTickAttachFunction((eosTickCallback) tickFunction, NULL);

    return true;
}


bool __attribute__ ((always_inline)) eosOutputServiceIsReady(void) {

    return hService && (hService->state != serviceInitializing);
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosOutputServiceTask(void)
 *
 *************************************************************************/

void eosOutputServiceTask(void) {

    if (hService) {

        switch (hService->state) {

            case serviceInitializing:
                hService->state = serviceRunning;
                break;

            case serviceRunning:
                break;
        }
    }
}


/*************************************************************************
 *
 *       Crea una sortida
 *
 *       Funcio:
 *           eosOutputHandle eosOutputsCreate(
 *               eosOutputParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio de la sortida
 *
 *       Retorn:
 *           El handler de la sortida. NULL en cas d'error
 *
 *************************************************************************/

eosOutputHandle eosOutputCreate(
    eosOutputParams *params) {

    // Comprova que el servei estiqui inicialitzat
    //
    if (!hService)
        return NULL;

    // Crea el bloc de memoria
    //
    eosOutputHandle hOutput = eosAlloc(sizeof(eosOutput));
    if (hOutput == NULL)
        return NULL;

    // Inicialitza les dades internes de la sortida
    //
    hOutput->hService = hService;   
    hOutput->channel = params->channel;
    hOutput->position = params->position;
    hOutput->inverted = params->inverted;
    hOutput->tickCount = 0;

    // Afegeis la sortida a la llista de sortides del servei
    //
    bool intState = eosInterruptDisable();
    hOutput->hNextOutput = hService->hFirstOutput;
    hService->hFirstOutput = hOutput;
    eosInterruptRestore(intState);

    // Inicialitza el ort fisic
    //
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

    if (hOutput)
        return portGet(hOutput);
    else
        return false;
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

    if (hOutput)
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

    if (hOutput)
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

    if (hOutput && (time > 0)) {
        bool intState = eosInterruptDisable();
        if (!hOutput->tickCount)
            portToggle(hOutput);
        hOutput->tickCount = time;
        eosInterruptRestore(intState);
    }
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void tickFunction(
 *               void *context)
 *
 *       Entrada:
 *           context: En aquest cas NULL
 *
 *************************************************************************/

static void tickFunction(
    void *context) {

    if (hService && (hService->state == serviceRunning)) {

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
