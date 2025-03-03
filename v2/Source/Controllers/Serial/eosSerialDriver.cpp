#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SerialDriver::SerialDriver() :
    _state {State::reset},
	_txCompletedEvent {nullptr},
	_rxCompletedEvent {nullptr},
	_txCompletedEventEnabled {false},
	_rxCompletedEventEnabled {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriver::initialize() {

    if (_state == State::reset) {

        onInitialize();

        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriver::deinitialize() {

    if (_state == State::ready) {

        onDeinitialize();

        _txCompletedEvent = nullptr;
        _rxCompletedEvent = nullptr;
        _txCompletedEventEnabled = false;
        _rxCompletedEventEnabled = false;

        _state = State::reset;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transmissio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes en el buffer.
/// \return   El resultat de l'operacio
///
Result SerialDriver::transmit(
    const uint8_t *buffer,
    unsigned length) {

    if (_state == State::ready) {
        onTransmit(buffer, length);
        _state = State::transmiting;
        return Results::success;
    }
    else
        return Results::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   True si tot es correcte.
///
Result SerialDriver::receive(
    uint8_t *buffer,
    unsigned bufferSize) {

    if (_state == State::ready) {
        onReceive(buffer, bufferSize);
        _state = State::receiving;
        return Results::success;
    }
    else
        return Results::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que finalitzi l'es operacions pendents.
/// \param    timeout: Tamps maxim d'espera.
/// \return   El nombre de bytes transferits i el resultat.
///
ResultU32 SerialDriver::wait(
	unsigned timeout) {

	if (_state == State::receiving) {
		if (_rxFinished.wait(timeout))
			return ResultU32(Results::success, _rxCount);
		else
			return Results::timeout;
	}
	else if (_state == State::transmiting) {
		if (_txFinished.wait(timeout))
			return ResultU32(Results::success, _txCount);
		else
			return Results::timeout;
	}
	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta l'operacio en curs.
/// \return   True si tot es correcte.
///
Result SerialDriver::abort() {

	if ((_state == State::transmiting) || (_state == State::receiving)) {
		onAbort();
		_state = State::ready;
		return Results::success;
	}
	else
		return Results::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'TxCompleted'
/// \param    event: L'event
/// \param    enabled: Indica si el deixa habilitat
///
void SerialDriver::setTxCompletedEvent(
	const ITxCompletedEvent &event,
	bool enabled) {

	_txCompletedEvent = &event;
	_txCompletedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'RxCompleted'
/// \param    event: L'event
/// \param    enabled: Indica si el deixa habilitat
///
void SerialDriver::setRxCompletedEvent(
	const IRxCompletedEvent &event,
	bool enabled) {

	_rxCompletedEvent = &event;
	_rxCompletedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Genera el event 'TxCompleted'.
///
void SerialDriver::raiseTxCompleted(
    unsigned length) {

    if (_txCompletedEventEnabled) {

        TxCompletedEventArgs args = {
            .driver = this,
            .length = length
        };

        _txCompletedEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Genera l'event 'RxCompleted'.
///
void SerialDriver::raiseRxCompleted(
    unsigned length) {

    if (_rxCompletedEventEnabled) {

        RxCompletedEventArgs args = {
            .driver = this,
            .length = length
        };

        _rxCompletedEvent->execute(args);
    }
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
        raiseTxCompleted(length);
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
        raiseRxCompleted(length);
        if (irq)
        	_rxFinished.releaseISR();
        else
        	_rxFinished.release();
        _rxCount = length;
        _state = State::ready;
    }
}
