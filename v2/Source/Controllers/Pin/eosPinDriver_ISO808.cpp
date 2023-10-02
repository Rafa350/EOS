#include "eos.h"
#include "Controllers/Pin/eosPinDriver_ISO808.h"


using namespace eos;
using namespace htl;


PinDriver_ISO808::PinDriver_ISO808(
    ISO808DeviceHandler hDevice, 
    uint8_t pinNumber) :

    _hDevice {hDevice},
    _pinMask {uint8_t(1 << pinNumber)} {
}
	

void PinDriver_ISO808::set() {
    
    _hDevice->set(_pinMask);
    _hDevice->load();
    _hDevice->sync();
}
	

void PinDriver_ISO808::clear() {
    
    _hDevice->clear(_pinMask);
    _hDevice->load();
    _hDevice->sync();
}
	

void PinDriver_ISO808::toggle() {
    
    _hDevice->toggle(_pinMask);
    _hDevice->load();
    _hDevice->sync();
}
	

void PinDriver_ISO808::write(
    bool pinState) {
    
    if (pinState)
        _hDevice->set(_pinMask);
    else
        _hDevice->clear(_pinMask);
    _hDevice->load();
    _hDevice->sync();
}
	

bool PinDriver_ISO808::read() const {

    return _hDevice->read(_pinMask) != 0;
}
