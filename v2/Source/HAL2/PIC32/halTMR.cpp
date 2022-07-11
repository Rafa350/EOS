#include "HAL2/hal.h"
#include "HAL2/PIC32/halTMR.h"


using namespace hal;


typedef struct  __attribute__((packed , aligned(4))) {
    union {
        __T1CONbits_t TAxCON;
        __T2CONbits_t TBxCON;
    };
    volatile uint32_t TxCONCLR;
    volatile uint32_t TxCONSET;
    volatile uint32_t TxCONINV;
    volatile uint32_t TMRx;
    volatile uint32_t TMRxCLR;
    volatile uint32_t TMRxSET;
    volatile uint32_t TMRxINV;
    volatile uint32_t PRx;
    volatile uint32_t PRxCLR;
    volatile uint32_t PRxSET;
    volatile uint32_t PRxINV;
} TMR_Registers;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    timer: Identificador del temporitzador.
///
TMR::TMR(
    Timer timer) {

    _addr = _TMR1_BASE_ADDRESS + (static_cast<unsigned>(timer) * 0x200);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    tmr: L'objecte a copiar.
///
TMR::TMR(
    const TMR &tmr):

    _addr(tmr._addr) {

}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el divisor.
/// \param    divider: Divisor del rellotge.
///
void TMR::setClockDivider(
    ClockDivider divider) {

    TMR_Registers *regs = reinterpret_cast<TMR_Registers*>(_addr);

    if (_addr == _TMR1_BASE_ADDRESS) {
        switch (divider) {
            case ClockDivider::div8:
                regs->TAxCON.TCKPS = 1;
                break;

            case ClockDivider::div64:
                regs->TAxCON.TCKPS = 2;
                break;

            case ClockDivider::div256:
                regs->TAxCON.TCKPS = 3;
                break;

            default:
                regs->TAxCON.TCKPS = 0;
                break;
        }
    }

    else {
        switch (divider) {
            case ClockDivider::div1:
                regs->TBxCON.TCKPS = 0;
                break;

            case ClockDivider::div2:
                regs->TBxCON.TCKPS = 1;
                break;

            case ClockDivider::div4:
                regs->TBxCON.TCKPS = 2;
                break;

            case ClockDivider::div8:
                regs->TBxCON.TCKPS = 3;
                break;

            case ClockDivider::div16:
                regs->TBxCON.TCKPS = 4;
                break;

            case ClockDivider::div32:
                regs->TBxCON.TCKPS = 5;
                break;

            case ClockDivider::div64:
                regs->TBxCON.TCKPS = 6;
                break;

            case ClockDivider::div256:
                regs->TBxCON.TCKPS = 7;
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la font.
/// \param    source: La font.
///
void TMR::setClockSource(
    ClockSource source) {

    TMR_Registers *regs = reinterpret_cast<TMR_Registers*>(_addr);

    if (_addr == _TMR1_BASE_ADDRESS)
        regs->TAxCON.TCS = 0;
    else
        regs->TBxCON.TCS = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la resolucio del contador.
/// \param    resolution: La resulucio.
///
void TMR::setResolution(
    Resolution resolution) {

    TMR_Registers *regs = reinterpret_cast<TMR_Registers*>(_addr);

    if (_addr != _TMR1_BASE_ADDRESS)
        regs->TBxCON.T32 = resolution == Resolution::res32;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el contador.
/// \param    period: El valor del contador.
///
void TMR::setCounter(
    uint32_t counter) {

    TMR_Registers *regs = reinterpret_cast<TMR_Registers*>(_addr);

    if ((_addr != _TMR1_BASE_ADDRESS) && (regs->TBxCON.T32 == 1)) {

        TMR_Registers *regs32 = reinterpret_cast<TMR_Registers*>(_addr + 0x200);
        regs32->TMRx = (counter >> 16) & 0xFFFF;
    }
    regs->TMRx = counter & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode.
/// \param    period: El valor del periode.
///
void TMR::setPeriod(
    uint32_t period) {

    TMR_Registers *regs = reinterpret_cast<TMR_Registers*>(_addr);

    if ((_addr != _TMR1_BASE_ADDRESS) && (regs->TBxCON.T32 == 1)) {

        TMR_Registers *regs32 = reinterpret_cast<TMR_Registers*>(_addr + 0x200);
        regs32->PRx = (period >> 16) & 0xFFFF;
    }
    regs->PRx = period & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador.
///
void TMR::start() {

    TMR_Registers *regs = reinterpret_cast<TMR_Registers*>(_addr);

    if (_addr == _TMR1_BASE_ADDRESS)
        regs->TAxCON.ON = 1;
    else
        regs->TBxCON.ON = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Para el contador.
///
void TMR::stop() {

    TMR_Registers *regs = reinterpret_cast<TMR_Registers*>(_addr);

    if (_addr == _TMR1_BASE_ADDRESS)
        regs->TAxCON.ON = 0;
    else
        regs->TBxCON.ON = 0;
}


/// ----------------------------------------------------------------------
/// \brief   Activa les interrupcions del temporitzador.
/// \param   event: El event a activar.
///
void TMR::enableInterrupt(
    InterruptEvent event) {

    if (event == InterruptEvent::update)
        switch (_addr) {
            case _TMR1_BASE_ADDRESS:
                IEC0bits.T1IE = 1;
                break;

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
/// \param    event: El event a desactivar.
/// \return   True si previament estava activada.
///
bool TMR::disableInterrupt(
    InterruptEvent event) {

    bool state = false;

    if (event == InterruptEvent::update)
        switch (_addr) {
            case _TMR1_BASE_ADDRESS:
                state = IEC0bits.T1IE;
                IEC0bits.T1IE = 0;
                break;

            #ifdef _TMR2
            case _TMR2_BASE_ADDRESS:
                state = IEC0bits.T2IE;
                IEC0bits.T2IE = 0;
                break;
            #endif

            #ifdef _TMR3
            case _TMR3_BASE_ADDRESS:
                state = IEC0bits.T3IE;
                IEC0bits.T3IE = 0;
                break;
            #endif

            #ifdef _TMR4
            case _TMR4_BASE_ADDRESS:
                state = IEC0bits.T4IE;
                IEC0bits.T4IE = 0;
                break;
            #endif

            #ifdef _TMR5
            case _TMR5_BASE_ADDRESS:
                state = IEC0bits.T5IE;
                IEC0bits.T5IE = 0;
                break;
            #endif
        }

    return state;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el flag d'interrupcio del temporitzador.
/// \param    event: El event.
/// \return   El valor del flag.
///
bool TMR::getInterruptFlag(
    InterruptEvent event) {

    bool state = false;

    if (event == InterruptEvent::update)
        switch (_addr) {
            case _TMR1_BASE_ADDRESS:
                state = IFS0bits.T1IF;
                break;

            #ifdef _TMR2
            case _TMR2_BASE_ADDRESS:
                state = IFS0bits.T2IF;
                break;
            #endif

            #ifdef _TMR3
            case _TMR3_BASE_ADDRESS:
                state = IFS0bits.T3IF;
                break;
            #endif

            #ifdef _TMR4
            case _TMR4_BASE_ADDRESS:
                state = IFS0bits.T4IF;
                break;
            #endif

            #ifdef _TMR5
            case _TMR5_BASE_ADDRESS:
                state = IFS0bits.T5IF;
                break;
            #endif
        }

    return state;
}


/// ----------------------------------------------------------------------
/// \brief    Borra els flags d'interrupcio del temporitzador.
/// \param    handler: El handler del temporitzador.
/// \param    event: El event.
///
void TMR::clearInterruptFlag(
    InterruptEvent event) {

    if (event == InterruptEvent::update)
        switch (_addr) {
            case _TMR1_BASE_ADDRESS:
                IFS0bits.T1IF = 0;
                break;

            #ifdef _TMR2
            case _TMR2_BASE_ADDRESS:
                IFS0bits.T2IF = 0;
                break;
            #endif

            #ifdef _TMR3
            case _TMR3_BASE_ADDRESS:
                IFS0bits.T3IF = 0;
                break;
            #endif

            #ifdef _TMR4
            case _TMR4_BASE_ADDRESS:
                IFS0bits.T4IF = 0;
                break;
            #endif

            #ifdef _TMR5
            case _TMR5_BASE_ADDRESS:
                IFS0bits.T5IF = 0;
                break;
            #endif
        }
}


/// ----------------------------------------------------------------------
/// \brief    Gestio de la interrupcio.
/// \param    event: Event que ha generat la interrupcio.
///
void TMR::interruptHandler(
    InterruptEvent event) {

}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    tmr: L'objecte a asignar.
///

TMR & TMR::operator = (
    const TMR &tmr) {

    _addr = tmr._addr;

    return  *this;
}



extern "C" void isrTMR1InterruptHandler(void) {

}