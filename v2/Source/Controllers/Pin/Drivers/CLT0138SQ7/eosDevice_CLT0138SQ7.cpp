#include "eos.h"
#include "Controllers/Pin/Drivers/CLT0138SQ7/eosDevice_CLT0138SQ7.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
///
Device_CLT0138SQ7::Device_CLT0138SQ7():

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
Device_CLT0138SQ7::Result Device_CLT0138SQ7::initialize(
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
void Device_CLT0138SQ7::update() {

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
