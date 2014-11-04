#define __EOS_TIMERS_INTERNAL
#include "Services/eosTimers.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"
#include "HardwareProfile.h"


// Comandes
//
#define CMD_NOP                   0    // NOP
#define CMD_PAUSE                 1    // Posa un temporitzador en pausa
#define CMD_CONTINUE              2    // Reanuda un temporitzador
#define CMD_RESET                 3    // Reseteja un temporitzador
#define CMD_REMOVE                4    // Elimina un temporitzador

// Estats del servei
//
#define SS_INITIALIZING           0    // Inicialitzant
#define SS_RUNNING                1    // Executant

// Indicadors del temporitzador
//
#define TF_PAUSED            0x0001    // Temporitzador en pausa
#define TF_TYPE              0x0006    // Tipus de temporitzador
#define TF_TYPE_CYCLIC       0x0002    // -Ciclic
#define TF_TYPE_AUTODESTROY  0x0003    // -Destruccio automatica


typedef struct {                       // Missatge
    unsigned command;                  // -Identificador de la comanda
    struct __eosTimer *timer;          // -Temporitzador
} Message;

struct __eosTimer {                    // Dades internes del temporitzador
    struct __eosTimerService *service; // -Servei asociat
    unsigned flags;                    // -Indicadors
    unsigned timeout;                  // -Temps en ms
    unsigned counter;                  // -Contador de temps en ms
    eosCallback callback;              // -Funcio callback
    void *context;                     // -Parametre de la funcio callback
    struct __eosTimer *nextTimer;      // -Seguent temporitzadorde la llista
};

struct __eosTimerService {             // Dades internes del servei
    unsigned state;                    // -Estat
    unsigned triggered;                // -Indica event del temporitzador
    eosHandle hQueue;                  // -Cua de missatges
    struct __eosTimer *firstTimer;     // -Primer temporitzador de la llista
};


// Definicio de funcions locals
//
static void destroyMessageQueue(eosTimerService service);
static void sendMessage(eosTimerService service, Message* message);
static BOOL receiveMessage(eosTimerService service, Message* message);
static void processMessage(eosTimerService service);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerServiceInitialize(
 *               eosTimerServiceParams *params,
 *               eosTimerService *service);
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

