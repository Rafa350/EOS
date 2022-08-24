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
/// \brief    Destructor
///
AsyncSerialDriver::~AsyncSerialDriver() {

	if (_state != State::reset)
		deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver::initialize() {

	_state = State::ready;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver::deinitialize() {

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
	ITxCompletedCallback &callback) {

	_txCompletedCallback = &callback;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el callback del event 'RxCompleted'
/// \param    callback: El callback
///
void AsyncSerialDriver::enableRxCompletedCallback(
	IRxCompletedCallback &callback) {

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
	unsigned count) {

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
	unsigned count) {

	_state = State::ready;

	if (_rxCompletedCallback != nullptr) {

		RxCompletedEventArgs args;
		args.count = count;

		_rxCompletedCallback->execute(args);
	}
}
