#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
AsyncSerialDriver::AsyncSerialDriver() :

	_state(State::reset),
	_txCompletedCallback(nullptr),
	_rxCompletedCallback(nullptr),
	_abortedCallback(nullptr) {
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
/// \param    dataLength: Longitut del buffer en bytes.
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
/*
	if constexpr(sizeof(_state) == sizeof(uint32_t))
		return (AsyncSerialDriver::State) __LDREXW((volatile uint32_t*)&_state);

	if constexpr(sizeof(_state) == sizeof(uint16_t))
		return (AsyncSerialDriver::State) __LDREXH((volatile uint16_t*)&_state);

	if constexpr(sizeof(_state) == sizeof(uint8_t))
		return (AsyncSerialDriver::State) __LDREXB((volatile uint8_t*)&_state);*/
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el callback del event 'TxCompleted'
/// \param    callback: El callback
///
void AsyncSerialDriver::enableTxCompletedCallback(
	const ITxCompletedCallback &callback) {

	_txCompletedCallback = &callback;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el callback del event 'RxCompleted'
/// \param    callback: El callback
///
void AsyncSerialDriver::enableRxCompletedCallback(
	const IRxCompletedCallback &callback) {

	_rxCompletedCallback = &callback;
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

	if (_txCompletedCallback != nullptr) {

		TxCompletedEventArgs args;
		args.count = count;

		_txCompletedCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca a la funcio callback.
/// \param    count: Nombre de bytes rebuts
///
void AsyncSerialDriver::notifyRxCompleted(
	int count) {

	_state = State::ready;

	if (_rxCompletedCallback != nullptr) {

		RxCompletedEventArgs args;
		args.count = count;

		_rxCompletedCallback->execute(args);
	}
}
