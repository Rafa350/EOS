#include "eosTimers.h"
#include "eosMemory.h"
#include "HardwareProfile.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


#define TIMER_ID             TMR_ID_4
#define TIMER_INT_VECTOR     INT_VECTOR_T4
#define TIMER_INT_SOURCE     INT_SOURCE_TIMER_4
#define TIMER_CORE_VECTOR    _TIMER_4_VECTOR


typedef struct {             // Bloc de control del temporitzador
    unsigned timeout;        // -Temps en ms
} Timer, PTimer;

typedef enum  {
    STATE_INITIALIZE,
    STATE_TERMINATE,
    STATE_RUN,
    STATE_HALTED
} TaskState;

typedef struct {             // Dades internes
    TaskState state;         // -Estat
    BOOL triggered;          // -Indica event del temporitzador
} TaskData;


static TaskData taskData;


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

    InitTimer();

    taskData.state = STATE_INITIALIZE;
    taskData.triggered = FALSE;

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
    
    switch (taskData.state) {
        case STATE_INITIALIZE:
            StartTimer();
            taskData.state = STATE_RUN;
            break;

        case STATE_TERMINATE:
            StopTimer();
            taskData.state = STATE_HALTED;
            break;

        case STATE_HALTED:
            break;

        case STATE_RUN:
            if (taskData.triggered) {
                taskData.triggered = FALSE;
            }
            break;
    }

    return eos_RESULT_SUCCESS;
}


eosResult eosTimerCreate(eosTimerCreateParams *params, eosHandle *handle) {

    if (params == NULL)
        return eos_ERROR_PARAMS;
    if (handle == NULL)
        return eos_ERROR_PARAMS;

    PTimer pTimer = eosAlloc(sizeof(Timer));
    if (pTimer == NULL)
        return eos_ERROR_ALLOC;
    
    *handle = (eosHandle) pTimer;

    return eos_RESULT_SUCCESS;
}


eosResult eosTimerDestroy(eosHandle handle) {

    if (handle == NULL)
        return eos_ERROR_PARAMS;

    eosFree(handle);

    return eos_RESULT_SUCCESS;
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
    PLIB_TMR_Period16BitSet(TIMER_ID, 5000);

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
 *           eosTimerTMRInterruptService(void)
 *
 *************************************************************************/

void __ISR(TIMER_CORE_VECTOR, ipl2) eosTimerTMRInterruptService(void) {

    taskData.triggered = TRUE;
    
    PLIB_INT_SourceFlagClear(INT_ID_0, TIMER_INT_SOURCE);
}
