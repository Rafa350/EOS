#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Pin/Drivers/VNI8200XP/eosPinDriver_VNI8200XP.h"


using namespace eos;
using namespace htl;


PinDriver_VNI8200XP::PinDriver_VNI8200XP(
	Device_VNI8200XP *dev,
	uint8_t pinNumber):

	_dev {dev},
	_pinMask {uint8_t(1 << pinNumber)} {

	eosAssert(dev != nullptr);
	eosAssert(pinNumber < 8);
}


void PinDriver_VNI8200XP::set() {

	_dev->set(_pinMask);
}


void PinDriver_VNI8200XP::clear() {

	_dev->clear(_pinMask);
}


void PinDriver_VNI8200XP::toggle() {

	_dev->toggle(_pinMask);
}


void PinDriver_VNI8200XP::write(
	bool pinState) {

	_dev->write(_pinMask, pinState);
}


bool PinDriver_VNI8200XP::read() {

	return (_dev->read() & _pinMask) != 0;
}