eosResult eosTimerServiceInitialize(eosTimerServiceParams *params, eosTimerService *_service) {

    eosTimerService service = eosAlloc(sizeof(struct __eosTimerService));
    if (service == NULL)
        return eos_ERROR_ALLOC;
    
    // Inicialitza les estructures de dades
    //
    service->state = SS_INITIALIZING;
    service->triggered = 0;
    service->hQueue = NULL;
    service->firstTimer = NULL;
   
    // Asigna la funcio d'interrupcio TICK
    //
    eosTickService tickService = params->tickService;
    if (tickService == NULL)
        tickService = eosGetTickServiceHandle();
    if (tickService != NULL)
        eosTickAttach(tickService, (eosCallback) eosTimerServiceISRTick, (void*) service);

    *_service = service;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTimerServiceTask(
 *               eosTimerService service)
 *
 *       Entrada:
 *           service: El handler del servei
 *
 *************************************************************************/

void eosTimerServiceTask(eosTimerService service) {

    switch (service->state) {
        case SS_INITIALIZING:
            service->state = SS_RUNNING;
            break;

        case SS_RUNNING: {

            // Obte el numero de tick pendents de procesar
            //
            BOOL intFlag = eosGetInterruptState();
            eosDisableInterrupts();
            unsigned triggered = service->triggered;
            service->triggered = 0;
            if (intFlag)
                eosEnableInterrupts();

            // Si hi han ticks a procesar...
            //
            if (triggered > 0) {

                eosTimer timer = service->firstTimer;
                while (timer) {
                    if ((timer->flags & TF_PAUSED) != TF_PAUSED) {

                        // Decrementa el contador
                        //
                        if (triggered > timer->counter)
                            timer->counter = 0;
                        else
                            timer->counter -= triggered;

                        // Si el contador arriba a zero...
                        //
                        if (timer->counter == 0) {

                            // Crida a la funcio callback
                            //
                            if (timer->callback != NULL)
                                timer->callback(timer->context);

                            // Si es ciclc, reicicia el contador
                            //
                            if ((timer->flags & TF_TYPE) == TF_TYPE_CYCLIC)
                                timer->counter = timer->timeout;
                        }
                    }

                    timer = timer->nextTimer;
                }
            }

            // Procesa els missatges pendents
            //
            processMessage(service);

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
 *               eosTimerService service)
 *
 *       Entrada:
 *           service: El handler del servei
 *
 *************************************************************************/

void eosTimerServiceISRTick(eosTimerService service) {

    service->triggered += 1;
}


/*************************************************************************
 *
 *       Crea un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerCreate(
 *               eosTimerService service,
 *               eosTimerParams *params,
 *               eosTimer *timer)
 *
 *       Entrada:
 *           service: Handler del servei
 *           params : Parametres d'inicialitzacio
 *
 *       Sortida:
 *           timer: El handler del temporitzador
 *
 *       Retorm:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosTimerCreate(eosTimerService service, eosTimerParams *params, eosTimer *_timer) {

    eosTimer timer = eosAlloc(sizeof(struct __eosTimer));
    if (timer == NULL)
        return eos_ERROR_ALLOC;

    timer->timeout = params->timeout;
    timer->counter = params->timeout;
    timer->callback = params->callback;
    timer->context = params->context;

    timer->service = service;
    timer->nextTimer = service->firstTimer;
    service->firstTimer = timer;

    *_timer = timer;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerDestroy(
 *               eosTimer timer)
 *
 *       Entrada:
 *           timer: El handler del temporitzador
 *
 *************************************************************************/

eosResult eosTimerDestroy(eosTimer timer) {

    return eos_RESULT_SUCCESS;
}


void eosTimerPause(eosTimer timer) {

    Message message;
    message.command = CMD_PAUSE;
    message.timer = timer;
    sendMessage(timer->service, &message);
}


void eosTimerContinue(eosTimer timer) {

    Message message;
    message.command = CMD_CONTINUE;
    message.timer = timer;
    sendMessage(timer->service, &message);
}


void eosTimerReset(eosTimer timer) {

    Message message;
    message.command = CMD_RESET;
    message.timer = timer;
    sendMessage(timer->service, &message);
}


/*************************************************************************
 *
 *       Crea un temporitzador per gestionar un retard
 *
 *       Funcio:
 *           eosTimer eosTimerDelayStart(
 *               eosTimerService* service,
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

eosTimer eosTimerDelayStart(eosTimerService service, unsigned timeout) {

    eosTimerParams params;
    params.timeout = timeout;
    params.type = TT_ONE_SHOT;
    params.callback = NULL;
    params.context = NULL;

    eosTimer timer;
    if (eosTimerCreate(service, &params, &timer) == eos_RESULT_SUCCESS)
        return timer;
    else
        return NULL;
}


/*************************************************************************
 *
 *       Comprova si ha finalitzat el retard
 *
 *       Funcio:
 *           BOOL eosTimerDelayGetStatus(
 *               eosTimer timer)
 *
 *       Entrada:
 *           timer: El handler del temporitzador
 *
 *       Retorn:
 *           TRUE si ha finalitzat el retard
 *
 *************************************************************************/

BOOL eosTimerDelayGetStatus(eosTimer timer) {

    if (timer->counter == 0) {
        eosTimerDestroy(timer);
        return TRUE;
    }
    else
        return FALSE;
}


static void sendMessage(eosTimerService service, Message* message) {

    if (service->hQueue == NULL) {

        eosQueueCreateParams qp;
        qp.itemSize = sizeof(Message);
        qp.maxItems = 10;
        eosQueueCreate(&qp, &service->hQueue);
    }

    if (service->hQueue != NULL)
        eosQueuePut(service->hQueue, message);
}


static BOOL receiveMessage(eosTimerService service, Message* message) {

    if (service->hQueue)
        return eosQueueGet(service->hQueue, message) == eos_RESULT_SUCCESS;

    else
        return FALSE;
}


static void destroyMessageQueue(eosTimerService service) {

    if (service->hQueue)
        eosQueueDestroy(service->hQueue);
}


static void processMessage(eosTimerService service) {

    Message __message;
    Message* message = &__message;

    while (receiveMessage(service, message)) {

        eosTimer timer = message->timer;

        switch (message->command) {
            case CMD_PAUSE:
                timer->flags |= TF_PAUSED;
                break;

            case CMD_CONTINUE:
                timer->flags &= ~TF_PAUSED;
                break;

            case CMD_RESET:
                timer->flags &= ~TF_PAUSED;
                timer->counter = timer->timeout;
                break;
        }
    }
}