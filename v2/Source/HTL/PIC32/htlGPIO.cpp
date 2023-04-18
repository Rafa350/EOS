#include "HTL/htlGPIO.h"


using namespace htl::gpio;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins de sortida.
/// \param    gpio: Registres de hardware del dispositiu.
/// \param    mask: Mascara de pins.
/// \param    driver: Driver de sortida.
/// \param    speed: Velocitat.
///
static void initializeOutput(
    internal::GPIORegisters *gpio,
    PinMask mask,
    OutDriver driver,
    Speed speed) {

    gpio->TRISxCLR = mask;

    switch (driver) {
        case OutDriver::openDrain:
            gpio->ODCxSET = mask;
            break;

        case OutDriver::pushPull:
            gpio->ODCxCLR = mask;
            break;

        default:
            break;
    }
}



/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres del hardware del dispositiu.
///
Port::Port(
    internal::GPIORegisters *gpio) :

    _gpio(gpio) {

}


/// ----------------------------------------------------------------------
/// \brief    Activa el dispositiu.
///
void Port::activate() {

}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el dispositiu.
///
void Port::deactivate() {


}


/// ----------------------------------------------------------------------
/// \brief    Reseteja el dispositiu.
///
void Port::reset() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el port com sortides.
///
void Port::initOutput(
    PinMask mask,
    OutDriver driver,
    Speed speed) {

    activate();
    initializeOutput(_gpio, mask, driver, speed);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres de hardware del dispositiu.
/// \param    pinID: Identificador del pin.
///
Pin::Pin(
    internal::GPIORegisters *gpio,
    PinID pinID) :

    _gpio(gpio),
    _pinMask(1 << (int)pinID) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com entrada.
///
void Pin::initInput(
    PullUp pullUp) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin copm a sortida.
///
void Pin::initOutput(
    OutDriver driver,
    Speed speed,
    InitPinState pinState) {

    initializeOutput(_gpio, _pinMask, driver, speed);
}