#include "System/eosMemory.h"
#include "Services/eosTimers.h"
#include "Services/eosTick.h"
#include "HardwareProfile.h"


typedef enum {                    // Estat del servei
    serviceStateInitialize,       // -Inicialitza
    serviceStateTerminate,        // -Finalitza
    serviceStateActive,           // -Actiu
} ServiceState;

typedef enum {                    // Estat del temporitzador
    timerStateFree,               // -Lliure
    timerStateActive,             // -Actiu (Esta contant)
    timerStateInactive            // -Inactiu (Esta en pausa)
} TimerState;

typedef struct {                  // Bloc de control del temporitzador
    TimerState state;             // -Estat
    unsigned timeout;             // -Temps en ms
    unsigned counter;             // -Contador de temps en ms
    eosTimerType type;            // -Tipus de temporitzador
    eosCallback callback;         // -Funcio callback
    void *context;                // -Parametre de la funcio callback
} Timer, *PTimer;

typedef struct  {                 // Dades internes
    ServiceState state;           // -Estat
    BOOL terminate;               // -Indica si cal acabar
    unsigned triggered;           // -Indica event del temporitzador
    unsigned maxTimers;           // -Numero maxim de temporitzadors
    PTimer timers;                // -Llista de temporitzadors
} Service, *PService;


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerInitialize(
 *               eosTimerInitializeParams *params,
 *               eosHandle *hService)
 *
 *       Sortida:
 *           hService   : Handler del servei
 *
 *       Retorn:
 *           eos_RETURN_SUCCESS si tot es correcte
 * 
 *************************************************************************/

eosResult eosTimerInitialize(eosTimerInitializeParams *params, eosHandle *hService) {

    // Comprova els parametres
    //
#ifdef eos_OPTION_CheckInputParams
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    // Crea les estructures de dades en el HEAP
    //
    PService service = eosAlloc(sizeof(Service));
    if (service == NULL)
        return eos_ERROR_ALLOC;

    PTimer timers = eosAlloc(sizeof(Timer) * params->maxTimers);
    if (timers == NULL) {
        eosFree(service);
        return eos_ERROR_ALLOC;
    }

    // Inicialitza les estructures de dades
    //
    service->state = serviceStateInitialize;
    service->triggered = 0;
    service->maxTimers = params->maxTimers;
    service->terminate = FALSE;
    service->timers = timers;
    
    unsigned i;
    for (i = 0; i < service->maxTimers; i++)
        service->timers[i].state = timerStateFree;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHandle hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, eosTimerISRTick, (eosHandle) service);

    // Retorna resultats i finalitza
    //
    *hService = (eosHandle) service;
    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Finalitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerTerminate(
 *               eosHandle hService)
 *
 *       Entrada:
 *           hService   : Handler del servei
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerTerminate(eosHandle hService) {

    // Comprova els parametres
    //
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    // Notifica el final i espera que finalitzi
    //
    service->terminate = TRUE;
    while (service->state != serviceStateTerminate)
        eosTimerTask(hService);

    // Allibera la memoria de les estructures de dades
    //
    eosFree(service->timers);
    eosFree(service);

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           eosResult eosTimerTask(
 *               eosService hService)
 *
 *       Entrada:
 *           hService   : Handler del servei
 *
 *       Return:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerTask(eosHandle hService) {

    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    switch (service->state) {
        case serviceStateInitialize:
            service->state = serviceStateActive;
            break;

        case serviceStateTerminate:
            break;

        case serviceStateActive: {

            BOOL intFlag = eosGetInterruptState();
            eosDisableInterrupts();
            unsigned triggered = service->triggered;
            service->triggered = 0;
            if (intFlag)
                eosEnableInterrupts();

            if (triggered > 0) {

                unsigned i;
                for (i = 0; i < service->maxTimers; i++) {
                    PTimer timer = &service->timers[i];

                    if (timer->state == timerStateActive) {
                        if (triggered > timer->counter)
                            timer->counter = 0;
                        else
                            timer->counter -= triggered;

                        if (timer->counter == 0) {
                            if (timer->callback != NULL)
                                timer->callback(timer->context);

                            if (timer->type == TT_CYCLIC)
                                timer->counter = timer->timeout;

                            else
                                timer->state = timer->type == TT_ONE_SHOT_AUTODESTROY ? timerStateFree : timerStateInactive;
                        }
                    }
                }
            }
            if (service->terminate)
                service->state = serviceStateTerminate;
            break;
        }
    }

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosTimerISRTick(void *context)
 *
 *       Entrada:
 *           context: Handler del sevei
 *
 *************************************************************************/

void eosTimerISRTick(void *context) {

    if (context == NULL)
        return;

    PService service = (PService) context;
    service->triggered += 1;
}


/*************************************************************************
 *
 *       Crea un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerCreate(
 *               eosHandle hService,
 *               eosTimerCreateParams *params,
 *               eosHandle *hTimer)
 *
 *       Entrada:
 *           hService   : Hasdler del servei
 *           params     : Parametres d'inicialitzacio
 *
 *       Sortida:
 *           hTimer     : Handle del temporitzador
 *
 *       Retorm:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerCreate(eosHandle hService, eosTimerCreateParams *params,
    eosHandle *hTimer) {

    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hTimer == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    unsigned i;
    for (i = 0; i < service->maxTimers; i++) {
        PTimer timer = &service->timers[i];
        if (!timer->state == timerStateFree) {
            timer->timeout = params->timeout;
            timer->counter = params->timeout;
            timer->type = params->type;
            timer->callback = params->callback;
            timer->context = params->context;
            timer->state = timerStateActive;
            *hTimer = (eosHandle) timer;
            break;
        }
    }
    if (i == service->maxTimers)
        return eos_ERROR_OPERATION;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerDestroy(
 *               eosHandle hTimer)
 *
 *       Entrada:
 *           hTimer     : Handler del temporitzador
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerDestroy(eosHandle hTimer) {

    if (hTimer == NULL)
        return eos_ERROR_PARAM_NULL;

    PTimer timer = (PTimer) hTimer;
    timer->state = timerStateFree;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Crea un temporitzador per gestionar un retard
 *
 *       Funcio:
 *           eosHandle eosTimerDelayStart(
 *               eosHandle hService,
 *               unsigned timeout)
 *
 *       Entrada:
 *           hService   : Handler del servei
 *           timeout    : Retard en ms
 *
 *       Retorn: El handler del temporitzador. NULL en cas d'error
 *
 *************************************************************************/

eosHandle eosTimerDelayStart(eosHandle hService, unsigned timeout) {

    if (hService == NULL)
        return NULL;

    eosHandle hTimer;

    eosTimerCreateParams params;
    params.timeout = timeout;
    params.type = TT_ONE_SHOT;
    params.callback = NULL;
    params.context = NULL;

    if (eosTimerCreate(hService, &params, &hTimer) != eos_RESULT_SUCCESS)
        return NULL;

    return hTimer;
}


/*************************************************************************
 *
 *       Comprova si ha finalitzat el retard
 *
 *       Funcio:
 *           BOOL eosTimerDelayGetStatus(
 *               eosHandle hTimer)
 *
 *       Entrada:
 *           hTimer     : Handler del timer
 *
 *       Retorn:
 *           TRUE si ha finalitzat el retard
 *
 *************************************************************************/

BOOL eosTimerDelayGetStatus(eosHandle hTimer) {

    if (hTimer == NULL)
        return FALSE;

    if (((PTimer) hTimer)->counter == 0) {
        eosTimerDestroy(hTimer);
        return TRUE;
    }
    else
        return FALSE;
}
