#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_UART.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUART: El dispositiu uart a utilitzar.
///
SerialDriver_UART::SerialDriver_UART(
	DevUART *devUART):

	_devUART {devUART},
	_uartNotifyEvent {*this, &SerialDriver_UART::uartNotifyEventHandler} {

	eosAssert(devUART != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_UART::onInitialize() {

	eosAssert(_devUART != nullptr);

	_devUART->setNotifyEvent(_uartNotifyEvent);
    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_UART::onDeinitialize() {

	eosAssert(_devUART != nullptr);

	_devUART->disableNotifyEvent();
    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la transmissio de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes a transmetre.
/// \return   True si tot es correcte.
///
bool SerialDriver_UART::onTransmit(
	const uint8_t *buffer,
	unsigned length) {

	eosAssert(buffer != nullptr);
	eosAssert(length > 0);
	eosAssert(_devUART != nullptr);

    return _devUART->transmit_IRQ(buffer, length).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la recepcio de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
/// \return   True si tot es correcte.
///
bool SerialDriver_UART::onReceive(
	uint8_t *buffer,
	unsigned bufferSize) {

	eosAssert(buffer != nullptr);
	eosAssert(bufferSize > 0);
	eosAssert(_devUART != nullptr);

	return _devUART->receive_IRQ(buffer, bufferSize).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Aborta l'operacio en curs.
/// \return   True si tot es correcte.
///
bool SerialDriver_UART::onAbort() {

	eosAssert(_devUART != nullptr);

	switch (getState()) {
		case State::receiving:
			return _devUART->abortReception().isSuccess();

		case State::transmiting:
			return _devUART->abortTransmission().isSuccess();

		default:
			return false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb les notificacions del UART
/// \param    args: Parametres del event.
///
void SerialDriver_UART::uartNotifyEventHandler(
	UARTNotifyID id,
	UARTNotifyEventArgs * const args) {

	eosAssert(args != nullptr);

	switch (id) {

		// Notificacio del final de la transmissio
		//
		case UARTNotifyID::txCompleted:
		    notifyTxCompleted(args->txCompleted.length, args->irq);
			break;

    	// Notificacio del final de la recepcio
		//
		case UARTNotifyID::rxCompleted:
		    notifyRxCompleted(args->rxCompleted.length, args->irq);
			break;

    	// Notificacio un error en la comunicacio
		//
		case UARTNotifyID::error:
			break;

    	// Notificacio nula
		//
		case UARTNotifyID::null:
			break;
	}
}
