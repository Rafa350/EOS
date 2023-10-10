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
    htl::gpio::PinHandler hPinSYNC,
    htl::gpio::PinHandler hPinLOAD,
    htl::gpio::PinHandler hPinIN1,
    htl::gpio::PinHandler hPinIN2,
    htl::gpio::PinHandler hPinIN3,
    htl::gpio::PinHandler hPinIN4,
    htl::gpio::PinHandler hPinIN5,
    htl::gpio::PinHandler hPinIN6,
    htl::gpio::PinHandler hPinIN7,
    htl::gpio::PinHandler hPinIN8,
    htl::gpio::PinHandler hPinOUTEN,
    htl::gpio::PinHandler hPinFAULT):

    _oldState {0},
    _newState {0},
    _hPinSYNC {hPinSYNC},
    _hPinLOAD {hPinLOAD},
    _hPinIN1 {hPinIN1},
    _hPinIN2 {hPinIN2},
    _hPinIN3 {hPinIN3},
    _hPinIN4 {hPinIN4},
    _hPinIN5 {hPinIN5},
    _hPinIN6 {hPinIN6},
    _hPinIN7 {hPinIN7},
    _hPinIN8 {hPinIN8},
    _hPinOUTEN {hPinOUTEN},
    _hPinFAULT {hPinFAULT} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void ISO808_Device::initialize() {

    _hPinSYNC->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, true);
    _hPinLOAD->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, true);
    _hPinIN1->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinIN2->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinIN3->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinIN4->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinIN5->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinIN6->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinIN7->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinIN8->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinOUTEN->initOutput(htl::gpio::OutputMode::pushPull, htl::gpio::Speed::high, false);
    _hPinFAULT->initInput(htl::gpio::InputMode::pullUp);
}


/// ----------------------------------------------------------------------
/// \brief    Sincronitza les sortides fisiques amb l'estat actual.
///
void ISO808_Device::update() {

    if (_newState != _oldState) {

        _hPinLOAD->clear();
        _hPinSYNC->clear();
        if ((_newState & 0x01) == 0) _hPinIN1->clear(); else _hPinIN1->set();
        if ((_newState & 0x02) == 0) _hPinIN2->clear(); else _hPinIN2->set();
        if ((_newState & 0x04) == 0) _hPinIN3->clear(); else _hPinIN3->set();
        if ((_newState & 0x08) == 0) _hPinIN4->clear(); else _hPinIN4->set();
        if ((_newState & 0x10) == 0) _hPinIN5->clear(); else _hPinIN5->set();
        if ((_newState & 0x20) == 0) _hPinIN6->clear(); else _hPinIN6->set();
        if ((_newState & 0x40) == 0) _hPinIN7->clear(); else _hPinIN7->set();
        if ((_newState & 0x80) == 0) _hPinIN8->clear(); else _hPinIN8->set();
        _hPinLOAD->set(); // Carrega en el latch
        _hPinSYNC->set(); // Transfereix a les sortides

        _oldState = _newState;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Indica si l'estat del dispositiu es correcte.
/// \return   True si tot es correcte.
///
bool ISO808_Device::isOK() {
    
    return _hPinFAULT->read();
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
