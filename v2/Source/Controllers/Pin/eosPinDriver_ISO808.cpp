#include "eos.h"
#include "Controllers/Pin/eosPinDriver_ISO808.h"


using namespace eos;
using namespace htl;



Driver_ISO808::Driver_ISO808() {

}



void Driver_ISO808::initialize() {

 	_pinSYNC->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium, gpio::PinState::set);
	_pinLOAD->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium, gpio::PinState::set);
	_pinIN1->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinIN2->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinIN3->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinIN4->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinIN5->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinIN6->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinIN7->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinIN8->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium);
	_pinOUTEN->initOutput(gpio::OutDriver::pushPull, gpio::Speed::medium, gpio::PinState::clear);
	_pinFAULT->initInput(gpio::PullUpDn::up);

	_pinState = 0;
}


void Driver_ISO808::set(
	uint8_t pinState) {

	_pinState |= pinState;
}


void Driver_ISO808::clear(
	uint8_t pinState) {

	_pinState &= ~pinState);
}


void Driver_ISO808::toggle(
	uint8_t pinState) {

	_pinState ^= pinState;
}


void Driver_ISO808::refresh() {

	_pinLOAD->clear();

	if ((_pinState & 0x01) == 0) _pinIN1->clear(); else _pinIN1->set();
	if ((_pinState & 0x02) == 0) _pinIN2->clear(); else _pinIN2->set();
	if ((_pinState & 0x04) == 0) _pinIN3->clear(); else _pinIN3->set();
	if ((_pinState & 0x08) == 0) _pinIN4->clear(); else _pinIN4->set();
	if ((_pinState & 0x10) == 0) _pinIN5->clear(); else _pinIN5->set();
	if ((_pinState & 0x20) == 0) _pinIN6->clear(); else _pinIN6->set();
	if ((_pinState & 0x40) == 0) _pinIN7->clear(); else _pinIN7->set();
	if ((_pinState & 0x80) == 0) _pinIN8->clear(); else _pinIN8->set();

	_pinLOAD->set();
}


void Driver_ISO808::outputEnable() {

	_pinOUTEN->set();
}


void Driver_ISO808::outputDisable() {

	_pinOUTEN->clear();
}


PinDriver_ISO808::PinDriver_ISO808(
	Driver_ISO808 *driver,
	uint8_t pinNumber):

	_driver {driver},
	_pinNumber {pinNumber} {

}


void PinDriver_ISO808::set() {
    
    _driver->set(1 << _pinNumber);
    _driver->refresh();
}


void PinDriver_ISO808::clear() {
    
    _driver->clear(1 << _pinNumber);
    _driver->refresh();
}


void PinDriver_ISO808::toggle() {
    
    _driver->toggle(1 << _pinNumber);
    _driver->refresh();
}
