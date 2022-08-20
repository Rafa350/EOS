#include "eos.h"
#include "Controllers/Serial/eosSerialDriver_IT.h"
#include "HAL/halSYS.h"
#include "HTL/htlUART.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    uart: El modul uart a utilitzar.+
///
SerialDriver_IT::SerialDriver_IT(
	UARTAdapter &uart):

	_uart(uart),
	_state(State::reset),
	_callback(nullptr),
	_callbackParam(nullptr) {
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
/// \brief    Asigna el callback
/// \param    callback: El callback
/// \param    callbackParam: El parametre
///
void SerialDriver_IT::setCallback(
	ICallback &callback,
	void *callbackParam) {

	_callback = &callback;
    _callbackParam= callbackParam;
}


/// ----------------------------------------------------------------------
/// \brief    Invoca a la funcio callback.
/// \param    event: El event.
///
void SerialDriver_IT::invokeCallback(
	Event event) {

	if (_callback != nullptr) {

		EventArgs args;
		args.driver = this;
		args.event = event;
		args.param = _callbackParam;

		_callback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades utilitzant interrupcions.
/// \param    data: El buffer de dades.
/// \param    dataLength: Nombre de bytes en el bloc de dades.
///
bool SerialDriver_IT::send(
	const uint8_t *data,
	unsigned dataLength) {

	if (_state != State::ready)
		return false;

	else {
		_state = State::sending;

		_data = data;
		_dataLength = dataLength;

		_uart.clearInterruptFlags();
		_uart.enableInterrupt(UARTEvent::txComplete);
		_uart.enableInterrupt(UARTEvent::txEmpty);

		// En aquest moment es genera una interrupocio txEmpty
		// i comença la transmissio controlada per interrupcions.

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
			if (_dataLength != 0) {
				_dataLength--;
				_uart.write(*_data++);
			}
			break;

		case UARTEvent::txComplete:
			_uart.disableInterrupt(UARTEvent::txEmpty);
			_uart.disableInterrupt(UARTEvent::txComplete);
			invokeCallback(Event::completed);
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
