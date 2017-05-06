#include "HAL/halTMR.h"
#include "HAL/PIC32/halINT.h"

#include "sys/attribs.h"

#include "xc.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


typedef struct {
    TMR_MODULE_ID tmrId;
    INT_SOURCE intSource;
    INT_VECTOR intVector;
    unsigned intCoreVector;
} TimerInfo;


#if defined(_TMR5)
#elif defined (_TMR4)
#elif defined (_TMR3)
#elif defined (_TMR2)
#elif defined (_TMR1)
#else
#error No hay modulos TMRx en esta CPU
#endif

#define NUM_TIMERS TMR_NUMBER_OF_MODULES


static const TimerInfo timerInfoTbl[NUM_TIMERS] = {
#ifdef _TMR1    
    { TMR_ID_1, INT_SOURCE_TIMER_1, INT_VECTOR_T1, _TIMER_1_VECTOR },
#endif    
#ifdef _TMR2    
    { TMR_ID_2, INT_SOURCE_TIMER_2, INT_VECTOR_T2, _TIMER_2_VECTOR },
#endif
#ifdef _TMR3    
    { TMR_ID_3, INT_SOURCE_TIMER_3, INT_VECTOR_T3, _TIMER_3_VECTOR },
#endif
#ifdef _TMR4    
    { TMR_ID_4, INT_SOURCE_TIMER_4, INT_VECTOR_T4, _TIMER_4_VECTOR },
#endif
#ifdef _TMR5    
    { TMR_ID_5, INT_SOURCE_TIMER_5, INT_VECTOR_T5, _TIMER_5_VECTOR },
#endif
};

static const TMR_PRESCALE prescaleTbl[8] = {
    TMR_PRESCALE_VALUE_1,
    TMR_PRESCALE_VALUE_2,
    TMR_PRESCALE_VALUE_4,
    TMR_PRESCALE_VALUE_8,
    TMR_PRESCALE_VALUE_16,
    TMR_PRESCALE_VALUE_32,
    TMR_PRESCALE_VALUE_64,
    TMR_PRESCALE_VALUE_256
};

static const INT_PRIORITY_LEVEL intPriority = INT_PRIORITY_LEVEL2;
static const INT_SUBPRIORITY_LEVEL intSubPriority = INT_SUBPRIORITY_LEVEL0;

static TMRInterruptCallback callbacks[NUM_TIMERS];
static void *params[NUM_TIMERS];

#if defined(_TMR1) && (HAL_TMR_USE_T1_INTERRUPT == 1)
extern void __ISR(_TIMER_1_VECTOR, IPL2SOFT) isrTMR1Wrapper(void);
#endif
#if defined(_TMR2) && (HAL_TMR_USE_T2_INTERRUPT == 1)
extern void __ISR(_TIMER_2_VECTOR, IPL2SOFT) isrTMR2Wrapper(void);
#endif
#if defined(_TMR3) && (HAL_TMR_USE_T3_INTERRUPT == 1)
extern void __ISR(_TIMER_3_VECTOR, IPL2SOFT) isrTMR3Wrapper(void);
#endif
#if defined(_TMR4) && (HAL_TMR_USE_T4_INTERRUPT == 1)
extern void __ISR(_TIMER_4_VECTOR, IPL2SOFT) isrTMR4Wrapper(void);
#endif
#if defined(_TMR5) && (HAL_TMR_USE_T5_INTERRUPT == 1)
extern void __ISR(_TIMER_5_VECTOR, IPL2SOFT) isrTMR5Wrapper(void);
#endif


