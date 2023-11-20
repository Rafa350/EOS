#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UART.h"
#include "HTL/htlUART.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUART: El dispositiu uart a utilitzar.
///
AsyncSerialDriver_UART::AsyncSerialDriver_UART(
	DevUART *devUART):

	_devUART {devUART},
	_uartNotifyEvent {*this, &AsyncSerialDriver_UART::uartNotifyEventHandler} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_UART::initializeImpl() {

    AsyncSerialDriver::initializeImpl();

	_devUART->setNotifyEvent(_uartNotifyEvent);
	_devUART->enable();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_UART::deinitializeImpl() {

	_devUART->disable();
	_devUART->disableNotifyEvent();

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

    eosAssert(data != nullptr);
    eosAssert(dataLength > 0);

	if (isBusy())
		return false;

	else {
		notifyTxStart();

		_devUART->transmit_IRQ(data,  dataLength);

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

    eosAssert(data != nullptr);
    eosAssert(dataLength > 0);

	if (isBusy())
		return false;

	else {
		notifyRxStart();

		_devUART->receive_IRQ(data, dataSize);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles en la UART.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha una notificacio del UART
/// \param    sender: L'objecte que genera el event.
/// \param    args: Parametres de la notificacio.
///
void AsyncSerialDriver_UART::uartNotifyEventHandler(
	const DevUART *sender,
	const UARTNotifyEventArgs &args) {

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
