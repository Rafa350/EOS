#include "System/eosMemory.h"
#include "Services/eosTimers.h"
#include "HardwareProfile.h"


#define MAX_TIMERS           20


typedef struct {                  // Bloc de control del temporitzador
    unsigned timeout;             // -Temps en ms
} Timer, *PTimer;

typedef enum  {                   // Estat del servei
    STATE_INITIALIZE,             // -Inicialitza
    STATE_TERMINATE,              // -Finalitza
    STATE_ACTIVE,                 // -Actiu
} State;

typedef struct {                  // Dades internes
    State state;                  // -Estat
    BOOL terminate;               // -Indica si cal acabar
    unsigned triggered;           // -Indica event del temporitzador
    unsigned maxTimers;           // -Numero maxim de temporitzadors
    unsigned numTimers;           // -Numero de temporitzadors actius
    PTimer timers[MAX_TIMERS];    // -Llista de temporitzadors actius
} Data, *PData;


static PData data = NULL;


static void InitTimer(void);
static void StartTimer(void);
static void StopTimer(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerInitialize(void)
 *
 *       Retorn:
 *           eos_RETURN_SUCCESS si tot es correcte
 * 
 *************************************************************************/

eosResult eosTimerInitialize(void) {

    data = eosAlloc(sizeof(Data));
    if (data == NULL)
        return eos_ERROR_ALLOC;

    data->state = STATE_INITIALIZE;
    data->triggered = 0;
    data->maxTimers = MAX_TIMERS;
    data->numTimers = 0;
    data->terminate = FALSE;
    memset(data->timers, 0, sizeof(data->timers));

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Finalitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerTerminate(void)
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerTerminate(void) {

    data->terminate = TRUE;

    return eos_RESULT_SUCCESS;
}



/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           eosResult eosTimerTask(void)
 *
 *       Return:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerTask(void) {

    switch (data->state) {
        case STATE_INITIALIZE:
            data->state = STATE_ACTIVE;
            break;

        case STATE_TERMINATE:
            break;

        case STATE_ACTIVE: {

            eosDisableInterrupts();
            unsigned triggered = data->triggered;
            data->triggered = 0;
            eosEnableInterrupts();

            if (triggered > 0) {

                int i;
                for (i = 0; i < data->maxTimers; i++) {
                    PTimer pTimer = data->timers[i];
                    if ((pTimer != NULL) && (pTimer->timeout > 0)) {
                        if ((pTimer->timeout -= triggered) <= 0) {
                            pTimer->timeout = 0;

                            // TODO cridar al callback
                        }
                    }
                }
            }
            if (data->terminate)
                data->state = STATE_TERMINATE;
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
 *           contrext: Contexte
 *
 *************************************************************************/

void eosTimerISRTick(void *context) {

    data->triggered += 1;
}


/*************************************************************************
 *
 *       Crea un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerCreate(eosTimerCreateParams *params,
 *               eosHandle *handle)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Sortida:
 *           handle: Handle del temporitzador
 *
 *       Retorm:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerCreate(eosTimerCreateParams *params, eosHandle *handle) {

    if (params == NULL)
        return eos_ERROR_PARAMS;
    if (handle == NULL)
        return eos_ERROR_PARAMS;

    if (data->numTimers >= MAX_TIMERS)
        return eos_ERROR_TIMER_UNAVAILABLE;

    PTimer pTimer = eosAlloc(sizeof(Timer));
    if (pTimer == NULL)
        return eos_ERROR_ALLOC;
    pTimer->timeout = params->timeOut;

    int i;
    for (i = 0; i < data->maxTimers; i++) {
        if (data->timers[i] == NULL) {
            data->timers[i] = pTimer;
            break;
        }
    }
    data->numTimers += 1;

    *handle = (eosHandle) pTimer;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix un temporitzador
 *
 *       Funcio:
 *           eosResult eosTimerDestroy(eosHandle handle)
 *
 *       Entrada:
 *           handle: Handler del temporitzador
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTimerDestroy(eosHandle handle) {

    if (handle == NULL)
        return eos_ERROR_PARAMS;

    int i;
    for (i = 0; i < data->maxTimers; i++) {
        if (data->timers[i] == (PTimer) handle) {
            data->timers[i] = NULL;
            data->numTimers -= 1;
            eosFree(handle);
            return eos_RESULT_SUCCESS;
        }
    }

    return eos_ERROR_PARAMS;
}


/*************************************************************************
 *
 *       Crea un temporitzador per gestionar un retard
 *
 *       Funcio:
 *           eosHandle eosTimerDelayStart(unsigned timeout)
 *
 *       Entrada:
 *           timeout: Retard en ms
 *
 *       Retorn: El handler del temporitzador. NULL en cas d'error
 *
 *************************************************************************/

eosHandle eosTimerDelayStart(unsigned timeout) {

    eosHandle handle;

    eosTimerCreateParams params;
    params.timeOut = timeout;
    params.callback = NULL;
    params.context = NULL;

    if (eosTimerCreate(&params, &handle) != eos_RESULT_SUCCESS)
        return NULL;

    return handle;
}


BOOL eosTimerDelayGetStatus(eosHandle handle) {

    if (handle == NULL)
        return eos_ERROR_PARAMS;

    BOOL result = FALSE;
    PTimer pTimer = (PTimer) handle;
    if (pTimer->timeout == 0) {
        result = TRUE;
        eosTimerDestroy(handle);
    }

    return result;
}
