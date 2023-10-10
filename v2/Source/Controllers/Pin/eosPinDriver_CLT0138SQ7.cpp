#include "eos.h"
#include "Controllers/Pin/eosPinDriver_CLT0138SQ7.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    hSPI: Handler del dispositiu SPI per la comunicacio.
/// \param    hSS: Handler del pin pel chip select.
///
CLT0138SQ7_Device::CLT0138SQ7_Device(
	htl::spi::SPIDeviceHandler hSPI,
	htl::gpio::PinHandler hPinSS):

	_hSPI {hSPI},
	_hPinSS {hPinSS},
	_state {0},
	_underVoltage {false},
	_overTemperature {false} {

}


void CLT0138SQ7_Device::initialize() {

}


void CLT0138SQ7_Device::update() {

	// NO UTILITZAR INTERRUPCIONS. Per evitar bloqueig si es crida
	// desde un altre interrupcio amb prioritat inferior o igual a la del SPI

	uint8_t rxBuffer[2];

	_hPinSS->clear();
	_hSPI->transmit(nullptr, rxBuffer, sizeof(rxBuffer));
	_hPinSS->set();

	_underVoltage = (rxBuffer[1] & 0x02) == 0;
	_overTemperature = (rxBuffer[1] & 0x01) == 0;

	_state = rxBuffer[0];
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


