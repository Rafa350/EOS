#include "eos.h"
#include "Controllers/Pin/Drivers/ISO808/eosPinDriver_ISO808.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
ISO808_Device::ISO808_Device():
    _oldState {0},
    _newState {0},
    _pinSYNC {nullptr},
    _pinLOAD {nullptr},
    _pinIN1 {nullptr},
    _pinIN2 {nullptr},
    _pinIN3 {nullptr},
    _pinIN4 {nullptr},
    _pinIN5 {nullptr},
    _pinIN6 {nullptr},
    _pinIN7 {nullptr},
    _pinIN8 {nullptr},
    _pinOUTEN {nullptr},
    _pinFAULT {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    pinSYNC: Handler del pin SYNC.
/// \param    pinLOAD: Handler del pin LOAD.
/// \param    pinIN1: Handler del pin IN1.
/// \param    pinIN2: Handler del pin IN2.
/// \param    pinIN3: Handler del pin IN3.
/// \param    pinIN4: Handler del pin IN4.
/// \param    pinIN5: Handler del pin IN5.
/// \param    pinIN6: Handler del pin IN6.
/// \param    pinIN7: Handler del pin IN7.
/// \param    pinIN7: Handler del pin IN8.
/// \param    pinOUTEN: Handler del pin OUTEN.
/// \param    pinFAULT: Handler del pin FAULT.
///
void ISO808_Device::initialize(
    htl::gpio::Pin *pinSYNC,
    htl::gpio::Pin *pinLOAD,
    htl::gpio::Pin *pinIN1,
    htl::gpio::Pin *pinIN2,
    htl::gpio::Pin *pinIN3,
    htl::gpio::Pin *pinIN4,
    htl::gpio::Pin *pinIN5,
    htl::gpio::Pin *pinIN6,
    htl::gpio::Pin *pinIN7,
    htl::gpio::Pin *pinIN8,
    htl::gpio::Pin *pinOUTEN,
    htl::gpio::Pin *pinFAULT) {

    _pinSYNC = pinSYNC;
    _pinLOAD = pinLOAD;
    _pinIN1 = pinIN1;
    _pinIN2 = pinIN2;
    _pinIN3 = pinIN3;
    _pinIN4 = pinIN4;
    _pinIN5 = pinIN5;
    _pinIN6 = pinIN6;
    _pinIN7 = pinIN7;
    _pinIN8 = pinIN8;
    _pinOUTEN = pinOUTEN;
    _pinFAULT = pinFAULT;
}


/// ----------------------------------------------------------------------
/// \brief    Sincronitza les sortides fisiques amb l'estat actual.
///
void ISO808_Device::update() {

    if (_newState != _oldState) {

        _pinLOAD->clear();
        _pinSYNC->clear();
        if ((_newState & 0x01) == 0) _pinIN1->clear(); else _pinIN1->set();
        if ((_newState & 0x02) == 0) _pinIN2->clear(); else _pinIN2->set();
        if ((_newState & 0x04) == 0) _pinIN3->clear(); else _pinIN3->set();
        if ((_newState & 0x08) == 0) _pinIN4->clear(); else _pinIN4->set();
        if ((_newState & 0x10) == 0) _pinIN5->clear(); else _pinIN5->set();
        if ((_newState & 0x20) == 0) _pinIN6->clear(); else _pinIN6->set();
        if ((_newState & 0x40) == 0) _pinIN7->clear(); else _pinIN7->set();
        if ((_newState & 0x80) == 0) _pinIN8->clear(); else _pinIN8->set();
        _pinLOAD->set(); // Carrega en el latch
        _pinSYNC->set(); // Transfereix a les sortides

        _oldState = _newState;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Indica si l'estat del dispositiu es correcte.
/// \return   True si tot es correcte.
///
bool ISO808_Device::isOK() {
    
    return _pinFAULT->read();
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    del: El dispositiu.
/// \param    pinNumber: El numero de pin.
///
PinDriver_ISO808::PinDriver_ISO808(
    ISO808_Device *dev,
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
