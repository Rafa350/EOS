#include "HAL2/hal.h"
#include "HAL2/PIC32/halGPIO.H"


using namespace hal;



/// ----------------------------------------------------------------------
/// \brief     Constructor.
/// \param     port: Identificador del port.
/// \param     pin: Identificador del pin.
//
GPIO::GPIO(
    Port port,
    Pin pin) :

    _regs(getRegisterPtr(port)),
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
/// \brief    Inicialitza el pin com entrada.
/// \param    mode: Modus de treball del pin.
///
void GPIO::initInput(
    InputMode mode) {

    _regs->TRISxSET = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com sortida.
/// \param    mode: Modus de treball del pin.
///
void GPIO::initOutput(
    OutputMode mode) {

    _regs->TRISxCLR = _mask;
    if (mode == OutputMode::output_OD)
        _regs->ODCxSET = _mask;
    else
        _regs->ODCxCLR = _mask;
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
GPIO::Registers* GPIO::getRegisterPtr(
    Port port) {

    uint32_t addr = 0;

    switch (port) {
        case Port::portA: addr = _PORTA_BASE_ADDRESS - 0x10; break;
        case Port::portB: addr = _PORTB_BASE_ADDRESS - 0x10; break;
        case Port::portC: addr = _PORTC_BASE_ADDRESS - 0x10; break;
        case Port::portD: addr = _PORTD_BASE_ADDRESS - 0x10; break;
        case Port::portE: addr = _PORTE_BASE_ADDRESS - 0x10; break;
        case Port::portF: addr = _PORTF_BASE_ADDRESS - 0x10; break;
    }

    return reinterpret_cast<Registers*>(addr);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la mascara associada al pin.
/// \return   La mascara.
///
uint32_t GPIO::getMask(
    Pin pin) {

    uint32_t mask = 0;

    switch (pin) {
        case Pin::pin0: mask = 0x0001; break;
        case Pin::pin1: mask = 0x0002; break;
        case Pin::pin2: mask = 0x0004; break;
        case Pin::pin3: mask = 0x0008; break;
        case Pin::pin4: mask = 0x0010; break;
        case Pin::pin5: mask = 0x0020; break;
        case Pin::pin6: mask = 0x0040; break;
        case Pin::pin7: mask = 0x0080; break;
        case Pin::pin8: mask = 0x0100; break;
        case Pin::pin9: mask = 0x0200; break;
        case Pin::pin10: mask = 0x0400; break;
        case Pin::pin11: mask = 0x0800; break;
        case Pin::pin12: mask = 0x1000; break;
        case Pin::pin13: mask = 0x2000; break;
        case Pin::pin14: mask = 0x4000; break;
        case Pin::pin15: mask = 0x8000; break;
    }

    return mask;
}
