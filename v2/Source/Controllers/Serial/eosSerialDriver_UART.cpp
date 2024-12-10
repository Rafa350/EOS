#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_UART.h"
#include "HTL/htlUART.h"


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
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del driver.
///
void SerialDriver_UART::onInitialize() {

    _devUART->setNotifyEvent(_uartNotifyEvent);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
///
void SerialDriver_UART::onDeinitialize() {

    _devUART->disableNotifyEvent();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la transmissio de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes a transmetre.
///
void SerialDriver_UART::onTransmit(
	const uint8_t *buffer,
	unsigned length) {

    _devUART->transmit_IRQ(buffer, length);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la recepcio de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
///
void SerialDriver_UART::onReceive(
	uint8_t *buffer,
	unsigned bufferSize) {

    _devUART->receive_IRQ(buffer, bufferSize);
}


/// ----------------------------------------------------------------------
/// \brief    Reb les notificacions del UART
/// \param    args: Parametres del event.
///
void SerialDriver_UART::uartNotifyEventHandler(
	UARTNotifyID id,
	UARTNotifyEventArgs * const args) {

	switch (id) {
		case UARTNotifyID::txCompleted:
		    notifyTxCompleted(args->txCompleted.length);
			break;

		case UARTNotifyID::rxCompleted:
		    notifyRxCompleted(args->rxCompleted.length);
			break;
	}
}
