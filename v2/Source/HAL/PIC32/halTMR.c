#include "eos.h"
#include "HAL/PIC32/halTMR.h"
#include "HAL/PIC32/halINT.h"
#include "HAL/PIC32/halSYS.h"
#include "sys/attribs.h"

#include "peripheral/tmr/plib_tmr.h"


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


static const TMR_MODULE_ID timerIdTbl[NUM_TIMERS] = {
#ifdef _TMR1    
    TMR_ID_1,
#endif    
#ifdef _TMR2    
    TMR_ID_2,
#endif
#ifdef _TMR3    
    TMR_ID_3,
#endif
#ifdef _TMR4    
    TMR_ID_4,
#endif
#ifdef _TMR5    
    TMR_ID_5,
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
    
    TMR_MODULE_ID tmrId = timerIdTbl[info->timer];
     
    PLIB_TMR_Stop(tmrId);
    halTMRDisableInterrupt(info->timer);
    
    PLIB_TMR_ClockSourceSelect(tmrId, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(tmrId, prescaleTbl[(info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos]);
    if ((info->options & HAL_TMR_MODE_mask) == HAL_TMR_MODE_16) {
        PLIB_TMR_Mode16BitEnable(tmrId);
        PLIB_TMR_Counter16BitClear(tmrId);
        PLIB_TMR_Period16BitSet(tmrId, info->period);    
    } 
    else if ((info->options & HAL_TMR_MODE_mask) == HAL_TMR_MODE_32) {
        PLIB_TMR_Mode32BitEnable(tmrId);
        PLIB_TMR_Counter32BitClear(tmrId);
        PLIB_TMR_Period32BitSet(tmrId, info->period);            
    }

    if (info->isrFunction != NULL) {       
        callbacks[info->timer].function = info->isrFunction;
        callbacks[info->timer].params = info->isrParams;

        if ((info->options & HAL_TMR_INTERRUPT_mask) == HAL_TMR_INTERRUPT_ENABLE) {
            unsigned state = halINTDisable();
            halTMRSetInterruptPriority(info->timer, info->irqPriority, info->irqSubPriority);
            halTMREnableInterrupt(info->timer);
            halINTRestore(state);
        }
    }
    else {
        callbacks[info->timer].function = NULL;
        callbacks[info->timer].params = NULL;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStartTimer(
    TMRTimer timer) {
    
    PLIB_TMR_Start(timerIdTbl[timer]);    
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStopTimer(
    TMRTimer timer) {
    
    PLIB_TMR_Stop(timerIdTbl[timer]);    
}


/// ----------------------------------------------------------------------
/// \brief   Activa les interrupcions del temporitzador.
/// \param   timer: El identificador del temporitzador.
///
void halTMREnableInterrupt(
    TMRTimer timer) {

    switch (timer) {
        case HAL_TMR_TIMER_1:
            IEC0bits.T1IE = 1;
            break;
            
        case HAL_TMR_TIMER_2:
            IEC0bits.T2IE = 1;
            break;
        
        case HAL_TMR_TIMER_3:
            IEC0bits.T3IE = 1;
            break;
        
        case HAL_TMR_TIMER_4:
            IEC0bits.T4IE = 1;
            break;
        
        case HAL_TMR_TIMER_5:
            IEC0bits.T5IE = 1;
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcions del temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRDisableInterrupt(
    TMRTimer timer) {

    switch (timer) {
        case HAL_TMR_TIMER_1:
            IEC0bits.T1IE = 0;
            break;
            
        case HAL_TMR_TIMER_2:
            IEC0bits.T2IE = 0;
            break;
        
        case HAL_TMR_TIMER_3:
            IEC0bits.T3IE = 0;
            break;
        
        case HAL_TMR_TIMER_4:
            IEC0bits.T4IE = 0;
            break;
        
        case HAL_TMR_TIMER_5:
            IEC0bits.T5IE = 0;
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la prioritaty der la interrupcio.
/// \param    timer: El identificador del temporitzador.
/// \param    priority: Prioritat.
/// \param    subPriority: Sub prioritat.
///
void halTMRSetInterruptPriority(
    TMRTimer timer,
    unsigned priority, 
    unsigned subPriority) {
       
    switch (timer) {
        case HAL_TMR_TIMER_1:
            IPC1bits.T1IP = priority;
            IPC1bits.T1IS = subPriority;
            break;

        case HAL_TMR_TIMER_2:
            IPC2bits.T2IP = priority;
            IPC2bits.T2IS = subPriority;
            break;

        case HAL_TMR_TIMER_3:
            IPC3bits.T3IP = priority;
            IPC3bits.T3IS = subPriority;
            break;

        case HAL_TMR_TIMER_4:
            IPC4bits.T4IP = priority;
            IPC4bits.T4IS = subPriority;
            break;

        case HAL_TMR_TIMER_5:
            IPC5bits.T5IP = priority;
            IPC5bits.T5IS = subPriority;
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Obte el flag d'interrupcio del temporitzador.
/// \param    timer: El identificador del temporitzador.
/// \return   El valor del flag.
///
bool halTMRGetInterruptFlag(
    TMRTimer timer) {
    
    switch (timer) {
        case HAL_TMR_TIMER_1:
            return IFS0bits.T1IF;
            
        case HAL_TMR_TIMER_2:
            return IFS0bits.T2IF;
        
        case HAL_TMR_TIMER_3:
            return IFS0bits.T3IF;
        
        case HAL_TMR_TIMER_4:
            return IFS0bits.T4IF;
        
        case HAL_TMR_TIMER_5:
            return IFS0bits.T5IF;
            
        default:
            return false;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag d'interrupcio del temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRClearInterruptFlag(
    TMRTimer timer) {
    
    switch (timer) {
        case HAL_TMR_TIMER_1:
            IFS0bits.T1IF = 0;
            break;
            
        case HAL_TMR_TIMER_2:
            IFS0bits.T2IF = 0;
            break;
        
        case HAL_TMR_TIMER_3:
            IFS0bits.T3IF = 0;
            break;
        
        case HAL_TMR_TIMER_4:
            IFS0bits.T4IF = 0;
            break;
        
        case HAL_TMR_TIMER_5:
            IFS0bits.T5IF = 0;
            break;
    }
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

    if (IFS0bits.T1IF) {
        invokeCallback(HAL_TMR_TIMER_1);
        IFS0bits.T1IF = 0;
    }
}
#endif

#ifdef _TMR2
void isrTMR2Handler(void) {

    if (IFS0bits.T2IF) {
        invokeCallback(HAL_TMR_TIMER_2);
        IFS0bits.T2IF = 0;
    }
}
#endif            

#ifdef _TMR3
void isrTMR3Handler(void) {

    if (IFS0bits.T3IF) {
        invokeCallback(HAL_TMR_TIMER_3);
        IFS0bits.T3IF = 0;
    }
}
#endif            

#ifdef _TMR4
void isrTMR4Handler(void) {

    if (IFS0bits.T4IF) {
        invokeCallback(HAL_TMR_TIMER_4);
        IFS0bits.T4IF = 0;
    }
}
#endif            

#ifdef _TMR5
void isrTMR5Handler(void) {

    if (IFS0bits.T5IF) {
        invokeCallback(HAL_TMR_TIMER_5);
        IFS0bits.T5IF = 0;
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
