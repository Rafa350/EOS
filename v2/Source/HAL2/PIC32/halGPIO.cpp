#include "HAL2/hal.h"
#include "HAL2/PIC32/halGPIO.H"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief     Constructor.
/// \param     port: Identificador del port.
/// \param     pin: Identificador del pin.
//
GPIO::GPIO(
    GPIOPort port,
    GPIOPin pin) :

    _regs(getRegister(port)),
    _mask(getMask(pin)) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    gpio: El objecte a copiar.
///
GPIO::GPIO(
    const GPIO &gpio) :

    _regs(gpio._regs),
    _mask(gpio._mask) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin.
/// \param    mode: Modus de treball del pin.
///
void GPIO::initialize(
    GPIOMode mode) {

    switch (mode) {
        case GPIOMode::input:
        case GPIOMode::input_PU:
        case GPIOMode::input_PD:
            _regs->TRISxSET = _mask;
            break;

        case GPIOMode::output:
        case GPIOMode::output_OD:
            _regs->TRISxCLR = _mask;
            if (mode == GPIOMode::output_OD)
                _regs->ODCxSET = _mask;
            else
                _regs->ODCxCLR = _mask;
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat SET al pin.
///
void GPIO::set() const {

    _regs->PORTxSET = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat CLEAR al pin.
///
void GPIO::clear() const {

    _regs->PORTxCLR = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin.
///
void GPIO::toggle() const {

    _regs->PORTxINV = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat del pin.
/// \param    s: eL ESTAT.
///
void GPIO::write(
    bool s) const {

    if (s)
        _regs->PORTxSET = _mask;
    else
        _regs->PORTxCLR = _mask;
}


/// ----------------------------------------------------------------------
/// \Brief    Llegeix l'estat del pin.
/// \return   L'estat del pin.
///
bool GPIO::read() const {

    return (_regs->PORTx & _mask) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    gpio: El objecte a asignar.
///
GPIO & GPIO::operator = (
    const GPIO &gpio) {

    _regs = gpio._regs;
    _mask = gpio._mask;

    return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    s: El valor a signar.
///
GPIO & GPIO::operator = (
    bool s) {

    write(s);

    return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador de conversio a bool
/// \return   L'estat del pin.
///
GPIO::operator bool() const {

    return read();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter als registres asociats al port.
/// \return   El punter.
///
GPIO::Registers* GPIO::getRegister(
    GPIOPort port) {

    uint32_t addr = 0;

    switch (port) {
        case GPIOPort::portA: addr = _PORTA_BASE_ADDRESS - 0x10; break;
        case GPIOPort::portB: addr = _PORTB_BASE_ADDRESS - 0x10; break;
        case GPIOPort::portC: addr = _PORTC_BASE_ADDRESS - 0x10; break;
        case GPIOPort::portD: addr = _PORTD_BASE_ADDRESS - 0x10; break;
        case GPIOPort::portE: addr = _PORTE_BASE_ADDRESS - 0x10; break;
        case GPIOPort::portF: addr = _PORTF_BASE_ADDRESS - 0x10; break;
    }

    return reinterpret_cast<Registers*>(addr);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la mascara associada al pin.
/// \return   La mascara.
///

uint32_t GPIO::getMask(
    GPIOPin pin) {

    uint32_t mask = 0;

    switch (pin) {
        case GPIOPin::pin0: mask = 0x0001; break;
        case GPIOPin::pin1: mask = 0x0002; break;
        case GPIOPin::pin2: mask = 0x0004; break;
        case GPIOPin::pin3: mask = 0x0008; break;
        case GPIOPin::pin4: mask = 0x0010; break;
        case GPIOPin::pin5: mask = 0x0020; break;
        case GPIOPin::pin6: mask = 0x0040; break;
        case GPIOPin::pin7: mask = 0x0080; break;
        case GPIOPin::pin8: mask = 0x0100; break;
        case GPIOPin::pin9: mask = 0x0200; break;
        case GPIOPin::pin10: mask = 0x0400; break;
        case GPIOPin::pin11: mask = 0x0800; break;
        case GPIOPin::pin12: mask = 0x1000; break;
        case GPIOPin::pin13: mask = 0x2000; break;
        case GPIOPin::pin14: mask = 0x4000; break;
        case GPIOPin::pin15: mask = 0x8000; break;
    }

    return mask;
}
