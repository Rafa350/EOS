#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halTMR.h"
#include "HAL/PIC32/halSYS.h"


#define __getRegisterPtr(timer)        ((TMRRegisters*)(_TMR1_BASE_ADDRESS + (timer * 0x00000200)))

#define __isTypeA(handler)             ((uint32_t) handler->regs == _TMR1_BASE_ADDRESS)
#define __is32Bits(handler)            (handler->regs->TBxCON.T32 == 1)

#define __getRegs16Ptr(handler)        handler->regs
#define __getRegs32Ptr(handler)        ((TMRRegisters*)((uint32_t) handler->regs + 0x00000200))


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el temporitzador.
/// \param    data: Buffer de dades del temporitzador.
/// \param    info: Parametres d'inicialitzacio.
/// \return   El handler del temporitzador.
/// \remarks  El temporitzador queda configurat, pero no genera 
///           interrupcions, i esta parat.
///
TMRHandler halTMRInitialize(
    TMRData* data,
    const TMRInitializeInfo* info) {
    
    // Inicialitza el handler
    //
    TMRHandler handler = data;
    handler->regs = __getRegisterPtr(info->timer);
    
    // Desactiva les interrupcions del temporitzador
    //
    halTMRDisableInterruptSource(handler);

    // Configura el timer de tipus A
    //
    if (__isTypeA(handler)) {
        
        handler->regs->TAxCON.ON = 0;    // Desactiva el timer
        handler->regs->TAxCON.TCS = 0;   // Clock source interna.
        switch((info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos) {
            case HAL_TMR_CLKDIV_8:
                handler->regs->TAxCON.TCKPS = 1;    
                break;

            case HAL_TMR_CLKDIV_64:
                handler->regs->TAxCON.TCKPS = 2;    
                break;

            case HAL_TMR_CLKDIV_256:
                handler->regs->TAxCON.TCKPS = 3;    
                break;
                
            default:
                handler->regs->TAxCON.TCKPS = 0;    
                break;
        }
    }
    
    // Configura el timer de tipus B
    //
    else {
        
        handler->regs->TBxCON.ON = 0;    // Desactiva el timer
#if defined(__32MX460F512L__)        
        handler->regs->TBxCON.TCS = 0;   // Clock source interna.
#endif        
        handler->regs->TBxCON.TCKPS = (info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos;    
        handler->regs->TBxCON.T32 = (info->options & HAL_TMR_MODE_mask) == HAL_TMR_MODE_32;
    }

    halTMRSetCounter(handler, 0);
    halTMRSetPeriod(handler, info->period);
    
    handler->isrFunction = NULL;
    
    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el temporitzador
/// \param    handler: Handler del temporitzador.
///
void halTMRShutdown(
    TMRHandler handler) {
    
    halTMRStopTimer(handler);
    halTMRDisableInterruptSource(handler); 
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el contador.
/// \param    period: El valor del contador.
///
void halTMRSetCounter(
    TMRHandler handler, 
    uint32_t counter) {
    
    eosAssert(handler != NULL);
    
    if (!__isTypeA(handler) && __is32Bits(handler)) {
        TMRRegisters* regs32 = __getRegs32Ptr(handler);
        regs32->TMRx = (counter >> 16) & 0xFFFF;
    }
    handler->regs->TMRx = counter & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode.
/// \param    period: El valor del periode.
///
void halTMRSetPeriod(
    TMRHandler handler, 
    uint32_t period) {
    
    eosAssert(handler != NULL);
    
    if (!__isTypeA(handler) && __is32Bits(handler)) {
        TMRRegisters* regs32 = __getRegs32Ptr(handler);
        regs32->PRx = (period >> 16) & 0xFFFF;
    }
    handler->regs->PRx = period & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    handler: Handler del temporitzador
/// \remarks  El temporitzador comença a contar i genera interrupcions, si 
///           estan activades.
///
void halTMRStartTimer(
    TMRHandler handler) {
    
    if (__isTypeA(handler))
        handler->regs->TAxCON.ON = 1;
    else 
        handler->regs->TBxCON.ON = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    handler: Handler del temporitzador.
/// \remarks  El contador deixa de contar.
///
void halTMRStopTimer(
    TMRHandler handler) {
    
    if (__isTypeA(handler))
        handler->regs->TAxCON.ON = 0;
    else 
        handler->regs->TBxCON.ON = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la funcio d'interrupcio.
/// \param    handler: El handler del temporitzador.
/// \param    function: La funcio.
/// \param    params: Els parametres.
///
void halTMRSetInterruptFunction(
    TMRHandler handler,
    TMRInterruptFunction function,
    void* params) {
    
    eosAssert(handler != NULL);
    
    handler->isrFunction = function;
    handler->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief   Activa les interrupcions del temporitzador.
/// \param   handler: El handler del temporitzador.
///
void halTMREnableInterruptSource(
    TMRHandler handler) {
    
    switch ((uint32_t) handler->regs) {
#ifdef _TMR1
        case _TMR1_BASE_ADDRESS:
            IEC0bits.T1IE = 1;
            break;
#endif            

#ifdef _TMR2
        case _TMR2_BASE_ADDRESS:
            IEC0bits.T2IE = 1;
            break;
#endif            

#ifdef _TMR3
        case _TMR3_BASE_ADDRESS:
            IEC0bits.T3IE = 1;
            break;
#endif            

#ifdef _TMR4
        case _TMR4_BASE_ADDRESS:
            IEC0bits.T4IE = 1;
            break;
#endif            

#ifdef _TMR5
        case _TMR5_BASE_ADDRESS:
            IEC0bits.T5IE = 1;
            break;
#endif            
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcions del temporitzador.
/// \param    timer: El identificador del modul.
/// \return   Diferent de zero si previament estava activada.
///
uint32_t halTMRDisableInterruptSource(
    TMRHandler handler) {
    
    uint32_t state = false;
    
    switch ((uint32_t) handler->regs) {
#ifdef _TMR1
        case _TMR1_BASE_ADDRESS:
            state = IEC0bits.T1IE;
            IEC0bits.T1IE = 0;
            break;
#endif            

#ifdef _TMR2
        case _TMR2_BASE_ADDRESS:
            state = IEC0bits.T1IE;
            IEC0bits.T2IE = 0;
            break;
#endif            

#ifdef _TMR3
        case _TMR3_BASE_ADDRESS:
            state = IEC0bits.T1IE;
            IEC0bits.T3IE = 0;
            break;
#endif            

#ifdef _TMR4
        case _TMR4_BASE_ADDRESS:
            state = IEC0bits.T1IE;
            IEC0bits.T4IE = 0;
            break;
#endif            

#ifdef _TMR5
        case _TMR5_BASE_ADDRESS:
            state = IEC0bits.T1IE;
            IEC0bits.T5IE = 0;
            break;
#endif            
    }
    
    return state;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el flag d'interrupcio del temporitzador.
/// \param    timer: El identificador del modul.
/// \param    event: El indicador del event.
/// \return   El valor del flag.
///
bool halTMRGetInterruptSourceFlag(
    TMRHandler handler) {
    
    switch ((uint32_t) handler->regs) {
#ifdef _TMR1
        case _TMR1_BASE_ADDRESS:
            return __halTMRGetTMR1InterruptSourceFlag();
#endif            

#ifdef _TMR2
        case _TMR2_BASE_ADDRESS:
            return __halTMRGetTMR2InterruptSourceFlag();
#endif            

#ifdef _TMR3
        case _TMR3_BASE_ADDRESS:
            return __halTMRGetTMR3InterruptSourceFlag();
#endif            

#ifdef _TMR4
        case _TMR4_BASE_ADDRESS:
            return __halTMRGetTMR4InterruptSourceFlag();
#endif            

#ifdef _TMR5
        case _TMR5_BASE_ADDRESS:
            return __halTMRGetTMR5InterruptSourceFlag();
#endif            
            
        default:
            return false;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag d'interrupcio del temporitzador.
/// \param    tmrId: El identificador del modul.
///
void halTMRClearInterruptSourceFlag(
    TMRHandler handler) {
    
    switch ((uint32_t) handler->regs) {
#ifdef _TMR1
        case _TMR1_BASE_ADDRESS:
            __halTMRClearTMR1InterruptSourceFlag();
            break;
#endif            

#ifdef _TMR2
        case _TMR2_BASE_ADDRESS:
            __halTMRClearTMR2InterruptSourceFlag();
            break;
#endif            

#ifdef _TMR3
        case _TMR3_BASE_ADDRESS:
            __halTMRClearTMR3InterruptSourceFlag();
            break;
#endif            

#ifdef _TMR4
        case _TMR4_BASE_ADDRESS:
            __halTMRClearTMR4InterruptSourceFlag();
            break;
#endif            

#ifdef _TMR5
        case _TMR5_BASE_ADDRESS:
            __halTMRClearTMR5InterruptSourceFlag();
            break;
#endif            
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio.
/// \param    handler: El temporitzador.
///
void halTMRInterruptHandler(
    TMRHandler handler) {
    
    if (halTMRGetInterruptSourceFlag(handler)) {
        if (handler->isrFunction != NULL)
            handler->isrFunction(handler, handler->isrParams);
        halTMRClearInterruptSourceFlag(handler);
    }
}


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
