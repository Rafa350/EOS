#include "eos.h"

#ifdef eosOPTIONS_UseDigOutputService

#include "Services/eosDigOutput.h"
#include "System/eosMemory.h"
#include "peripheral/ports/plib_ports.h"
#include "FreeRTOS.h"
#include "timers.h"


typedef struct __eosDigOutput {        // Dates d'una sortida
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;            // -Posicio
    bool inverted;                     // -Senyal invertida
    unsigned timeout;                  // -Contador de temps
    eosDigOutputServiceHandle hService;// -El servei al que pertany
    eosDigOutputHandle hNextOutput;    // -Seguent sortida
} eosDigOutput;

typedef struct __eosDigOutputService { // Dades del servei
    eosDigOutputHandle hFirstOutput;   // -Primera sortida
} eosDigOutputService;


static void timerCallback(TimerHandle_t rtosTimer);


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

    eosDigOutputServiceHandle hService = eosAlloc(sizeof(eosDigOutputService));
    if (hService != NULL) {
        hService->hFirstOutput = NULL;
    }
    
    return hService;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void task(
 *               void *param)
 *
 *       Entrada:
 *           param : Parametre (hService)
 *
 *************************************************************************/

static void task(void *param) {

    eosDigOutputServiceHandle hService = param;

    TRISDbits.TRISD2 = 0;
    while (true) {
        PORTDbits.RD2 = !LATDbits.LATD2;
        eosTaskDelay(300);
        eosTaskDelay(500);
        /*Command command;
        if (eosQueueGet(hService->hQueue, &command, 1000)) {
            eosDigOutputHandle hOutput = command.hTarget;
            switch (command.cmd) {
                case cmdCode_SET:
                    PLIB_PORTS_PinWrite(
                        PORTS_ID_0, 
                        hOutput->channel, 
                        hOutput->position, 
                        hOutput->inverted ? command.param1 : !command.param1);
                    break;
                    
                case cmdCode_TOGGLE:
                    PLIB_PORTS_PinToggle(
                        PORTS_ID_0, 
                        hOutput->channel, 
                        hOutput->position);
                    break;
                    
                case cmdCode_PULSE:
         
            }
        }*/
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
        hOutput->channel = params->channel;
        hOutput->position = params->position;
        hOutput->inverted = params->inverted;
        hOutput->timeout = 0;

        // Afegeis la sortida a la llista de sortides del servei
        //
        bool lock = eosTickServiceLock();
        hOutput->hNextOutput = hService->hFirstOutput;
        hService->hFirstOutput = hOutput;
        eosTickServiceUnlock(lock);

        // Inicialitza el port fisic a estat OFF
        //
        PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position, hOutput->inverted ? true : false);
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, hOutput->channel, hOutput->position);
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

    bool p = PLIB_PORTS_PinGet(PORTS_ID_0, hOutput->channel, hOutput->position);
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
    
    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position, 
        hOutput->inverted ? state : !state);
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

    PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->channel, hOutput->position);
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
 *       Notes:
 *           Si encara esta en un puls, unicament l'allarga
 *
 *************************************************************************/

void eosDigOutputsPulse(
    eosDigOutputHandle hOutput,
    unsigned time) {

    if (hOutput->timeout > 0)
        PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->channel, hOutput->position);
    hOutput->timeout = time;
}


static void timerCallback(TimerHandle_t rtosTimer) {
    
    eosDigOutputHandle hOutput = (eosDigOutputHandle) pvTimerGetTimerID(rtosTimer);
    if (hOutput->timeout > 0) {
        hOutput->timeout -= 1;
        if (hOutput->timeout == 0)
            PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->channel, hOutput->position);
    }
}


#endif
