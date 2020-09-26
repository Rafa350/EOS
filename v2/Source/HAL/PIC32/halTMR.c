#include "eos.h"
#include "HAL/PIC32/halTMR.h"
#include "HAL/PIC32/halINT.h"
#include "HAL/PIC32/halSYS.h"
#include "sys/attribs.h"


typedef struct {
    TMRInterruptFunction function;
    void* params;
} CallbackInfo;

static CallbackInfo callbacks[HAL_TMR_TIMER_MAX];

static INTSource irqTbl[] = {
    HAL_INT_SOURCE_TMR1,
    HAL_INT_SOURCE_TMR2,
    HAL_INT_SOURCE_TMR3,
    HAL_INT_SOURCE_TMR4,
    HAL_INT_SOURCE_TMR5
};


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
    
    halTMRDisableInterrupt(info->timer);

    // Contigura el timer de tipus A
    //
    if (IsTypeA(info->timer)) {
        
        TMRTypeARegisters* tmr = halTMRGetTypeARegisterPtr(info->timer);

        tmr->TxCON.ON = 0;    // Desactiva el timer
        tmr->TxCON.TCS = 0;   // Clock source interna.
        switch((info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos) {
            case HAL_TMR_CLKDIV_8:
                tmr->TxCON.TCKPS = 1;    
                break;

            case HAL_TMR_CLKDIV_64:
                tmr->TxCON.TCKPS = 2;    
                break;

            case HAL_TMR_CLKDIV_256:
                tmr->TxCON.TCKPS = 3;    
                break;
                
            default:
                tmr->TxCON.TCKPS = 0;    
                break;
        }
        tmr->TMRx = 0;
        tmr->PRx = info->period & 0xFFFF;
    }
    
    // Configura el timer de tipus B
    //
    else {
        
        TMRTypeBRegisters* tmr = halTMRGetTypeBRegisterPtr(info->timer);

        tmr->TxCON.ON = 0;    // Desactiva el timer
#if defined(__32MX460F512L__)        
        tmr->TxCON.TCS = 0;   // Clock source interna.
#endif        
        tmr->TxCON.TCKPS = (info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos;    

        if ((info->options & HAL_TMR_MODE_mask) == HAL_TMR_MODE_16) {
            tmr->TxCON.T32 = 0;
            tmr->TMRx = 0;
            tmr->PRx = info->period & 0xFFFF;
        } 
        else if ((info->options & HAL_TMR_MODE_mask) == HAL_TMR_MODE_32) {
            TMRTypeBRegisters* tmrHi = halTMRGetTypeBRegisterHiPtr(info->timer);
            tmr->TxCON.T32 = 1;
            tmr->TMRx = 0;
            tmrHi->TMRx = 0;
            tmr->PRx = info->period & 0xFFFF;
            tmrHi->PRx = (info->period >> 16) & 0xFFFF;
        }
    }
    
    // Configura les interrupcions
    //
    if (info->isrFunction != NULL) {       
        halTMRSetInterruptFunction(info->timer, info->isrFunction, info->isrParams);

        if ((info->options & HAL_TMR_INTERRUPT_mask) == HAL_TMR_INTERRUPT_ENABLE) {
            halTMRSetInterruptPriority(info->timer, info->irqPriority, info->irqSubPriority);
            halTMREnableInterrupt(info->timer);
        }
    }
    else
        halTMRSetInterruptFunction(info->timer, NULL, NULL);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStartTimer(
    TMRTimer timer) {
    
    if (IsTypeA(timer)) {
        TMRTypeARegisters* tmr = halTMRGetTypeARegisterPtr(timer);
        tmr->TxCON.ON = 1;
    }
    else {
        TMRTypeBRegisters* tmr = halTMRGetTypeBRegisterPtr(timer);
        tmr->TxCON.ON = 1;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStopTimer(
    TMRTimer timer) {
    
    if (IsTypeA(timer)) {
        TMRTypeARegisters* tmr = halTMRGetTypeARegisterPtr(timer);
        tmr->TxCON.ON = 0;
    }
    else {
        TMRTypeBRegisters* tmr = halTMRGetTypeBRegisterPtr(timer);
        tmr->TxCON.ON = 0;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la funcio d'interrupcio.
/// \param    timer: El identificador del temporitzador.
/// \param    function: La funcio.
/// \param    params: Els parametres de la funcio.
///
void halTMRSetInterruptFunction(
    TMRTimer timer,
    TMRInterruptFunction function,
    void* params) {
    
    callbacks[timer].function = function;
    callbacks[timer].params = params;
}


/// ----------------------------------------------------------------------
/// \brief   Activa les interrupcions del temporitzador.
/// \param   timer: El identificador del temporitzador.
///
void halTMREnableInterrupt(
    TMRTimer timer) {
    
    halINTEnableInterrupt(irqTbl[timer]);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcions del temporitzador.
/// \param    timer: El identificador del temporitzador.
/// \return   True si previament estava activada.
///
bool halTMRDisableInterrupt(
    TMRTimer timer) {
    
    return halINTDisableInterrupt(irqTbl[timer]);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la prioritaty de la interrupcio.
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
    
    return halINTGetInterruptFlag(irqTbl[timer]);
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag d'interrupcio del temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRClearInterruptFlag(
    TMRTimer timer) {
    
    halINTClearInterruptFlag(irqTbl[timer]);
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