/// ----------------------------------------------------------------------
/// \brief Inicialitza les interrupcions per un temporitzador.
/// \param timer: El identificador del temporitzador.
/// \param mode: Modus 16 o 32 bits
/// \param prescale: Divisor d'entrada
/// \param period: Periode
/// \param callback: Funcio per procesar la interrupcio.
/// \param param: Parametre de la funcio callback.
///
void halTMRInitializeTimer(
    uint8_t timer, 
    uint8_t mode,
    uint8_t prescale,
    unsigned period,
    TMRInterruptCallback callback, 
    void *param) {
    
    const TimerInfo *ti = &timerInfoTbl[timer];
    
    PLIB_TMR_Stop(ti->tmrId);
    PLIB_TMR_ClockSourceSelect(ti->tmrId, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(ti->tmrId, prescaleTbl[prescale & 0x07]);
    if (mode == HAL_TMR_MODE16) {
        PLIB_TMR_Mode16BitEnable(ti->tmrId);
        PLIB_TMR_Counter16BitClear(ti->tmrId);
        PLIB_TMR_Period16BitSet(ti->tmrId, period);    
    } 
    else if (mode == HAL_TMR_MODE32) {
        PLIB_TMR_Mode32BitEnable(ti->tmrId);
        PLIB_TMR_Counter32BitClear(ti->tmrId);
        PLIB_TMR_Period32BitSet(ti->tmrId, period);            
    }

    callbacks[timer] = callback;
    if (callback != NULL) {
        params[timer] = param;

        halINTDisableInterrupts();
        
        PLIB_INT_VectorPrioritySet(INT_ID_0, ti->intVector, intPriority);
        PLIB_INT_VectorSubPrioritySet(INT_ID_0, ti->intVector, intSubPriority);    

        PLIB_INT_SourceFlagClear(INT_ID_0, ti->intSource);
        PLIB_INT_SourceEnable(INT_ID_0, ti->intSource);
        
        halINTEnableInterrupts();
    }
}


/// ----------------------------------------------------------------------
/// \brief Inicia el temporitzador.
/// \param timer: El identificador del temporitzador.
///
void halTMRStartTimer(
    uint8_t timer) {
    
    const TimerInfo *ti = &timerInfoTbl[timer];
    PLIB_TMR_Start(ti->tmrId);    
}


/// ----------------------------------------------------------------------
/// \brief Para el temporitzador.
/// \param timer: El identificador del temporitzador.
///
void halTMRStopTimer(
    uint8_t timer) {
    
    const TimerInfo *ti = &timerInfoTbl[timer];
    PLIB_TMR_Stop(ti->tmrId);    
}


/// ----------------------------------------------------------------------
/// \brief Funcio callback de la interrupcio.
/// \param timer: El identificador del temporitzador.
///
static void doCallback(
    uint8_t timer) {
    
    TMRInterruptCallback callback = callbacks[timer];
    if (callback != NULL)
        callback(timer, params[timer]);
}


/*************************************************************************
 *
 *       Funcions ISR del modul TMR (Hi una per cada modul)
 * 
 *       Funcio:
 *          void isrTMRxHandler(void)
 *
 *************************************************************************/

#ifdef _TMR1
void isrTMR1Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_1)) {
        doCallback(HAL_TMR_T1);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_1);
    }
}
#endif

#ifdef _TMR2
void isrTMR2Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_2)) {
        doCallback(HAL_TMR_T2); 
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_2);
    }
}
#endif            

#ifdef _TMR3
void isrTMR3Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_3)) {
        doCallback(HAL_TMR_T3);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_3);
    }
}
#endif            

#ifdef _TMR4
void isrTMR4Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_4)) {
        doCallback(HAL_TMR_T4);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_4);
    }
}
#endif            

#ifdef _TMR5
void isrTMR5Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_5)) {
        doCallback(HAL_TMR_T5);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_5);
    }
}
#endif            


/// ----------------------------------------------------------------------
/// \brief Retard en milisegons.
/// \param time: Temps en milisegons.
///
void halTMRDelay(
    unsigned time) {
    
    unsigned startCount = _CP0_GET_COUNT();
    unsigned endCount = startCount + time * (80000000ul / 2000ul);
    
    if (endCount >= startCount) 
        while (_CP0_GET_COUNT() < endCount);
    
    else {
        while (_CP0_GET_COUNT() > startCount);
        while (_CP0_GET_COUNT() < endCount);
    }    
}
