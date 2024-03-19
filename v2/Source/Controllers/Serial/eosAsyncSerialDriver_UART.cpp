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
	_devUART->enable(); // TODO: Es necesari????
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
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Nombre de bytes en el buffer de dades..
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UART::transmitImpl(
	const uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

	if (isBusy())
		return false;

	else {
		notifyTxStart();

		_devUART->transmit_IRQ(buffer, bufferSize);

		// En aquest moment es genera una interrupcio txEmpty
		// i comença la transmissio controlada per interrupcions.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UART::receiveImpl(
	uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

	if (isBusy())
		return false;

	else {
		notifyRxStart();

		_devUART->receive_IRQ(buffer, bufferSize);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles en la UART.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb les notificacions del UART
/// \param    devUART: El dispositiu UART que genera el event.
/// \param    args: Parametres del event.
///
void AsyncSerialDriver_UART::uartNotifyEventHandler(
	DevUART *devUART,
	UARTNotifyEventArgs &args) {

	switch (args.id) {
		case htl::uart::NotifyID::txComplete:
			notifyTxCompleted(args.TxComplete.length);
			break;

		case htl::uart::NotifyID::rxComplete:
			notifyRxCompleted(args.RxComplete.length);
			break;

		default:
			break;
	}
}
