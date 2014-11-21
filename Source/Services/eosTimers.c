#define __EOS_TIMERS_INTERNAL
#include "Services/eosTimers.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"
#include "HardwareProfile.h"


typedef enum {                         // Codis d'operacio
    opCode_Pause,                      // -Posa un temporitzador en pausa
    opCode_Continue,                   // -Reanuda un temporitzador
    opCode_Reset,                      // -Reseteja un temporitzador
    opCode_Remove                      // -Elimina un temporitzador
} OpCodes;

typedef enum {                         // Estat del servei
    state_Initializing,                // -Inicialitzant
    state_Running                      // -Executant
} States;

// Indicadors del temporitzador
//
#define TF_PAUSED            0x0001    // Temporitzador en pausa
#define TF_TYPE              0x0006    // Tipus de temporitzador
#define TF_TYPE_CYCLIC       0x0002    // -Ciclic
#define TF_TYPE_AUTODESTROY  0x0003    // -Destruccio automatica


typedef struct {                       // Commanda
    OpCodes opCode;                    // -Codi d'operacio
    eosHTimer hTimer;                  // -Temporitzador al que aplicar la comanda
} Command;

typedef struct __eosTimer {            // Dades internes del temporitzador
    eosHTimerService hService;         // -Servei asociat
    unsigned flags;                    // -Indicadors
    unsigned timeout;                  // -Temps en ms
    unsigned counter;                  // -Contador de temps en ms
    eosCallback onTimeout;             // -Event TIMEOUT
    void *context;                     // -Parametre del events
    eosHTimer hNextTimer;              // -Seguent temporitzadorde la llista
} Timer;

typedef struct __eosTimerService {     // Dades internes del servei
    States state;                      // -Estat
    unsigned triggered;                // -Indica event del temporitzador
    eosHQueue hCommandQueue;           // -Cua de comandes
    eosHTimer hFirstTimer;             // -Primer temporitzador de la llista
} TimerService;


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerServiceInitialize(
 *               eosTimerServiceParams *params,
 *               eosTimerService *hService);
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Sortida:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           El resultat de l'operacio
 * 
 *************************************************************************/

