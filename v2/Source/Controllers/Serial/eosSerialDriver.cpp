#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
AsyncSerialDriver::AsyncSerialDriver() :

	_state {State::reset},
	_txCompletedEvent {nullptr},
	_rxCompletedEvent {nullptr},
	_abortedEvent {nullptr},
	_txCompletedEventEnabled {false},
	_rxCompletedEventEnabled {false},
	_abortedEventEnabled {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver::initialize() {

	initializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver::deinitialize() {

	deinitializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: El nombre de bytes a transmetre.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver::startTx(
	const uint8_t *buffer,
	unsigned length) {

	return isBusy() ? false : startTxImpl(buffer, length);
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    buffer: El buffer de recepcio.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver::startRx(
	uint8_t *buffer,
	unsigned bufferSize) {

	return isBusy() ? false : startRxImpl(buffer, bufferSize);
}


/// ----------------------------------------------------------------------
/// \brief    Aborta la comunicacio.
/// \return   True si es correcte.
///
bool AsyncSerialDriver::abort() {

    return abortImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver::initializeImpl() {

	_state = State::ready;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver::deinitializeImpl() {

	_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta la comunicacio.
/// \return   True si es correcte.
///
bool AsyncSerialDriver::abortImpl() {

    _state = State::ready;
    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del driver.
/// \return   L'estat.
///
AsyncSerialDriver::State AsyncSerialDriver::getState() const {

	return _state;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'TxCompleted'
/// \param    event: L'event
///
void AsyncSerialDriver::setTxCompletedEvent(
	const ITxCompletedEvent &event,
	bool enabled) {

	_txCompletedEvent = &event;
	_txCompletedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'RxCompleted'
/// \param    event: L'event
///
void AsyncSerialDriver::setRxCompletedEvent(
	const IRxCompletedEvent &event,
	bool enabled) {

	_rxCompletedEvent = &event;
	_rxCompletedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el inici de la transmissio.
///
void AsyncSerialDriver::notifyTxStart() {

	_state = State::transmiting;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el inici de la recepcio.
///
void AsyncSerialDriver::notifyRxStart() {

	_state = State::receiving;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de transmissio.
/// \param    length: Nombre de bytes transmessos.
///
void AsyncSerialDriver::notifyTxCompleted(
	unsigned length) {

	_state = State::ready;

	if (_txCompletedEventEnabled) {

		TxCompletedEventArgs args = {
		    .driver = this,
		    .length = length
		};

		_txCompletedEvent->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca a la funcio callback.
/// \param    length: Nombre de bytes rebuts
///
void AsyncSerialDriver::notifyRxCompleted(
	unsigned length) {

	_state = State::ready;

	if (_rxCompletedEventEnabled) {

		RxCompletedEventArgs args = {
		    .driver = this,
		    .length = length
		};

		_rxCompletedEvent->execute(args);
	}
}
