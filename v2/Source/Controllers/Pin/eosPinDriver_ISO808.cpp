#include "eos.h"
#include "Controllers/Pin/eosPinDriver_ISO808.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hSYNC: Handler del pin SYNC.
/// \param    hLOAD: Handler del pin LOAD.
/// \param    hIN1: Handler del pin IN1.
/// \param    hIN2: Handler del pin IN2.
/// \param    hIN3: Handler del pin IN3.
/// \param    hIN4: Handler del pin IN4.
/// \param    hIN5: Handler del pin IN5.
/// \param    hIN6: Handler del pin IN6.
/// \param    hIN7: Handler del pin IN7.
/// \param    hIN7: Handler del pin IN8.
/// \param    hOUTEN: Handler del pin OUTEN.
/// \param    hFAULT: Handler del pin FAULT.
///
ISO808_Device::ISO808_Device(
    htl::gpio::PinHandler hSYNC,
    htl::gpio::PinHandler hLOAD,
    htl::gpio::PinHandler hIN1,
    htl::gpio::PinHandler hIN2,
    htl::gpio::PinHandler hIN3,
    htl::gpio::PinHandler hIN4,
    htl::gpio::PinHandler hIN5,
    htl::gpio::PinHandler hIN6,
    htl::gpio::PinHandler hIN7,
    htl::gpio::PinHandler hIN8,
    htl::gpio::PinHandler hOUTEN,
    htl::gpio::PinHandler hFAULT):

    _oldState {0},
    _newState {0},
    _hSYNC {hSYNC},
    _hLOAD {hLOAD},
    _hIN1 {hIN1},
    _hIN2 {hIN2},
    _hIN3 {hIN3},
    _hIN4 {hIN4},
    _hIN5 {hIN5},
    _hIN6 {hIN6},
    _hIN7 {hIN7},
    _hIN8 {hIN8},
    _hOUTEN {hOUTEN},
    _hFAULT {hFAULT} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void ISO808_Device::initialize() {

    _hSYNC->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, true);
    _hLOAD->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, true);
    _hIN1->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hIN2->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hIN3->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hIN4->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hIN5->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hIN6->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hIN7->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hIN8->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hOUTEN->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::PullUpDn::none, htl::gpio::Speed::high, false);
    _hFAULT->initInput(htl::gpio::PullUpDn::up);
}


/// ----------------------------------------------------------------------
/// \brief    Sincronitza les sortides fisiques amb l'estat actual.
///
void ISO808_Device::update() {

    if (_newState != _oldState) {

        _hLOAD->clear();
        _hSYNC->clear();
        if ((_newState & 0x01) == 0) _hIN1->clear(); else _hIN1->set();
        if ((_newState & 0x02) == 0) _hIN2->clear(); else _hIN2->set();
        if ((_newState & 0x04) == 0) _hIN3->clear(); else _hIN3->set();
        if ((_newState & 0x08) == 0) _hIN4->clear(); else _hIN4->set();
        if ((_newState & 0x10) == 0) _hIN5->clear(); else _hIN5->set();
        if ((_newState & 0x20) == 0) _hIN6->clear(); else _hIN6->set();
        if ((_newState & 0x40) == 0) _hIN7->clear(); else _hIN7->set();
        if ((_newState & 0x80) == 0) _hIN8->clear(); else _hIN8->set();
        _hLOAD->set(); // Carrega en el latch
        _hSYNC->set(); // Transfereix a les sortides

        _oldState = _newState;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Indica si l'estat del dispositiu es correcte.
/// \return   True si tot es correcte.
///
bool ISO808_Device::isOK() {
    
    return _hFAULT->read();
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hDevice: El dispositiu.
/// \param    pinNumber: El numero de pin.
///
PinDriver_ISO808::PinDriver_ISO808(
    ISO808_DeviceHandler hDevice,
    uint8_t pinNumber) :

    _hDevice {hDevice},
    _pinMask {uint8_t(1 << pinNumber)} {
}


/// ----------------------------------------------------------------------
/// \brief    Activa el pin.
///
void PinDriver_ISO808::set() {

    _hDevice->set(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el pin.
///
void PinDriver_ISO808::clear() {

    _hDevice->clear(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix el pin.
///
void PinDriver_ISO808::toggle() {

    _hDevice->toggle(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el pin.
/// \param    pinState: El estat del pin.
///
void PinDriver_ISO808::write(
    bool pinState) {

    if (pinState)
        _hDevice->set(_pinMask);
    else
        _hDevice->clear(_pinMask);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el pin.
/// \return   L0estat del pin.
///
bool PinDriver_ISO808::read() {

    return (_hDevice->read() & _pinMask) != 0;
}
