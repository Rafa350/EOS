#include "System/eosMemory.h"
#include "Services/eosTimers.h"
#include "HardwareProfile.h"


typedef enum {                    // Estat del servei
    STATE_INITIALIZE,             // -Inicialitza
    STATE_TERMINATE,              // -Finalitza
    STATE_ACTIVE,                 // -Actiu
} State;

typedef struct {                  // Bloc de control del temporitzador
    unsigned timeout;             // -Temps en ms
    eosTimerCallback callback;    // -Funcio callback
    void *context;                // -Parametre de la funcio callback
    struct __DATA *service;       // -Servei 
} Timer, *PTimer;

typedef struct __DATA {           // Dades internes
    State state;                  // -Estat
    BOOL terminate;               // -Indica si cal acabar
    unsigned triggered;           // -Indica event del temporitzador
    unsigned maxTimers;           // -Numero maxim de temporitzadors
    unsigned numTimers;           // -Numero de temporitzadors actius
    PTimer timers;                // -Llista de temporitzadors actius
} Service, *PService;


static void InitTimer(void);
static void StartTimer(void);
static void Stotimer(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerInitialize(eosTimerInitializeParams *params,
 *               eosHandle *hService)
 *
 *       Sortida:
 *           hService: Handler del servei
 *
 *       Retorn:
 *           eos_RETURN_SUCCESS si tot es correcte
 * 
 *************************************************************************/

eosResult eosTimerInitialize(eosTimerInitializeParams *params, eosHandle *hService) {

    if (params == NULL)
        return eos_ERROR_PARAMS;
    if (hService == NULL)
        return eos_ERROR_PARAMS;
    
    unsigned timersSize = sizeof(Timer) * params->maxTimers;
    
    PService service = eosAlloc(sizeof(Service) + timersSize);
    if (service == NULL)
        return eos_ERROR_ALLOC;

    service->state = STATE_INITIALIZE;
    service->triggered = 0;
    service->maxTimers = params->maxTimers;
    service->numTimers = 0;
    service->terminate = FALSE;
    service->timers = (PTimer)((BYTE*) service + sizeof(Service));
    memset(service->timers, 0, timersSize);
    
    *hService = (eosHandle) service;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Finalitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerTerminate(eosHandle hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerTerminate(eosHandle hService) {

    if (hService == NULL)
        return eos_ERROR_PARAMS;

    PService service = (PService) hService;
    service->terminate = TRUE;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           eosResult eosTimerTask(eosService hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *       Return:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerTask(eosHandle hService) {

    if (hService == NULL)
        return eos_ERROR_PARAMS;

    PService service = (PService) hService;

    switch (service->state) {
        case STATE_INITIALIZE:
            service->state = STATE_ACTIVE;
            break;

        case STATE_TERMINATE:
            break;

        case STATE_ACTIVE: {

            eosDisableInterrupts();
            unsigned triggered = service->triggered;
            service->triggered = 0;
            eosEnableInterrupts();

            if (triggered > 0) {

                int i;
                for (i = 0; i < service->maxTimers; i++) {
                    PTimer timer = &service->timers[i];
                    if ((timer->service != NULL) && (timer->timeout > 0)) {
                        if ((timer->timeout -= triggered) <= 0) {
                            timer->timeout = 0;

                            // TODO: cridar al callback
                        }
                    }
                }
            }
            if (service->terminate)
                service->state = STATE_TERMINATE;
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
 *           eosResult eosTimerCreate(eosHandle hService,
 *               eosTimerCreateParams *params, eosHandle *hTimer)
 *
 *       Entrada:
 *           hService: Hasdler del servei
 *           params  : Parametres d'inicialitzacio
 *
 *       Sortida:
 *           hTimer: Handle del temporitzador
 *
 *       Retorm:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerCreate(eosHandle hService, eosTimerCreateParams *params,
    eosHandle *hTimer) {

    if (hService == NULL)
        return eos_ERROR_PARAMS;
    if (params == NULL)
        return eos_ERROR_PARAMS;
    if (hTimer == NULL)
        return eos_ERROR_PARAMS;

    PService service = (PService) hService;

    if (service->numTimers >= service->maxTimers)
        return eos_ERROR_TIMER_UNAVAILABLE;

    int i;
    for (i = 0; i < service->maxTimers; i++) {
        PTimer timer = &service->timers[i];
        if (timer->service == NULL) {
            service->numTimers += 1;
            timer->timeout = params->timeout;
            timer->callback = params->callback;
            timer->context = params->context;
            timer->service = service;
            *hTimer = (eosHandle) timer;
            break;
        }
    }

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerDestroy(eosHandle hTimer)
 *
 *       Entrada:
 *           hTimer: Handler del temporitzador
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerDestroy(eosHandle hTimer) {

    if (hTimer == NULL)
        return eos_ERROR_PARAMS;

    PTimer timer = (PTimer) hTimer;
    timer->service = NULL;

    PService service = timer->service;
    service->numTimers -= 1;
    
    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Crea un temporitzador per gestionar un retard
 *
 *       Funcio:
 *           eosHandle eosTimerDelayStart(eosHandle hService, unsigned timeout)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           timeout : Retard en ms
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
    params.callback = NULL;
    params.context = NULL;

    if (eosTimerCreate(hService, &params, &hTimer) != eos_RESULT_SUCCESS)
        return NULL;

    return hTimer;
}


BOOL eosTimerDelayGetStatus(eosHandle hTimer) {

    if (hTimer == NULL)
        return FALSE;

    BOOL result = FALSE;
    PTimer timer = (PTimer) hTimer;
    if (timer->timeout == 0) {
        result = TRUE;
        eosTimerDestroy(hTimer);
    }

    return result;
}
