#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver.h"


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
/// \param    data: El buffer de dades.
/// \param    dataLength: Longitut de les dades en bytes.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver::transmit(
	const uint8_t *data,
	int dataLength) {

	return isBusy() ? false : transmitImpl(data, dataLength);
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    data: El buffer de recepcio.
/// \param    dataSize: El tasmany del buffer en bytes.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver::receive(
	uint8_t *data,
	int dataSize) {

	return isBusy() ? false : receiveImpl(data, dataSize);
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
/// \param    count: Nombre de bytes transmessos.
///
void AsyncSerialDriver::notifyTxCompleted(
	int count) {

	_state = State::ready;

	if (_txCompletedEventEnabled) {

		TxCompletedEventArgs args;
		args.count = count;

		_txCompletedEvent->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca a la funcio callback.
/// \param    count: Nombre de bytes rebuts
///
void AsyncSerialDriver::notifyRxCompleted(
	int count) {

	_state = State::ready;

	if (_rxCompletedEventEnabled) {

		RxCompletedEventArgs args;
		args.count = count;

		_rxCompletedEvent->execute(args);
	}
}
