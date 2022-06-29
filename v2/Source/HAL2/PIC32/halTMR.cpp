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
/// \brief    Inicialitza el contador.
/// \param    clkDiv: Divisor del rellotge.
/// \param    period: Periode del contador.
/// \param    mode32: True si es un contador de 32 bits.
///
void TMR::initialize(
    ClockDivider clkDiv,
    uint32_t period,
    bool mode32) {

    // Desactiva les interrupcions del temporitzador
    //
    //halTMRDisableInterrupts(handler, HAL_TMR_EVENT_ALL);

    // Configura el timer de tipus A
    //
    if (_regs == reinterpret_cast<Registers*>(_TMR1_BASE_ADDRESS)) {

        _regs->TAxCON.ON = 0;    // Desactiva el timer
        _regs->TAxCON.TCS = 0;   // Clock source interna.
        switch (clkDiv) {
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

    // Configura el timer de tipus B
    //
    else {

        _regs->TBxCON.ON = 0;    // Desactiva el timer
#if defined(__32MX460F512L__)
        _regs->TBxCON.TCS = 0;   // Clock source interna.
#endif
        _regs->TBxCON.TCKPS = (settings->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos;
        _regs->TBxCON.T32 = mode32;
    }

    setCounter(0);
    setPeriod(period);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el contador.
/// \param    handler: Handler del temporitzador.
/// \param    period: El valor del contador.
///
void TMR::setCounter(
    uint32_t counter) {

    if ((_regs != reinterpret_cast<Registers*>(_TMR1_BASE_ADDRESS)) &&
        (_regs->TBxCON.T32 == 1)) {

        Registers *regs32 = reinterpret_cast<Registers*>((uint32_t)_regs + 0x200);
        regs32->TMRx = (counter >> 16) & 0xFFFF;
    }
    _regs->TMRx = counter & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode.
/// \param    handler: Handler del temporitzador.
/// \param    period: El valor del periode.
///
void TMR::setPeriod(
    uint32_t period) {

    if ((_regs != reinterpret_cast<Registers*>(_TMR1_BASE_ADDRESS)) &&
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

    if (_regs == reinterpret_cast<Registers*>(_TMR1_BASE_ADDRESS))
        _regs->TAxCON.ON = 1;
    else
        _regs->TBxCON.ON = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Para el contador.
///
void TMR::stop() {

    if (_regs == reinterpret_cast<Registers*>(_TMR1_BASE_ADDRESS))
        _regs->TAxCON.ON = 0;
    else
        _regs->TBxCON.ON = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter als registres del temporitzador.
/// \param    timer: Identificador del temporitzadof.
/// \return   Punter als registres.
///
TMR::Registers* TMR::getRegisterPtr(
    Timer timer) {

    uint32_t addr = 0;

    switch (timer) {
        case Timer::timer1: addr = _TMR1_BASE_ADDRESS; break;
        case Timer::timer2: addr = _TMR2_BASE_ADDRESS; break;
        case Timer::timer3: addr = _TMR3_BASE_ADDRESS; break;
        case Timer::timer4: addr = _TMR4_BASE_ADDRESS; break;
        case Timer::timer5: addr = _TMR5_BASE_ADDRESS; break;

    }
    return reinterpret_cast<Registers*>(addr);
}
