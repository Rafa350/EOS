#include "eos.h"
#include "Controllers/Pin/Drivers/ISO808/eosDevice_ISO808.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pinSYNC: El pin SYNC.
/// \param    pinLOAD: El pin LOAD.
/// \param    pinIN1: El pin IN1.
/// \param    pinIN2: El pin IN2.
/// \param    pinIN3: El pin IN3.
/// \param    pinIN4: El pin IN4.
/// \param    pinIN5: El pin IN5.
/// \param    pinIN6: El pin IN6.
/// \param    pinIN7: El pin IN7.
/// \param    pinIN7: El pin IN8.
/// \param    pinOUTEN: El pin OUTEN.
/// \param    pinFAULT: El pin FAULT.
///
Device_ISO808::Device_ISO808(
    Pin *pinSYNC,
    Pin *pinLOAD,
    Pin *pinIN1,
    Pin *pinIN2,
    Pin *pinIN3,
    Pin *pinIN4,
    Pin *pinIN5,
    Pin *pinIN6,
    Pin *pinIN7,
    Pin *pinIN8,
    Pin *pinOUTEN,
    Pin *pinFAULT):

    _oldState {0},
    _newState {0},
    _pinSYNC {pinSYNC},
    _pinLOAD {pinLOAD},
    _pinIN1 {pinIN1},
    _pinIN2 {pinIN2},
    _pinIN3 {pinIN3},
    _pinIN4 {pinIN4},
    _pinIN5 {pinIN5},
    _pinIN6 {pinIN6},
    _pinIN7 {pinIN7},
    _pinIN8 {pinIN8},
    _pinOUTEN {pinOUTEN},
    _pinFAULT {pinFAULT} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
Device_ISO808::Result Device_ISO808::initialize() {

    if (_pinOUTEN == nullptr)
        _pinOUTEN->clear();

    return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
void Device_ISO808::deinitialize() {

    if (_pinOUTEN == nullptr)
        _pinOUTEN->clear();
}


/// ----------------------------------------------------------------------
/// \brief    Sincronitza les sortides fisiques amb l'estat actual.
///
void Device_ISO808::update() {

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
bool Device_ISO808::isOK() {

    return _pinFAULT->read();
}
