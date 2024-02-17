#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


using namespace htl;
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
PortDevice::PortDevice(
    internal::GPIORegisters *gpio) :

    _gpio(gpio) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el port com sortides.
///
void PortDevice::initOutput(
    PinMask mask,
    OutputMode mode,
    Speed speed) const {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres de hardware del dispositiu.
/// \param    pinID: Identificador del pin.
///
PinDevice::PinDevice(
    internal::GPIORegisters *gpio,
    PinID pinID) :

    _gpio(gpio),
    _pinMask(1 << (int)pinID) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com entrada.
///
void PinDevice::initInput(
    InputMode mode) const {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin copm a sortida.
///
void PinDevice::initOutput(
    OutputMode mode,
    Speed speed) const {

}