eosResult eosTimerServiceInitialize(
    eosTimerServiceParams *params,
    eosHTimerService *_hService) {

    eosHTimerService hService = eosAlloc(sizeof(TimerService));
    if (hService == NULL)
        return eos_ERROR_ALLOC;
    
    // Inicialitza la cua de commandes
    //
    eosQueueParams queueParams;
    queueParams.itemSize = sizeof(Command);
    queueParams.maxItems = 10;
    if (eosQueueCreate(&queueParams, &hService->hCommandQueue) != eos_RESULT_SUCCESS) {
        eosFree(hService);
        return eos_ERROR_ALLOC;
    }

    // Inicialitza les estructures de dades
    //
    hService->state = state_Initializing;
    hService->triggered = 0;
    hService->hFirstTimer = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHTickService hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, (eosTickCallback) eosTimerServiceISRTick, (void*) hService);

    *_hService = hService;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTimerServiceTask(
 *               eosHTimerService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosTimerServiceTask(
    eosHTimerService hService) {

    switch (hService->state) {
        case state_Initializing:
            hService->state = state_Running;
            break;

        case state_Running: {

            // Obte el numero de tick pendents de procesar
            //
            BOOL intFlag = eosGetInterruptState();
            eosDisableInterrupts();
            unsigned triggered = hService->triggered;
            hService->triggered = 0;
            if (intFlag)
                eosEnableInterrupts();

            // Procesa els ticks pendents
            //
            if (triggered > 0) {

                eosHTimer hTimer = hService->hFirstTimer;
                while (hTimer) {
                    if ((hTimer->flags & TF_PAUSED) != TF_PAUSED) {

                        // Decrementa el contador
                        //
                        if (triggered > hTimer->counter)
                            hTimer->counter = 0;
                        else
                            hTimer->counter -= triggered;

                        // Si el contador arriba a zero...
                        //
                        if (hTimer->counter == 0) {

                            // Crida a la funcio callback
                            //
                            if (hTimer->onTimeout != NULL)
                                hTimer->onTimeout(hTimer, hTimer->context);

                            // Si es ciclc, reicicia el contador
                            //
                            if ((hTimer->flags & TF_TYPE) == TF_TYPE_CYCLIC)
                                hTimer->counter = hTimer->timeout;
                        }
                    }

                    hTimer = hTimer->hNextTimer;
                }
            }

            // Procesa les comandes pendents
            //
            Command command;
            while (eosQueueGet(hService->hCommandQueue, &command) == eos_RESULT_SUCCESS) {

                eosHTimer hTimer = command.hTimer;

                switch (command.opCode) {
                    case opCode_Pause:
                        hTimer->flags |= TF_PAUSED;
                        break;

                    case opCode_Continue:
                        hTimer->flags &= ~TF_PAUSED;
                        break;

                    case opCode_Reset:
                        hTimer->flags &= ~TF_PAUSED;
                        hTimer->counter = hTimer->timeout;
                        break;
                }
            }

            break;
        }
    }
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosTimerServiceISRTick(
 *               eosHTimerService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosTimerServiceISRTick(
    eosHTimerService hService) {

    hService->triggered += 1;
}


/*************************************************************************
 *
 *       Crea un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerCreate(
 *               eosHTimerService hService,
 *               eosTimerParams *params,
 *               eosHTimer *hTimer)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params : Parametres d'inicialitzacio
 *
 *       Sortida:
 *           hTimer: El handler del temporitzador
 *
 *       Retorm:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosTimerCreate(
    eosHTimerService hService,
    eosTimerParams *params,
    eosHTimer *_hTimer) {

    eosHTimer hTimer = eosAlloc(sizeof(Timer));
    if (hTimer == NULL)
        return eos_ERROR_ALLOC;

    hTimer->timeout = params->timeout;
    hTimer->counter = params->timeout;
    hTimer->onTimeout = params->onTimeout;
    hTimer->context = params->context;

    hTimer->hService = hService;
    hTimer->hNextTimer = hService->hFirstTimer;
    hService->hFirstTimer = hTimer;

    *_hTimer = hTimer;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerDestroy(
 *               eosHTimer hTimer)
 *
 *       Entrada:
 *           hTimer: El handler del temporitzador
 *
 *************************************************************************/

eosResult eosTimerDestroy(
    eosHTimer hTimer) {

    return eos_RESULT_SUCCESS;
}


eosResult eosTimerPause(
    eosHTimer hTimer) {

    Command command;
    command.opCode = opCode_Pause;
    command.hTimer = hTimer;
    eosQueuePut(hTimer->hService->hCommandQueue, &command);

    return eos_RESULT_SUCCESS;
}


eosResult eosTimerContinue(
    eosHTimer hTimer) {

    Command command;
    command.opCode = opCode_Continue;
    command.hTimer = hTimer;
    eosQueuePut(hTimer->hService->hCommandQueue, &command);

    return eos_RESULT_SUCCESS;
}


eosResult eosTimerReset(
    eosHTimer hTimer) {

    Command command;
    command.opCode = opCode_Reset;
    command.hTimer = hTimer;
    eosQueuePut(hTimer->hService->hCommandQueue, &command);

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Crea un temporitzador per gestionar un retard
 *
 *       Funcio:
 *           eosHTimer eosTimerDelayStart(
 *               eosHTimerService hService,
 *               unsigned timeout)
 *
 *       Entrada:
 *           service: El handler del servei
 *           timeout: Retard en ms
 *
 *       Retorn:
 *           El handler del temporitzador. NULL en cas d'error
 *
 *************************************************************************/

eosHTimer eosTimerDelayStart(
    eosHTimerService hService,
    unsigned timeout) {

    eosTimerParams params;
    params.timeout = timeout;
    params.type = TT_ONE_SHOT;
    params.onTimeout = NULL;
    params.context = NULL;

    eosHTimer hTimer;
    if (eosTimerCreate(hService, &params, &hTimer) == eos_RESULT_SUCCESS)
        return hTimer;
    else
        return NULL;
}


/*************************************************************************
 *
 *       Comprova si ha finalitzat el retard
 *
 *       Funcio:
 *           BOOL eosTimerDelayGetStatus(
 *               eosHTimer hTimer)
 *
 *       Entrada:
 *           hTimer: El handler del temporitzador
 *
 *       Retorn:
 *           TRUE si ha finalitzat el retard
 *
 *************************************************************************/

BOOL eosTimerDelayGetStatus(
    eosHTimer hTimer) {

    if (hTimer->counter == 0) {
        eosTimerDestroy(hTimer);
        return TRUE;
    }
    else
        return FALSE;
}
