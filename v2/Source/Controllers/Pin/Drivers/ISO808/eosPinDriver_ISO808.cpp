#include "eos.h"
#include "Controllers/Pin/Drivers/ISO808/eosPinDriver_ISO808.h"
#include "Controllers/Pin/Drivers/ISO808/eosDevice_ISO808.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    del: El dispositiu.
/// \param    pinNumber: El numero de pin.
///
PinDriver_ISO808::PinDriver_ISO808(
    Device_ISO808 *dev,
    uint8_t pinNumber) :

    _dev {dev},
    _pinMask {uint8_t(1 << pinNumber)} {
}


/// ----------------------------------------------------------------------
/// \brief    Activa el pin.
///
void PinDriver_ISO808::set() {

    _dev->set(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el pin.
///
void PinDriver_ISO808::clear() {

    _dev->clear(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix el pin.
///
void PinDriver_ISO808::toggle() {

    _dev->toggle(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el pin.
/// \param    pinState: El estat del pin.
///
void PinDriver_ISO808::write(
    bool pinState) {

    if (pinState)
        _dev->set(_pinMask);
    else
        _dev->clear(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el pin.
/// \return   L0estat del pin.
///
bool PinDriver_ISO808::read() {

    return (_dev->read() & _pinMask) != 0;
}
