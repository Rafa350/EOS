#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SerialDriver::SerialDriver() :
    _state {State::reset} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriver::initialize() {

    if (_state == State::reset)
    	if (onInitialize())
    		_state = State::ready;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriver::deinitialize() {

    if (_state == State::ready)
    	if (onDeinitialize())
    		_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transmissio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes en el buffer.
/// \return   El resultat de l'operacio.
///
Result SerialDriver::transmit(
    const uint8_t *buffer,
    unsigned length) {

	eosAssert(buffer != nullptr);
	eosAssert(length > 0);

	if ((buffer == nullptr) ||
		(length == 0))
		return Results::errorParameter;

	else if (_state == State::ready) {
    	if (onTransmit(buffer, length)) {
    		_state = State::transmiting;
    		return Results::success;
    	}
    	else
    		return Results::error;
    }

    else
    	return Results::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
Result SerialDriver::receive(
    uint8_t *buffer,
    unsigned bufferSize) {

	eosAssert(buffer != nullptr);
	eosAssert(bufferSize > 0);

	if ((buffer == nullptr) ||
		(bufferSize == 0))
		return Results::errorParameter;

	else if (_state == State::ready) {
    	if (onReceive(buffer, bufferSize)) {
    		_state = State::receiving;
    		return Results::success;
    	}
    	else
    		return Results::error;
    }

    else
    	return Results::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que finalitzin les operacions pendents.
/// \param    timeout: Tamps maxim d'espera.
/// \return   El nombre de bytes transferits i el resultat.
/// \notes    En cas de timeout, s'aborta la comunicacio.
///
ResultU32 SerialDriver::wait(
	unsigned timeout) {

	if (_state == State::receiving) {
		if (_rxFinished.wait(timeout))
			return ResultU32(Results::success, _rxCount);
		else {
			abort();
			return Results::timeout;
		}
	}
	else if (_state == State::transmiting) {
		if (_txFinished.wait(timeout))
			return ResultU32(Results::success, _txCount);
		else {
			abort();
			return Results::timeout;
		}
	}
	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta l'operacio en curs.
/// \return   El resultat de l'operacio.
///
Result SerialDriver::abort() {

	if ((_state == State::transmiting) || (_state == State::receiving)) {
		if (onAbort()) {
			_state = State::ready;
			return Results::success;
		}
		else
			return Results::error;
	}
	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de transmissio.
/// \param    length: Nombre de bytes transmessos.
/// \param    irq: True si es crida des d'una interrupcio.
///
void SerialDriver::notifyTxCompleted(
	unsigned length,
	bool irq) {

    if (_state == State::transmiting) {
        if (irq)
        	_txFinished.releaseISR();
        else
        	_txFinished.release();
        _txCount = length;
        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la recepcio.
/// \param    length: Nombre de bytes rebuts
/// \param    irq: True si es crida des d'una interrupcio.
///
void SerialDriver::notifyRxCompleted(
	unsigned length,
	bool irq) {

    if (_state == State::receiving) {
        if (irq)
        	_rxFinished.releaseISR();
        else
        	_rxFinished.release();
        _rxCount = length;
        _state = State::ready;
    }
}
