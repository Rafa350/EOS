#include "eos.h"
#include "Controllers/Pin/eosPinDriver_VNI8200XP.h"


using namespace eos;
using namespace htl;


VNI8200XP_SerialDevice::VNI8200XP_SerialDevice(
	spi::SPIDeviceHandler hSPI,
	gpio::PinHandler hSS,
	gpio::PinHandler hOUTEN) :

	_hSPI {hSPI},
	_hSS {hSS},
	_hOUTEN {hOUTEN},
	_outReg {0} {

}


uint8_t VNI8200XP_SerialDevice::calcParity(
	uint8_t data) {

	uint8_t p0, p1, p2, np0;

	p0 = data ^ (data >> 1);
	p0 = p0 ^ (p0 >> 2);
	p0 = p0 ^ (p0 >> 4);
	p0 = p0 & 0x01;

	p1 = data ^ (data >> 2);
	p1 = p1 ^ (p1 >> 4);

	p2 = p1 & 0x01;

	p1 = p1 & 0x02;
	p1 = p1 >> 1;

	np0 = (~p0) & 0x01;

	return (p2 << 3) | (p1 << 2) | (p0 << 1) | np0;
}


uint8_t VNI8200XP_SerialDevice::transmit(uint8_t data) {

	uint8_t txData[2], rxData[2];

	txData[0] = calcParity(data);
	txData[1] = data;

	_hSS->clear();
	_hSPI->transmit(txData,  sizeof(txData));
	_hSS->set();

	return rxData[0];
}


void VNI8200XP_SerialDevice::outputEnable() {

	_hOUTEN->set();
}


void VNI8200XP_SerialDevice::outputDisable() {

	_hOUTEN->clear();
}


void VNI8200XP_SerialDevice::sync() {
    
    transmit(_outReg);
}


void VNI8200XP_SerialDevice::set(
	uint8_t pinMask) {

	_outReg |= pinMask;
}


void VNI8200XP_SerialDevice::clear(
	uint8_t pinMask) {

	_outReg &= ~pinMask;
}


void VNI8200XP_SerialDevice::toggle(
	uint8_t pinMask) {

	_outReg ^= pinMask;
}


void VNI8200XP_SerialDevice::write(
	uint8_t pinMask,
	bool pinState) {

	_outReg = (_outReg & ~pinMask) | pinMask;
}


bool VNI8200XP_SerialDevice::read(
	uint8_t pinMask) {

	return false;
}



PinDriver_VNI8200XP::PinDriver_VNI8200XP(
	VNI8200XP_DeviceHandler hDevice,
	uint8_t pinNumber):

	_hDevice {hDevice},
	_pinNumber {pinNumber} {

}


void PinDriver_VNI8200XP::set() {

	_hDevice->set(_pinNumber);
}


void PinDriver_VNI8200XP::clear() {

	_hDevice->clear(_pinNumber);
}


void PinDriver_VNI8200XP::toggle() {

	_hDevice->toggle(_pinNumber);
}

void PinDriver_VNI8200XP::write(
	bool pinState) {

	_hDevice->write(_pinNumber, pinState);
}


bool PinDriver_VNI8200XP::read() const {

	return _hDevice->read(_pinNumber);
}

