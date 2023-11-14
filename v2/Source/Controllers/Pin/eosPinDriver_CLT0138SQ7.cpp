#include "eos.h"
#include "Controllers/Pin/eosPinDriver_CLT0138SQ7.h"
#include "System/Core/eosTask.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
///
CLT0138SQ7_Device::CLT0138SQ7_Device():

	_state {State::reset},
	_pinState {0},
	_underVoltage {false},
	_overTemperature {false},
	_spi {nullptr},
	_pinSS {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    hSPI: Handler del dispositiu SPI per la comunicacio.
/// \param    pinSS: El pin pel chip select.
///
CLT0138SQ7_Device::Result CLT0138SQ7_Device::initialize(
	htl::spi::SPIDevice *spi,
	htl::gpio::Pin *pinSS) {

	if (_state == State::reset) {

		_spi = spi;
		_pinSS = pinSS;

		_state = State::ready;

		return Result::ok;
	}

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza l'estat del driver en funcio del les entrades.
///
void CLT0138SQ7_Device::update() {

	// NO UTILITZAR INTERRUPCIONS. Per evitar bloqueig si es crida
	// desde un altre interrupcio amb prioritat inferior o igual a la del SPI

	if (_state == State::ready) {

		uint8_t rxBuffer[2];

		_pinSS->clear();
		_spi->receive(rxBuffer, sizeof(rxBuffer));
		_pinSS->set();

		_underVoltage = (rxBuffer[1] & 0x80) == 0;
		_overTemperature = (rxBuffer[1] & 0x40) == 0;

		_pinState = rxBuffer[0];
	}
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hDevice: Handler del dispositiu CTL0138SQ7
/// \param    pinNumber: El numero de pin.
///
PinDriver_CLT0138SQ7::PinDriver_CLT0138SQ7(
	CLT0138SQ7_Device *dev,
	uint8_t pinNumber):

	_dev {dev},
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

	return (_dev->read() & _pinMask) != 0;
}


