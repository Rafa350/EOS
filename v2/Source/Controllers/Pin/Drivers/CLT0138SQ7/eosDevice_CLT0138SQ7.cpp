#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Pin/Drivers/CLT0138SQ7/eosDevice_CLT0138SQ7.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    devSPI: El dispositiu SPI per la comunicacio.
/// \param    pinSS: El pin pel chip select.
///
Device_CLT0138SQ7::Device_CLT0138SQ7(
    htl::spi::SPIDevice *devSPI,
    htl::gpio::PinDevice *pinSS):

	_state {State::reset},
	_pinState {0},
	_underVoltage {false},
	_overTemperature {false},
	_devSPI {devSPI},
	_pinSS {pinSS} {

}


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    params: Parametres de configuracio.
///
Device_CLT0138SQ7::Device_CLT0138SQ7(
    const CreateParams *params) :

    _state {State::reset},
    _pinState {0},
    _underVoltage {false},
    _overTemperature {false},
    _devSPI {params->devSPI},
    _pinSS {params->pinSS} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \return   El resultat de l'operacio.
///
Result Device_CLT0138SQ7::initialize() {

	if (_state == State::reset) {

		_pinSS->clear();

		_state = State::ready;

		return Results::success;
	}

	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza l'estat del driver en funcio del les entrades.
/// \return   El resultat de l'operacio.
///
Result Device_CLT0138SQ7::update() {

	// NO UTILITZAR INTERRUPCIONS. Per evitar bloqueig si es crida
	// desde un altre interrupcio amb prioritat inferior o igual a la del SPI

	if (_state == State::ready) {

		uint8_t rxBuffer[2];

		_pinSS->clear();
		_devSPI->receive(rxBuffer, sizeof(rxBuffer), 1000);
		_pinSS->set();

		_underVoltage = (rxBuffer[1] & 0x80) == 0;
		_overTemperature = (rxBuffer[1] & 0x40) == 0;

		_pinState = rxBuffer[0];

		return Results::success;
	}

	else
	    return Results::error;
}
