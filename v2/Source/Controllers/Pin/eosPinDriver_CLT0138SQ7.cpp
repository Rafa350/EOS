#include "eos.h"
#include "Controllers/Pin/eosPinDriver_CLT0138SQ7.h"


using namespace eos;
using namespace htl;


CLT0138SQ7_Device::CLT0138SQ7_Device(
	htl::spi::SPIDeviceHandler hSPI,
	htl::gpio::PinHandler hSS):

	_hSPI {hSPI},
	_hSS {hSS},
	_state {0} {

}


void CLT0138SQ7_Device::initialize() {

}


uint8_t CLT0138SQ7_Device::read() {

	return _state;
}


void CLT0138SQ7_Device::update() {

	// NO UTILITZAR INTERRUPCIONS. Per evitar bloqueig si es crida
	// desde un altre interrupcio amb prioritat inferior o igual a la del SPI

	uint8_t buffer[2];

	_hSS->clear();
	_hSPI->receive(buffer, sizeof(buffer));
	_hSS->set();

	_state = buffer[1];
}


PinDriver_CLT0138SQ7::PinDriver_CLT0138SQ7(
	CLT0138SQ7_DeviceHandler hDevice,
	uint8_t pinNumber):

	_hDevice {hDevice},
	_pinMask {uint8_t(1 << pinNumber)} {

}


void PinDriver_CLT0138SQ7::set() {

}


void PinDriver_CLT0138SQ7::clear() {

}


void PinDriver_CLT0138SQ7::toggle() {

}


void PinDriver_CLT0138SQ7::write(
	bool state) {

}


bool PinDriver_CLT0138SQ7::read() {

	return (_hDevice->read() & _pinMask) != 0;
}


