#include "eos.h"
#include "Controllers/Serial/eosSerialDriver_IT.h"
#include "HAL/halSYS.h"
#include "HTL/htlUART.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    uart: El modul uart a utilitzar.
///
SerialDriver_IT::SerialDriver_IT(
	UARTAdapter &uart):

	_uart(uart),
	_state(State::reset),
	_txCompletedCallback(nullptr),
	_rxCompletedCallback(nullptr),
	_abortedCallback(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor
///
SerialDriver_IT::~SerialDriver_IT() {

	if (_state != State::reset)
		deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriver_IT::initialize() {

	_uart.setInterruptFunction(interruptHandler, this);
	_state = State::ready;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriver_IT::deinitialize() {

	_uart.disableInterrupts();
	_uart.clearInterruptFlags();
	_uart.setInterruptFunction(nullptr, nullptr);
	_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del driver.
/// \return   L'estat.
///
SerialDriver_IT::State SerialDriver_IT::getState() const {

	if constexpr(sizeof(_state) == sizeof(uint32_t))
		return (SerialDriver_IT::State) __LDREXW((volatile uint32_t*)&_state);

	if constexpr(sizeof(_state) == sizeof(uint16_t))
		return (SerialDriver_IT::State) __LDREXH((volatile uint16_t*)&_state);

	if constexpr(sizeof(_state) == sizeof(uint8_t))
		return (SerialDriver_IT::State) __LDREXB((volatile uint8_t*)&_state);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el callback del event 'TxCompleted'
/// \param    callback: El callback
///
void SerialDriver_IT::setTxCompletedCallback(
	ITxCompletedCallback &callback) {

	_txCompletedCallback = &callback;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el callback del event 'RxCompleted'
/// \param    callback: El callback
///
void SerialDriver_IT::setRxCompletedCallback(
	IRxCompletedCallback &callback) {

	_rxCompletedCallback = &callback;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de transmissio.
///
void SerialDriver_IT::notifyTxCompleted() {

	if (_txCompletedCallback != nullptr) {

		TxCompletedEventArgs args;
		args.count = _txCount;

		_txCompletedCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca a la funcio callback.
/// \param    count: Nombre de bytes rebuts
///
void SerialDriver_IT::notifyRxCompleted() {

	if (_rxCompletedCallback != nullptr) {

		RxCompletedEventArgs args;
		args.count = _rxCount;

		_rxCompletedCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    data: El buffer de dades.
/// \param    dataLength: Nombre de bytes en el buffer de dades..
/// \return   True si tot es correcte.
///
bool SerialDriver_IT::transmit(
	const uint8_t *data,
	unsigned dataLength) {

	if ((data == nullptr) || (dataLength == 0))
		return false;

	else if (_state != State::ready)
		return false;

	else {
		_state = State::transmiting;

		_txData = data;
		_txLength = dataLength;
		_txCount = 0;

		_uart.clearInterruptFlags();
		_uart.enableInterrupt(UARTEvent::txEmpty);

		// En aquest moment es genera una interrupocio txEmpty
		// i comença la transmissio controlada per interrupcions.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    data: El buffer de dades.
/// \param    dataSize: El tamany en bytes del buffer de dades.
/// \return   True si tot es correcte.
///
bool SerialDriver_IT::receive(
	uint8_t *data,
	unsigned dataSize) {

	if ((data == nullptr) || (dataSize == 0))
		return false;

	else if (_state != State::ready)
		return false;

	else {
		_state = State::receiving;

		_rxData = data;
		_rxSize = dataSize;
		_rxCount = 0;

		_uart.clearInterruptFlags();
		_uart.enableInterrupt(UARTEvent::rxNotEmpty);
		_uart.enableInterrupt(UARTEvent::rxTimeout);

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions.
/// \param    event: El event.
///
void SerialDriver_IT::interruptHandler(
	UARTEvent event) {

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wswitch"
	#pragma GCC diagnostic ignored "-Wswitch-default"
	switch (event) {
		case UARTEvent::txEmpty:
			if (_txCount < _txLength) {
				_txCount++;
				_uart.write(*_txData++);
				if (_txCount == _txLength) {
					_uart.disableInterrupt(UARTEvent::txEmpty);
					_uart.enableInterrupt(UARTEvent::txComplete);
				}
			}
			break;

		case UARTEvent::txComplete:
			_uart.disableInterrupt(UARTEvent::txEmpty);
			_uart.disableInterrupt(UARTEvent::txComplete);
			notifyTxCompleted();
			_state = State::ready;
			break;

		case UARTEvent::rxNotEmpty:
			if (_rxCount < _rxSize) {
				_rxCount++;
				*_rxData++ = _uart.read();
				if (_rxCount == _rxSize) {
					_uart.disableInterrupt(UARTEvent::rxNotEmpty);
					_uart.disableInterrupt(UARTEvent::rxTimeout);
					notifyRxCompleted();
					_state = State::ready;
				}
			}
			break;

		case UARTEvent::rxTimeout:
			_uart.disableInterrupt(UARTEvent::rxNotEmpty);
			_uart.disableInterrupt(UARTEvent::rxTimeout);
			notifyRxCompleted();
			_state = State::ready;
			break;
	}
	#pragma GCC diagnostic pop
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions.
/// \param    event: EL event.
/// \param    param: EL parametre.
///
void SerialDriver_IT::interruptHandler(
	UARTEvent event,
	UARTInterruptParam param) {

	SerialDriver_IT *driver = reinterpret_cast<SerialDriver_IT*>(param);
	driver->interruptHandler(event);
}
