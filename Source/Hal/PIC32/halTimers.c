#include "eosHAL.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


static TMR_MODULE_ID timerId[halTimer_NUM_TIMERS] = {

    TMR_ID_1,
    TMR_ID_2,
    TMR_ID_3,
    TMR_ID_4,
    TMR_ID_5
};

static INT_SOURCE timerIntSource[halTimer_NUM_TIMERS] = {

    INT_SOURCE_TIMER_1,
    INT_SOURCE_TIMER_2,
    INT_SOURCE_TIMER_3,
    INT_SOURCE_TIMER_4,
    INT_SOURCE_TIMER_5
};

static INT_VECTOR timerIntVector[halTimer_NUM_TIMERS] = {
    INT_VECTOR_T1,
    INT_VECTOR_T2,
    INT_VECTOR_T3,
    INT_VECTOR_T4,  
    INT_VECTOR_T5
};

static halTimerInterruptCallback timerCallback[halTimer_NUM_TIMERS] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};


/*************************************************************************
 *
 *       Arranca el temporitzador
 *
 *       Funcio:
 *           void halTimerStart(
 *               unsigned timer)
 *
 *       Entrada:
 *           timer: Identificador del temporitzador
 *
 *************************************************************************/

void halTimerStart(unsigned timer) {

    PLIB_TMR_Start(timerId[timer]);
}


/*************************************************************************
 *
 *       Para el temporitzador
 *
 *       Funcio:
 *           void halTimerStop(
 *               unsigned timer)
 *
 *       Entrada:
 *           timer: Identificador del temporitzador
 *
 *************************************************************************/

void halTimerStop(unsigned timer) {

    PLIB_TMR_Stop(timerId[timer]);
}


/*************************************************************************
 *
 *       Assigna la funcio callback a la interrupcio del temporitzador
 *
 *       Funcio:
 *          void halTimerSetInterruptCallback(
 *              unsigned timer,
 *              halTimerInterruptCallback callback)
 *
 *      Entrada:
 *          timer   : Identificador del temporitzador
 *          callback: Funcio callback
 *
 *************************************************************************/

void halTimerSetInterruptCallback(unsigned timer,
    halTimerInterruptCallback callback) {

    timerCallback[timer] = callback;
}


/*************************************************************************
 *
 *       Autoritza les interrupcions dels temporitzadors
 *
 *       Funcio:
 *           bool halTimerSetInterruptEnable(
 *               unsigned timer,
 *               bool enabled)
 *
 *       Entrada:
 *           timer  : Identificador del temporitzador
 *           enabled: Autotitzacio true/false
 *
 *       Retorn:
 *           Estat previ
 *
 *************************************************************************/

bool halTimerSetInterruptEnable(
    unsigned timer,
    bool enabled) {

    INT_SOURCE intSource = timerIntSource[timer];
    bool oldEnabled = PLIB_INT_SourceIsEnabled(INT_ID_0, intSource);
    if (oldEnabled != enabled) {
        if (enabled)
            PLIB_INT_SourceEnable(INT_ID_0, intSource);
        else
            PLIB_INT_SourceDisable(INT_ID_0, intSource);
    }

    return oldEnabled;
}


/*************************************************************************
 *
 *       Assigna la mprioritat de les interrupcions de temporitzador
 *
 *       Funcio:
 *           void halTimerSetInterruptPriority(
 *               unsigned timer,
 *               unsigned priority,
 *               unsigned subPriority)
 *
 *       Entrada:
 *           timer      : Identificador del temporitzador
 *           priority   : Prioritat
 *           subPriority: Sub-prioritat
 *
 *************************************************************************/

void halTimerSetInterruptPriority(
    unsigned timer,
    unsigned priority,
    unsigned subPriority) {

    INT_VECTOR intVector = timerIntVector[timer];
    PLIB_INT_VectorPrioritySet(INT_ID_0, intVector, priority);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, intVector, subPriority);
}


/*************************************************************************
 *
 *       Gestiona les interrupcios dels moduls TMR
 *
 *************************************************************************/

void __ISR(_TIMER_1_VECTOR, IPL2SOFT) timerInterruptTMR1(void) {

    if (timerCallback[halTimer_TMR1])
        timerCallback[halTimer_TMR1](halTimer_TMR1);
    PLIB_INT_SourceFlagClear(INT_ID_0, timerIntSource[halTimer_TMR1]);
}

/*void __ISR(_TIMER_2_VECTOR, IPL2SOFT) timerInterruptTMR2(void) {

    if (timerCallback[halTimer_TMR2])
        timerCallback[halTimer_TMR2](halTimer_TMR2);
    PLIB_INT_SourceFlagClear(INT_ID_0, timerIntSource[halTimer_TMR2]);
}*/

void __ISR(_TIMER_3_VECTOR, IPL2SOFT) timerInterruptTMR3(void) {

    if (timerCallback[halTimer_TMR3])
        timerCallback[halTimer_TMR3](halTimer_TMR3);
    PLIB_INT_SourceFlagClear(INT_ID_0, timerIntSource[halTimer_TMR3]);
}

void __ISR(_TIMER_4_VECTOR, IPL2SOFT) timerInterruptTMR4(void) {

    if (timerCallback[halTimer_TMR4])
        timerCallback[halTimer_TMR4](halTimer_TMR4);
    PLIB_INT_SourceFlagClear(INT_ID_0, timerIntSource[halTimer_TMR4]);
}

void __ISR(_TIMER_5_VECTOR, IPL2SOFT) timerInterruptTMR5(void) {

    if (timerCallback[halTimer_TMR5])
        timerCallback[halTimer_TMR5](halTimer_TMR5);
    PLIB_INT_SourceFlagClear(INT_ID_0, timerIntSource[halTimer_TMR5]);
}
