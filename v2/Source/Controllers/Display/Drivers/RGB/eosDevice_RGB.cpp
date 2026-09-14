#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "Controllers/Display/Drivers/RGB/eosDevice_RGB.h"


using namespace eos;


void Device_RGB::initialize(
        Pin *pinLCDE,
        Pin *pinBKLE) {

    _pinLCDE = pinLCDE;
    _pinBKLE = pinBKLE;
}


void Device_RGB::enable() {

    _pinLCDE->set();
    _pinBKLE->set();
}


void Device_RGB::disable() {

    _pinLCDE->clear();
    _pinBKLE->clear();
}
