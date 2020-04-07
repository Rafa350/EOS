#include "eos.h"
#include "HAL/PIC32/halTMR.h"
#include "HAL/PIC32/halINT.h"
#include "HAL/PIC32/halSYS.h"
#include "sys/attribs.h"

#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


typedef struct {
    TMR_MODULE_ID tmrId;
    INT_SOURCE intSource;
    INT_VECTOR intVector;
} TimerInfo;

typedef struct {
    TMRInterruptFunction function;
    void* params;
} CallbackInfo;


#if defined(_TMR5)
#elif defined (_TMR4)
#elif defined (_TMR3)
#elif defined (_TMR2)
#elif defined (_TMR1)
#else
    //#error No hay modulos TMRx en esta CPU
#endif

#define NUM_TIMERS TMR_NUMBER_OF_MODULES


static const TimerInfo timerInfoTbl[NUM_TIMERS] = {
#ifdef _TMR1    
    { TMR_ID_1, INT_SOURCE_TIMER_1, INT_VECTOR_T1 },
#endif    
#ifdef _TMR2    
    { TMR_ID_2, INT_SOURCE_TIMER_2, INT_VECTOR_T2 },
#endif
#ifdef _TMR3    
    { TMR_ID_3, INT_SOURCE_TIMER_3, INT_VECTOR_T3 },
#endif
#ifdef _TMR4    
    { TMR_ID_4, INT_SOURCE_TIMER_4, INT_VECTOR_T4 },
#endif
#ifdef _TMR5    
    { TMR_ID_5, INT_SOURCE_TIMER_5, INT_VECTOR_T5 },
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

static CallbackInfo callbacks[NUM_TIMERS];

#if defined(_TMR1) && (HAL_TMR_USE_T1_INTERRUPT == 1)
extern void __ISR(_TIMER_1_VECTOR, IPL2SOFT) isrTMR1Wrapper(void);
#endif
#if defined(_TMR2) && defined(HAL_TMR_USE_T2_INTERRUPT)
extern void __ISR(_TIMER_2_VECTOR, IPL2SOFT) isrTMR2Wrapper(void);
#endif
#if defined(_TMR3) && defined(HAL_TMR_USE_T3_INTERRUPT)
extern void __ISR(_TIMER_3_VECTOR, IPL2SOFT) isrTMR3Wrapper(void);
#endif
#if defined(_TMR4) && defined(HAL_TMR_USE_T4_INTERRUPT)
extern void __ISR(_TIMER_4_VECTOR, IPL2SOFT) isrTMR4Wrapper(void);
#endif
#if defined(_TMR5) && defined(HAL_TMR_USE_T5_INTERRUPT)
extern void __ISR(_TIMER_5_VECTOR, IPL2SOFT) isrTMR5Wrapper(void);
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el temporitzador.
/// \param    info: Parametres d'inicialitzacio.
///
void halTMRInitialize(
    const TMRInitializeInfo* info) {
    
    const TimerInfo* ti = &timerInfoTbl[info->timer];
     
    PLIB_TMR_Stop(ti->tmrId);
    PLIB_TMR_ClockSourceSelect(ti->tmrId, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(ti->tmrId, prescaleTbl[(info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos]);
    if ((info->options & HAL_TMR_MODE_mask) == HAL_TMR_MODE_16) {
        PLIB_TMR_Mode16BitEnable(ti->tmrId);
        PLIB_TMR_Counter16BitClear(ti->tmrId);
        PLIB_TMR_Period16BitSet(ti->tmrId, info->period);    
    } 
    else if ((info->options & HAL_TMR_MODE_mask) == HAL_TMR_MODE_32) {
        PLIB_TMR_Mode32BitEnable(ti->tmrId);
        PLIB_TMR_Counter32BitClear(ti->tmrId);
        PLIB_TMR_Period32BitSet(ti->tmrId, info->period);            
    }

    if (((info->options & HAL_TMR_INTERRUPT_mask) == HAL_TMR_INTERRUPT_ENABLE) &&
        (info->isrFunction != NULL)) {
        
        callbacks[info->timer].function = info->isrFunction;
        callbacks[info->timer].params = info->isrParams;

        halINTDisableInterrupts();

        PLIB_INT_VectorPrioritySet(INT_ID_0, ti->intVector, intPriority);
        PLIB_INT_VectorSubPrioritySet(INT_ID_0, ti->intVector, intSubPriority);    

        PLIB_INT_SourceFlagClear(INT_ID_0, ti->intSource);
        PLIB_INT_SourceEnable(INT_ID_0, ti->intSource);

        halINTEnableInterrupts();
    }
    else
        callbacks[info->timer].function = NULL;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStartTimer(
    TMRTimer timer) {
    
    const TimerInfo *ti = &timerInfoTbl[timer];
    PLIB_TMR_Start(ti->tmrId);    
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStopTimer(
    TMRTimer timer) {
    
    const TimerInfo *ti = &timerInfoTbl[timer];
    PLIB_TMR_Stop(ti->tmrId);    
}


/// ----------------------------------------------------------------------
/// \brief    Funcio callback de la interrupcio.
/// \param    timer: El identificador del temporitzador.
///
static void invokeCallback(
    TMRTimer timer) {
    
    TMRInterruptFunction function = callbacks[timer].function;
    if (function != NULL)
        function(timer, callbacks[timer].params);
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
        invokeCallback(HAL_TMR_TIMER_1);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_1);
    }
}
#endif

#ifdef _TMR2
void isrTMR2Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_2)) {
        invokeCallback(HAL_TMR_TIMER_2); 
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_2);
    }
}
#endif            

#ifdef _TMR3
void isrTMR3Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_3)) {
        invokeCallback(HAL_TMR_TIMER_3);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_3);
    }
}
#endif            

#ifdef _TMR4
void isrTMR4Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_4)) {
        invokeCallback(HAL_TMR_TIMER_4);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_4);
    }
}
#endif            

#ifdef _TMR5
void isrTMR5Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_5)) {
        invokeCallback(HAL_TMR_TIMER_5);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_5);
    }
}
#endif            


/// ----------------------------------------------------------------------
/// \brief    Retard en milisegons.
/// \param    time: Temps en milisegons.
///
void halTMRDelay(
    unsigned time) {
    
    int startCount = _CP0_GET_COUNT();
    int endCount = startCount + ((int)time) * (halSYSGetSystemClockFrequency() / 2000);
    
    if (endCount >= startCount) 
        while (_CP0_GET_COUNT() < endCount);
    
    else {
        while (_CP0_GET_COUNT() > startCount);
        while (_CP0_GET_COUNT() < endCount);
    }    
}
