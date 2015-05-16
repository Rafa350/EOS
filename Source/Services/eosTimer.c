#include "Services/eosTimer.h"
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
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -Executant
} eosTimerServiceState;

// Indicadors del temporitzador
//
#define TF_PAUSED            0x0001    // Temporitzador en pausa
#define TF_TYPE              0x0006    // Tipus de temporitzador
#define TF_TYPE_CYCLIC       0x0002    // -Ciclic
#define TF_TYPE_AUTODESTROY  0x0003    // -Destruccio automatica


typedef struct {                       // Commanda
    OpCodes opCode;                    // -Codi d'operacio
    eosTimerHandle hTimer;             // -Temporitzador al que aplicar la comanda
} Command;

typedef struct __eosTimer {            // Dades internes del temporitzador
    bool inUse;                        // -Indica si esta en us en el pool
    eosTimerServiceHandle hService;    // -Handle del servei
    unsigned flags;                    // -Indicadors
    unsigned timeout;                  // -Temps en ms
    unsigned counter;                  // -Contador de temps en ms
    eosTimerCallback onTimeout;        // -Notifica timeout
    eosTimerHandle hNextTimer;         // -Seguent temporitzadorde la llista
} eosTimer;

typedef struct __eosTimerService {     // Dades internes del servei
    bool inUse;                        // -Indica si esta en us en el pool
    eosTimerServiceState state;        // -Estat
    unsigned triggered;                // -Indica event del temporitzador
    eosHQueue hCommandQueue;           // -Cua de comandes
    eosTimerHandle hFirstTimer;        // -Primer temporitzador de la llista
    eosTimer *timerPool;               // -Pool de memoria
    unsigned timerPoolSize;            // -Numero maxim d'elements en el pool de memoria
} eosTimerService;


static bool initialized = false;

