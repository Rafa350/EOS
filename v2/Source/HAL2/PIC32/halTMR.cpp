#include "HAL2/hal.h"
#include "HAL2/PIC32/halTMR.h"


using namespace hal;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    timer: Identificador del temporitzador.
///
TMR::TMR(
    Timer timer):

    _regs(getRegisterPtr(timer)) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    tmr: L'objecte a copiar.
///
TMR::TMR(
    const TMR &tmr):

    _regs(tmr._regs) {

}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el divisor.
/// \param    divider: Divisor del rellotge.
///
void TMR::setClockDivider(
    ClockDivider divider) {

    // Desactiva les interrupcions del temporitzador
    //
    //halTMRDisableInterrupts(handler, HAL_TMR_EVENT_ALL);

    if ((uint32_t)_regs == _TMR1_BASE_ADDRESS) {
        switch (divider) {
            case ClockDivider::div8:
                _regs->TAxCON.TCKPS = 1;
                break;

            case ClockDivider::div64:
                _regs->TAxCON.TCKPS = 2;
                break;

            case ClockDivider::div256:
                _regs->TAxCON.TCKPS = 3;
                break;

            default:
                _regs->TAxCON.TCKPS = 0;
                break;
        }
    }

    else {
        switch (divider) {
            case ClockDivider::div1:
                _regs->TBxCON.TCKPS = 0;
                break;

            case ClockDivider::div2:
                _regs->TBxCON.TCKPS = 1;
                break;

            case ClockDivider::div4:
                _regs->TBxCON.TCKPS = 2;
                break;

            case ClockDivider::div8:
                _regs->TBxCON.TCKPS = 3;
                break;

            case ClockDivider::div16:
                _regs->TBxCON.TCKPS = 4;
                break;

            case ClockDivider::div32:
                _regs->TBxCON.TCKPS = 5;
                break;

            case ClockDivider::div64:
                _regs->TBxCON.TCKPS = 6;
                break;

            case ClockDivider::div256:
                _regs->TBxCON.TCKPS = 7;
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

//#if defined(__32MX460F512L__)
    if ((uint32_t)_regs == _TMR1_BASE_ADDRESS)
        _regs->TAxCON.TCS = 0;
    else
        _regs->TBxCON.TCS = 0;
//#endif
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la resolucio del contador.
/// \param    resolution: La resulucio.
///
void TMR::setResolution(
    Resolution resolution) {

    if ((uint32_t)_regs != _TMR1_BASE_ADDRESS)
        _regs->TBxCON.T32 = resolution == Resolution::res32;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el contador.
/// \param    period: El valor del contador.
///
void TMR::setCounter(
    uint32_t counter) {

    if (((uint32_t)_regs != _TMR1_BASE_ADDRESS) &&
        (_regs->TBxCON.T32 == 1)) {

        Registers *regs32 = reinterpret_cast<Registers*>((uint32_t)_regs + 0x200);
        regs32->TMRx = (counter >> 16) & 0xFFFF;
    }
    _regs->TMRx = counter & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode.
/// \param    period: El valor del periode.
///
void TMR::setPeriod(
    uint32_t period) {

    if (((uint32_t)_regs != _TMR1_BASE_ADDRESS) &&
        (_regs->TBxCON.T32 == 1)) {

        Registers *regs32 = reinterpret_cast<Registers*>((uint32_t)_regs + 0x200);
        regs32->PRx = (period >> 16) & 0xFFFF;
    }
    _regs->PRx = period & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador.
///
void TMR::start() {

    if ((uint32_t)_regs == _TMR1_BASE_ADDRESS)
        _regs->TAxCON.ON = 1;
    else
        _regs->TBxCON.ON = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Para el contador.
///
void TMR::stop() {

    if ((uint32_t)_regs == _TMR1_BASE_ADDRESS)
        _regs->TAxCON.ON = 0;
    else
        _regs->TBxCON.ON = 0;
}


/// ----------------------------------------------------------------------
/// \brief   Activa les interrupcions del temporitzador.
/// \param   event: El event a activar.
///
void TMR::enableInterrupts(
    uint32_t event) {

    switch ((uint32_t) handler->regs) {
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
/// \return   Diferent de zero si previament estava activada.
///
uint32_t TMR::disableInterrupts(
    uint32_t event) {

    uint32_t state = 0;

    switch ((uint32_t) _regs) {
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
bool TMR::getInterruptFlags(
    uint32_t event) {

    switch ((uint32_t) _regs) {
        case _TMR1_BASE_ADDRESS:
            return IFS0bits.T1IF;

#ifdef _TMR2
        case _TMR2_BASE_ADDRESS:
            return IFS0bits.T2IF;
#endif

#ifdef _TMR3
        case _TMR3_BASE_ADDRESS:
            return IFS0bits.T3IF;
#endif

#ifdef _TMR4
        case _TMR4_BASE_ADDRESS:
            return IFS0bits.T4IF;
#endif

#ifdef _TMR5
        case _TMR5_BASE_ADDRESS:
            return IFS0bits.T5IF;
#endif

        default:
            return false;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Borra els flags d'interrupcio del temporitzador.
/// \param    handler: El handler del temporitzador.
/// \param    event: El event.
///
void TMR::clearInterruptFlags(
    uint32_t event) {

    switch ((uint32_t) _regs) {
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
/// \brief    Obte el punter als registres del temporitzador.
/// \param    timer: Identificador del temporitzado.
/// \return   Punter als registres.
///
TMR::Registers* TMR::getRegisterPtr(
    Timer timer) {

    return reinterpret_cast<Registers*>(_TMR1_BASE_ADDRESS + (timer * 0x00000200));
}
