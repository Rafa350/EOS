module Eos.Controllers.Pin.ISO808;


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;


/// ---------------------------------------------------------------------------
/// @brief    Constructor
/// @param    devSPI: Dispositiu SPI
/// @param    pinSS: El pin SS
/// @param    pinOUTEN: EL pin OUTEN
/// @param    pinFAULT: El pin FAULT
/// @param    pinPGOOD: EL pin PGOOD
///
Device_ISO808_SPI::Device_ISO808_SPI(
    SPIDevice *devSPI,
    PinDevice *pinSS,
    PinDevice *pinOUTEN,
    PinDevice *pinFAULT,
    PinDevice *pinPGOOD) :

    Device_ISO808 {},
    _devSPI {devSPI},
    _pinSS {pinSS},
    _pinOUTEN {pinOUTEN},
    _pinFAULT {pinFAULT},
    _pinPGOOD {pinPGOOD} {

}

/// ---------------------------------------------------------------------------
/// @brief    Sincronitza les sortides fisiques amb l'estat actual.
///
void Device_ISO808_SPI::updateImpl(
    UInt8 state) {

    _pinSS->clear();

    _pinSS->set();
}


/// ---------------------------------------------------------------------------
/// @brief    Indica si l'estat del dispositiu es correcte.
/// \return   True si tot es correcte.
///
bool Device_ISO808_SPI::isOKImpl() {

    return _pinFAULT->read();
}
