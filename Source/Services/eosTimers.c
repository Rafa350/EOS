#include "Services/eosTimers.h"
#include "Services/eosTick.h"
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
} ServiceStates;

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
    bool inUse;                        // -Indica si esta en us en el pool
    eosHTimerService hService;         // -Servei asociat
    unsigned flags;                    // -Indicadors
    unsigned timeout;                  // -Temps en ms
    unsigned counter;                  // -Contador de temps en ms
    eosEvent onTimeout;                // -Event TIMEOUT
    eosHTimer hNextTimer;              // -Seguent temporitzadorde la llista
} Timer;

typedef struct __eosTimerService {     // Dades internes del servei
    bool inUse;                        // -Indica si esta en us en el pool
    ServiceStates state;               // -Estat
    unsigned triggered;                // -Indica event del temporitzador
    eosHQueue hCommandQueue;           // -Cua de comandes
    eosHTimer hFirstTimer;             // -Primer temporitzador de la llista
} TimerService;


// Pool de memoria pels timers
//
static bool timerPoolInitialized = false;
static Timer timerPool[eosOPTIONS_TIMERS_MAX_TIMERS];


static eosHTimer allocTimer(void);
static void freeTimer(eosHTimer hTimer);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosHTimerService eosTimerServiceInitialize(
 *               eosTimerServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 * 
 *************************************************************************/

eosHTimerService eosTimerServiceInitialize(
    eosTimerServiceParams *params) {

    eosHTimerService hService = (eosHTimerService) eosAlloc(sizeof(TimerService));
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

    // Asigna la funcio d'interrupcio TICK
    //
    eosHTickService hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, (eosTickCallback) eosTimerServiceTick, (void*) hService);

    return hService;
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
        case serviceInitializing:
            hService->state = serviceRunning;
            break;

        case serviceRunning: {

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
                            if (hTimer->onTimeout.method)
                                hTimer->onTimeout.method(hTimer->onTimeout.target, hTimer);

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
            while (eosQueueGet(hService->hCommandQueue, &command)) {

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
 *           void eosTimerServiceTick(
 *               eosHTimerService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosTimerServiceTick(
    eosHTimerService hService) {

    hService->triggered += 1;
}


/*************************************************************************
 *
 *       Crea un temporitzador
 *
 *       Funcio:
 *           eosHTimer eosTimerCreate(
 *               eosHTimerService hService,
 *               eosTimerParams *params)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params : Parametres d'inicialitzacio
 *
 *       Retorm:
 *           El handler del timer. NULL en cas d'error
 *
 *************************************************************************/

eosHTimer eosTimerCreate(
    eosHTimerService hService,
    eosTimerParams *params) {

    eosHTimer hTimer = allocTimer();
    if (hTimer == NULL)
        return NULL;

    hTimer->timeout = params->timeout;
    hTimer->counter = params->timeout;
    hTimer->onTimeout = params->onTimeout;

    hTimer->hService = hService;
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
 *               eosHTimer hTimer)
 *
 *       Entrada:
 *           hTimer: El handler del temporitzador
 *
 *************************************************************************/

void eosTimerDestroy(
    eosHTimer hTimer) {

    freeTimer(hTimer);
}


void eosTimerPause(
    eosHTimer hTimer) {

    Command command;
    command.opCode = opCode_Pause;
    command.hTimer = hTimer;
    eosQueuePut(hTimer->hService->hCommandQueue, &command);
}


void eosTimerContinue(
    eosHTimer hTimer) {

    Command command;
    command.opCode = opCode_Continue;
    command.hTimer = hTimer;
    eosQueuePut(hTimer->hService->hCommandQueue, &command);
}


void eosTimerReset(
    eosHTimer hTimer) {

    Command command;
    command.opCode = opCode_Reset;
    command.hTimer = hTimer;
    eosQueuePut(hTimer->hService->hCommandQueue, &command);
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
 *               eosHTimer hTimer)
 *
 *       Entrada:
 *           hTimer: El handler del temporitzador
 *
 *       Retorn:
 *           true si ha finalitzat el retard
 *
 *************************************************************************/

bool eosTimerDelayGetStatus(
    eosHTimer hTimer) {

    if (hTimer->counter == 0) {
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
 *           eosHTimer allocTimer(void)
 *
 *       Retorn:
 *           El handler del objecte creat. NULL en cas d'error
 *
 *************************************************************************/

static eosHTimer allocTimer(void) {

    int i;

    if (!timerPoolInitialized) {
        for (i = 0; i < sizeof(timerPool) / sizeof(timerPool[0]); i++)
            timerPool[i].inUse = false;
        timerPoolInitialized = true;
    }

    for (i = 0; i < sizeof(timerPool) / sizeof(timerPool[0]); i++) {
        eosHTimer hTimer = &timerPool[i];
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
 *           void freeTimer(eosHTimer hTimer)
 *
 *       Entrada:
 *           hTimer: Handler del objecte a destruir
 *
 *************************************************************************/

static void freeTimer(eosHTimer hTimer) {

    hTimer->inUse = false;
}