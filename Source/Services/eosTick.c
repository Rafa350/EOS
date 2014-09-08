#include "System/eosMemory.h"
#include "Services/eosTick.h"
#include "HardwareProfile.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


#define TIMER_ID             TMR_ID_4
#define TIMER_INT_VECTOR     INT_VECTOR_T4
#define TIMER_INT_SOURCE     INT_SOURCE_TIMER_4
#define TIMER_CORE_VECTOR    _TIMER_4_VECTOR


typedef enum  {                   // Estat del servei
    STATE_INITIALIZE,             // -Inicialitza
    STATE_TERMINATE,              // -Finalitza
    STATE_ACTIVE,                 // -Actiu
} State;

typedef struct {                  // Funcio adjunte
    eosTickCallback callback;     // -Funcio callback
    void *context;                // -Parametre de la funcio callback
} Attach, *PAttach;

typedef struct {                  // Dades internes del servei
    State state;                  // -Estat
    BOOL terminate;               // -Indica si cal acabar
    unsigned maxAttaches;         // -Numero maxim d'adjunts
    PAttach attaches;             // -llista d'adjunts
} Service, *PService;


static PService isrService = NULL;


static void InitTimer(void);
static void StartTimer(void);
static void StopTimer(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosTickInitialize(eosTickInitializeParams *params,
 *               eosHandle *hService)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Sortida:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           eos_RETURN_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickInitialize(eosTickInitializeParams *params, eosHandle *hService) {

    if (params == NULL)
        return eos_ERROR_PARAMS;
    if (hService == NULL)
        return eos_ERROR_PARAMS;

    unsigned attachesSize = sizeof(Attach) * params->maxAttaches;

    PService service = eosAlloc(sizeof(Service) + attachesSize);
    if (service == NULL)
        return eos_ERROR_ALLOC;

    service->state = STATE_INITIALIZE;
    service->terminate = FALSE;
    service->maxAttaches = params->maxAttaches;
    service->attaches = (PAttach)((BYTE*) service + sizeof(Service));
    memset(service->attaches, 0, attachesSize);

    InitTimer();

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
 *           hService: El handler del servei
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickTerminate(eosHandle hService) {

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
 *           eosResult eosTickTask(eosHandle hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *       Return:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickTask(eosHandle hService) {

    if (hService == NULL)
        return eos_ERROR_PARAMS;

    PService service = (PService) hService;

    switch (service->state) {
        case STATE_INITIALIZE:
            isrService = service;
            StartTimer();
            service->state = STATE_ACTIVE;
            break;

        case STATE_TERMINATE:
            //eosFree(service);
            break;

        case STATE_ACTIVE: {
            if (service->terminate) {
                StopTimer();
                isrService = NULL;
                service->state = STATE_TERMINATE;
            }
            break;
        }
    }

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Asigna una funcio per disparar
 *
 *       Funcio:
 *           eosResult eosTickAttach(eosHandle hService,
 *               eosTickCallback callback, void *context)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           callback: Funcio a asignar
 *           context : Contexte
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *       Notes:
 *           La funcio es crida en el contexte ISR
 *
 *************************************************************************/

eosResult eosTickAttach(eosHandle hService, eosTickCallback callback, void *context) {

    if (hService == NULL)
        return eos_ERROR_PARAMS;
    if (callback == NULL)
        return eos_ERROR_PARAMS;

    int i;
    PService service = (PService) hService;

    eosDisableInterrupts();
    for (i = 0; i < service->maxAttaches; i++) {
        PAttach attach = &service->attaches[i];
        if (attach->callback == NULL) {
            attach->callback = callback;
            attach->context = context;
            break;
        }
    }
    eosEnableInterrupts();

    return i == service->maxAttaches ? eos_ERROR_INVALID : eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Desasigna una funcio
 *
 *       Funcio:
 *           eosResult eosTickUnAttach(eosHandle hService, eosTickCallback callback)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           callback: La funcio
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickUnAttach(eosHandle hService, eosTickCallback callback) {

    if (hService == NULL)
        return eos_ERROR_PARAMS;
    if (callback == NULL)
        return eos_ERROR_PARAMS;

    int i;
    PService service = (PService) hService;
    
    eosDisableInterrupts();
    for (i = 0; i < service->maxAttaches; i++) {
        PAttach attach = &service->attaches[i];
        if (attach->callback == callback) {
            attach->callback = NULL;
            break;
        }
    }
    eosEnableInterrupts();

    return i == service->maxAttaches ? eos_ERROR_INVALID : eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Inicialitza el temporitzador
 *
 *       Funcio:
 *           void InitTimer(void)
 *
 *************************************************************************/

static void InitTimer(void) {

    PLIB_TMR_Stop(TIMER_ID);

    // Inicialitza el temporitzador per genera una interrupcio a 1KHz (1ms)
    //
    PLIB_TMR_ClockSourceSelect(TIMER_ID, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TIMER_ID, TMR_PRESCALE_VALUE_16);
    PLIB_TMR_Mode16BitEnable(TIMER_ID);
    PLIB_TMR_Counter16BitClear(TIMER_ID);
    PLIB_TMR_Period16BitSet(TIMER_ID, CLOCK_PERIPHERICAL_HZ / 16 / 1000);

    // Configura les interrupcions del temporitzador
    //
    PLIB_INT_SourceEnable(INT_ID_0, TIMER_INT_SOURCE);
    PLIB_INT_VectorPrioritySet(INT_ID_0, TIMER_INT_VECTOR, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, TIMER_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
}


/*************************************************************************
 *
 *       Activa el temporitzador, i comença a generar interrupcions
 *
 *       Funcio:
 *           void StartTimer(void) {
 *
 *************************************************************************/

static void StartTimer(void) {

    PLIB_TMR_Start(TIMER_ID);
}


/*************************************************************************
 *
 *       Descativa el temporitzador
 *
 *       Funcio:
 *           void StopTimer(void)
 *
 *************************************************************************/

static void StopTimer(void) {

    PLIB_TMR_Stop(TIMER_ID);
}


/*************************************************************************
 *
 *       Gestiona la interrupcio del temporitzador
 *
 *       Funcio:
 *           eosTickTMRInterruptService(void)
 *
 *************************************************************************/

void __ISR(TIMER_CORE_VECTOR, ipl2) eosTickTMRInterruptService(void) {

    if (isrService != NULL) {
        int i;
        for (i = 0; i < isrService->maxAttaches; i++) {
            PAttach attach = &isrService->attaches[i];
            if (attach->callback != NULL)
                attach->callback(attach->context);
        }
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, TIMER_INT_SOURCE);
}
