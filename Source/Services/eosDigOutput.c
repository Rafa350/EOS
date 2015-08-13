#include "Services/eosDigOutput.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "peripheral/ports/plib_ports.h"



typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -En execucio
} eosOutputServiceState;

typedef struct __eosDigOutput {        // Dates d'una sortida
    PORTS_CHANNEL port;                // -Port
    PORTS_BIT_POS pin;                 // -Pin
    bool inverted;                     // -Senyal invertida
    unsigned tickCount;                // -Tics restant del puls
    eosDigOutputServiceHandle hService;// -El servei al que pertany
    eosDigOutputHandle hNextOutput;    // -Seguent sortida
} eosDigOutput;

typedef struct __eosDigOutputService { // Dades del servei
    eosOutputServiceState state;       // -Estat del servei
    eosDigOutputHandle hFirstOutput;   // -Primera sortida
} eosDigOutputService;


static eosDigOutputServiceHandle __hService = NULL;


static eosDigOutputServiceHandle createDigOutputServiceHandle(void);
static eosDigOutputHandle createDigOutputHandle(void);
static void tickFunction(eosDigOutputServiceHandle hService);


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           eosDigOutputServiceHandle eosDigOutputServiceInitialize(
 *               eosOutputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosDigOutputServiceHandle eosDigOutputServiceInitialize(
    eosDigOutputServiceParams *params) {

    if (__hService == NULL) {
        eosDigOutputServiceHandle hService = eosAlloc(sizeof(eosDigOutputService));
        if (hService != NULL) {

            hService->state = serviceInitializing;
            hService->hFirstOutput = NULL;
            
            __hService = hService;
        }        
    }
    return __hService;
}


/************************************************************************
 *
 *       Comprova que el servei esta preparat i en funcionament
 *
 *       Funcio:
 *           bool eosDigOutputServiceIsReady(
 *               eosDigOutputServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           True si esta preparat. False en cas contrari
 * 
 ************************************************************************/

bool eosDigOutputServiceIsReady(
    eosDigOutputServiceHandle hService) {

    return hService->state != serviceInitializing;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosDigOutputServiceTask(
 *               eosDigOutputServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosDigOutputServiceTask(
    eosDigOutputServiceHandle hService) {

    switch (hService->state) {

        case serviceInitializing:
            hService->state = serviceRunning;
            eosTickRegisterCallback(NULL, (eosTickCallback) tickFunction, hService);
            break;

        case serviceRunning:
            break;
    }
}


/*************************************************************************
 *
 *       Crea una sortida
 *
 *       Funcio:
 *           eosDigOutputHandle eosDigOutputsCreate(
 *               eosDigOutputServiceHandle hService,
 *               eosOutputParams *params)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           params  : Parametres d'inicialitzacio de la sortida
 *
 *       Retorn:
 *           El handler de la sortida. NULL en cas d'error
 *
 *************************************************************************/

eosDigOutputHandle eosDigOutputCreate(
    eosDigOutputServiceHandle hService,
    eosDigOutputParams *params) {

    // Crea el bloc de memoria
    //
    eosDigOutputHandle hOutput = eosAlloc(sizeof(eosDigOutput));
    if (hOutput != NULL) {

        // Inicialitza les dades internes de la sortida
        //
        hOutput->hService = hService;   
        hOutput->port = (PORTS_CHANNEL) params->port;
        hOutput->pin = (PORTS_BIT_POS) params->pin;
        hOutput->inverted = params->inverted;
        hOutput->tickCount = 0;

        // Afegeis la sortida a la llista de sortides del servei
        //
        bool intState = eosInterruptDisable();
        hOutput->hNextOutput = hService->hFirstOutput;
        hService->hFirstOutput = hOutput;
        eosInterruptRestore(intState);

        // Inicialitza el port fisic a estat OFF
        //
        PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->port, hOutput->pin, hOutput->inverted ? true : false);
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, hOutput->port, hOutput->pin);
    }
    
    return hOutput;
}


/*************************************************************************
 *
 *       Destrueix una sortida
 *
 *       Funcio:
 *           void eosDigOutputDestroy(
 *               eosDigOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void eosDigOutputDestroy(
    eosDigOutputHandle hOutput) {

}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           bool eosDigOutputsGet(
 *               eosDigOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

bool eosDigOutputGet(
    eosDigOutputHandle hOutput) {

    bool p = PLIB_PORTS_PinGet(PORTS_ID_0, hOutput->port, hOutput->pin);
    return hOutput->inverted ? !p : p;
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           void eosDigOutputsSet(
 *               eosDigOutputHandle hOutput,
 *               bool state)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           state  : L'estat a signar
 *
 *************************************************************************/

void eosDigOutputSet(
    eosDigOutputHandle hOutput,
    bool state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->port, hOutput->pin,
        hOutput->inverted ? !state : state);
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void eosDigOutputToggle(
 *               eosDigOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void eosDigOutputToggle(
    eosDigOutputHandle hOutput) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->port, hOutput->pin);    
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida
 *
 *       Funcio:
 *           void eosDigOutputsPulse(
 *               eosDigOutput hOutput,
 *               unsigned time)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           time   : Duracio del puls
 *
 *************************************************************************/

void eosDigOutputsPulse(
    eosDigOutputHandle hOutput,
    unsigned time) {

    if (time > 0) {
        bool intState = eosInterruptDisable();
        if (!hOutput->tickCount)
            PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->port, hOutput->pin);    
        hOutput->tickCount = time;
        eosInterruptRestore(intState);
    }
}


static eosDigOutputServiceHandle createDigOutputServiceHandle(void) {
    
    return (eosDigOutputServiceHandle) eosAlloc(sizeof(eosDigOutputService));
}


static eosDigOutputHandle createDigOutputHandle(void) {
    
    return (eosDigOutputHandle) eosAlloc(sizeof(eosDigOutput));
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void tickFunction(
 *               eosDigOutputServiceHandle *hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

static void tickFunction(
    eosDigOutputServiceHandle hService) {

    eosDigOutputHandle hOutput = hService->hFirstOutput;
    while (hOutput) {
        if (hOutput->tickCount) {
            hOutput->tickCount -= 1;
            if (!hOutput->tickCount)
                PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->port, hOutput->pin);    
        }
        hOutput = hOutput->hNextOutput;
    }
}
