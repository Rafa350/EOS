#include "Services/__eosTimers.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"
#include "HardwareProfile.h"


static void destroyMessageQueue(eosTimerService* service);
static void sendMessage(eosTimerService* service, Message* message);
static BOOL receiveMessage(eosTimerService* service, Message* message);
static void processMessage(eosTimerService* service);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosTimerService* eosTimerServiceInitialize(
 *               eosTimerServiceParams *params);
 *
 *       Retorn:
 *           Punter al servei creat
 * 
 *************************************************************************/

eosTimerService* eosTimerServiceInitialize(eosTimerServiceParams *params) {

    eosTimerService* service = eosAlloc(sizeof(eosTimerService));
    if (service) {
    
        // Inicialitza les estructures de dades
        //
        service->state = SS_INITIALIZING;
        service->triggered = 0;
        service->hQueue = NULL;
        service->firstTimer = NULL;
   
        // Asigna la funcio d'interrupcio TICK
        //
        eosHandle hTickService = params->hTickService;
        if (hTickService == NULL)
            hTickService = eosGetTickServiceHandle();
        if (hTickService != NULL)
            eosTickAttach(hTickService, eosTimerServiceISRTick, (eosHandle) service, &service->hAttach);
        else
            service->hAttach = NULL;
    }

    return service;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTimerServiceTask(
 *               eosTimerService* service)
 *
 *       Entrada:
 *           service   : Punter al servei
 *
 *************************************************************************/

void eosTimerServiceTask(eosTimerService* service) {

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

                eosTimer* timer = service->firstTimer;
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
 *               void *context)
 *
 *       Entrada:
 *           context    : Punter al servei
 *
 *************************************************************************/

void eosTimerServiceISRTick(void *context) {

    if (context)
        ((eosTimerService*) context)->triggered += 1;
}


/*************************************************************************
 *
 *       Crea un temporitzador
 *
 *       Funcio:
 *           eosTimer* eosTimerCreate(
 *               eosTimerService* service,
 *               eosTimerParams *params)
 *
 *       Entrada:
 *           service    : Punter al servei
 *           params     : Parametres d'inicialitzacio
 *
 *       Retorm:
 *           Punter al temporitzador
 *
 *************************************************************************/

eosTimer* eosTimerCreate(eosTimerService* service, eosTimerParams *params) {

    eosTimer* timer = eosAlloc(sizeof(eosTimer));
    if (timer) {
        timer->timeout = params->timeout;
        timer->counter = params->timeout;
        timer->callback = params->callback;
        timer->context = params->context;
        timer->nextTimer = service->firstTimer;
        timer->service = service;
        service->firstTimer = timer;
    }

    return timer;
}


/*************************************************************************
 *
 *       Destrueix un temporitzador
 *
 *       Funcio:
 *           void eosTimerDestroy(
 *               eosTimer* timer)
 *
 *       Entrada:
 *           timer      : Punter al temporitzador
 *
 *************************************************************************/

void eosTimerDestroy(eosTimer* timer) {

}


void eosTimerPause(eosTimer* timer) {

    Message message;
    message.command = CMD_PAUSE;
    message.timer = timer;
    sendMessage(timer->service, &message);
}


void eosTimerContinue(eosTimer* timer) {

    Message message;
    message.command = CMD_CONTINUE;
    message.timer = timer;
    sendMessage(timer->service, &message);
}


void eosTimerReset(eosTimer* timer) {

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
 *           eosTimer* eosTimerDelayStart(
 *               eosTimerService* service,
 *               unsigned timeout)
 *
 *       Entrada:
 *           service    : Punter al servei
 *           timeout    : Retard en ms
 *
 *       Retorn: Punter al temporitzador. NULL en cas d'error
 *
 *************************************************************************/

eosTimer* eosTimerDelayStart(eosTimerService *service, unsigned timeout) {

    eosTimerParams params;
    params.timeout = timeout;
    params.type = TT_ONE_SHOT;
    params.callback = NULL;
    params.context = NULL;
        
    return eosTimerCreate(service, &params);
}


/*************************************************************************
 *
 *       Comprova si ha finalitzat el retard
 *
 *       Funcio:
 *           BOOL eosTimerDelayGetStatus(
 *               eosTimer *timer)
 *
 *       Entrada:
 *           timer      : El timer
 *
 *       Retorn:
 *           TRUE si ha finalitzat el retard
 *
 *************************************************************************/

BOOL eosTimerDelayGetStatus(eosTimer* timer) {

    if (timer->counter == 0) {
        eosTimerDestroy(timer);
        return TRUE;
    }
    else
        return FALSE;
}


static void sendMessage(eosTimerService* service, Message* message) {

    if (service->hQueue == NULL) {

        eosQueueCreateParams qp;
        qp.itemSize = sizeof(Message);
        qp.maxItems = 10;
        eosQueueCreate(&qp, &service->hQueue);
    }

    if (service->hQueue != NULL)
        eosQueuePut(service->hQueue, message);
}


static BOOL receiveMessage(eosTimerService* service, Message* message) {

    if (service->hQueue)
        return eosQueueGet(service->hQueue, message) == eos_RESULT_SUCCESS;

    else
        return FALSE;
}


static void destroyMessageQueue(eosTimerService* service) {

    if (service->hQueue)
        eosQueueDestroy(service->hQueue);
}


static void processMessage(eosTimerService* service) {

    Message __message;
    Message* message = &__message;

    while (receiveMessage(service, message)) {

        eosTimer* timer = message->timer;

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