static void tickFunction(eosTimerServiceHandle hService);
static eosTimerHandle allocTimer(eosTimerServiceHandle hService);
static void freeTimer(eosTimerHandle hTimer);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosTimerServiceHandle eosTimerServiceInitialize(
 *               eosTimerServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 * 
 *************************************************************************/

eosTimerServiceHandle eosTimerServiceInitialize(
    eosTimerServiceParams *params) {

    if (initialized)
        return NULL;

    if (params->maxTimers < 10)
        params->maxTimers = 10;

    unsigned timerPoolSize = sizeof(eosTimer) * params->maxTimers;

    eosTimerServiceHandle hService = eosAlloc(sizeof(eosTimerService)
        + timerPoolSize);
    if (hService == NULL)
        return NULL;

    // Inicialitza la cua de commandes
    //
    eosQueueParams queueParams;
    queueParams.itemSize = sizeof(Command);
    queueParams.maxItems = 10;
    if ((hService->hCommandQueue = eosQueueCreate(&queueParams)) == NULL) {
        eosFree(hService);
        return NULL;
    }

    // Inicialitza les estructures de dades
    //
    hService->state = serviceInitializing;
    hService->triggered = 0;
    hService->hFirstTimer = NULL;
    hService->timerPool = (eosTimer*)((BYTE*)hService + sizeof(eosTimer));
    hService->timerPoolSize = params->maxTimers;

    // Asigna la funcio d'interrupcio TICK
    //
    eosTickRegisterCallback(NULL, (eosTickCallback) tickFunction, hService);

    initialized = true;
    
    return hService;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTimerServiceTask(
 *               eosTimerServiceHandle hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *************************************************************************/

void eosTimerServiceTask(
    eosTimerServiceHandle hService) {

    if (hService) {

        switch (hService->state) {

            case serviceInitializing:
                hService->state = serviceRunning;
                break;

            case serviceRunning: {

                // Obte el numero de tick pendents de procesar
                //
                bool intState = eosInterruptDisable();
                unsigned triggered = hService->triggered;
                hService->triggered = 0;
                eosInterruptRestore(intState);

                // Procesa els ticks pendents
                //
                if (triggered > 0) {

                    eosTimerHandle hTimer = hService->hFirstTimer;
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
                                if (hTimer->onTimeout)
                                    hTimer->onTimeout(hTimer);

                                // Si es ciclc, reinicia el contador
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
                while (eosQueueGet(hService->hCommandQueue, &command)) {

                    eosTimerHandle hTimer = command.hTimer;

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
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void tickFunction(
 *               eosTimerServiceHandle hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *************************************************************************/

static void tickFunction(
    eosTimerServiceHandle hService) {

    hService->triggered += 1;
}


/*************************************************************************
 *
 *       Crea un temporitzador
 *
 *       Funcio:
 *           eosTimerHandle eosTimerCreate(
 *               eosTimerServiceHandle hService
 *               eosTimerParams *params)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params  : Parametres d'inicialitzacio
 *
 *       Retorm:
 *           El Handle del timer. NULL en cas d'error
 *
 *************************************************************************/

eosTimerHandle eosTimerCreate(
    eosTimerServiceHandle hService,
    eosTimerParams *params) {

    eosTimerHandle hTimer = allocTimer(hService);
    if (hTimer == NULL)
        return NULL;

    hTimer->hService = hService;
    hTimer->timeout = params->timeout;
    hTimer->counter = params->timeout;
    hTimer->onTimeout = params->onTimeout;

    hTimer->hNextTimer = hService->hFirstTimer;
    hService->hFirstTimer = hTimer;

    return hTimer;
}


/*************************************************************************
 *
 *       Destrueix un temporitzador
 *
 *       Funcio:
 *           void eosTimerDestroy(
 *               eosTimerHandle hTimer)
 *
 *       Entrada:
 *           hTimer: El Handle del temporitzador
 *
 *************************************************************************/

void eosTimerDestroy(
    eosTimerHandle hTimer) {

    freeTimer(hTimer);
}


void eosTimerPause(
    eosTimerHandle hTimer) {

    if (hTimer) {
        Command command;
        command.opCode = opCode_Pause;
        command.hTimer = hTimer;
        eosQueuePut(hTimer->hService->hCommandQueue, &command);
    }
}


void eosTimerContinue(
    eosTimerHandle hTimer) {

    if (hTimer) {
        Command command;
        command.opCode = opCode_Continue;
        command.hTimer = hTimer;
        eosQueuePut(hTimer->hService->hCommandQueue, &command);
    }
}


void eosTimerReset(
    eosTimerHandle hTimer) {

    if (hTimer) {
        Command command;
        command.opCode = opCode_Reset;
        command.hTimer = hTimer;
        eosQueuePut(hTimer->hService->hCommandQueue, &command);
    }
}


/*************************************************************************
 *
 *       Crea un temporitzador per gestionar un retard
 *
 *       Funcio:
 *           eosTimerHandle eosTimerDelayStart(
 *               eosTimerServiceHandle hService
 *               unsigned timeout)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           timeout : Retard en ms
 *
 *       Retorn:
 *           El Handle del temporitzador. NULL en cas d'error
 *
 *************************************************************************/

eosTimerHandle eosTimerDelayStart(
    eosTimerServiceHandle hService,
    unsigned timeout) {

    eosTimerParams timerParams;
    memset(&timerParams, 0, sizeof(timerParams));
    timerParams.timeout = timeout;
    timerParams.type = TT_ONE_SHOT;

    return eosTimerCreate(hService, &timerParams);
}


/*************************************************************************
 *
 *       Comprova si ha finalitzat el retard
 *
 *       Funcio:
 *           bool eosTimerDelayGetStatus(
 *               eosTimerHandle hTimer)
 *
 *       Entrada:
 *           hTimer: El Handle del temporitzador
 *
 *       Retorn:
 *           true si ha finalitzat el retard
 *
 *************************************************************************/

bool eosTimerDelayGetStatus(
    eosTimerHandle hTimer) {

    if (hTimer && (hTimer->counter == 0)) {
        eosTimerDestroy(hTimer);
        return true;
    }
    else
        return false;
}


/*************************************************************************
 *
 *       Crea una objecte Timer
 *
 *       Funcio:
 *           eosTimerHandle allocTimer(
 *               eosTimerServiceHandle hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *       Retorn:
 *           El Handle del objecte creat. NULL en cas d'error
 *
 *************************************************************************/

static eosTimerHandle allocTimer(
    eosTimerServiceHandle hService) {

    unsigned i;
    for (i = 0; i < hService->timerPoolSize; i++) {
        eosTimerHandle hTimer = &hService->timerPool[i];
        if (!hTimer->inUse) {
            hTimer->inUse = true;
            return hTimer;
        }
    }

    return NULL;
}


/*************************************************************************
 *
 *       Destrueix un objecte Timer
 *
 *       Funcio:
 *           void freeTimer(
 *               eosTimerHandle hTimer)
 *
 *       Entrada:
 *           hTimer: Handle del objecte a destruir
 *
 *************************************************************************/

static void freeTimer(
    eosTimerHandle hTimer) {

    hTimer->inUse = false;
}
