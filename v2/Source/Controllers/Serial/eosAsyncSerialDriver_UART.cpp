#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UART.h"
#include "HTL/htlUART.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    uart: El modul uart a utilitzar.
///
AsyncSerialDriver_UART::AsyncSerialDriver_UART(
	uart::UARTDeviceHandler hUART):

	_hUART {hUART},
	_uartNotifyEvent {*this, &AsyncSerialDriver_UART::uartNotifyEventHandler},
	_taskCallback {*this, &AsyncSerialDriver_UART::taskCallbackHandler} {
	//_task {100, Task::Priority::normal, "", &_taskCallback, nullptr} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_UART::initializeImpl() {

    AsyncSerialDriver::initializeImpl();

	_hUART->setNotifyEvent(_uartNotifyEvent);
	_hUART->enable();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_UART::deinitializeImpl() {

	_hUART->disable();
	_hUART->disableNotifyEvent();

    AsyncSerialDriver::deinitializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    data: El buffer de dades.
/// \param    dataLength: Nombre de bytes en el buffer de dades..
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UART::transmitImpl(
	const uint8_t *data,
	int dataLength) {

	if ((data == nullptr) || (dataLength == 0))
		return false;

	else if (isBusy())
		return false;

	else {
		notifyTxStart();

		_hUART->transmit_IRQ(data,  dataLength);

		// En aquest moment es genera una interrupcio txEmpty
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
bool AsyncSerialDriver_UART::receiveImpl(
	uint8_t *data,
	int dataSize) {

	if ((data == nullptr) || (dataSize == 0))
		return false;

	else if (isBusy())
		return false;

	else {
		notifyRxStart();

		_hUART->receive_IRQ(data, dataSize);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles en la UART.

		return true;
	}
}


void AsyncSerialDriver_UART::taskCallbackHandler(
	const TaskCallbackArgs &args) {

	Task::delay(1000000);
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha una notificacio del UART
/// \param    sender: L'objecte que genera el event.
/// \param    args: Parametres de la notificacio.
///
void AsyncSerialDriver_UART::uartNotifyEventHandler(
	const htl::uart::UARTDevice *sender,
	const htl::uart::NotifyEventArgs &args) {

	switch (args.id) {
		case htl::uart::NotifyID::txCompleted:
			notifyTxCompleted(args.TxCompleted.length);
			break;

		case htl::uart::NotifyID::rxCompleted:
			notifyRxCompleted(args.RxCompleted.length);
			break;

		default:
			break;
	}
}
