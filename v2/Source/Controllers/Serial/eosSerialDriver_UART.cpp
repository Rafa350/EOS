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
	_uartNotifyEvent {*this, &SerialDriver_UART::uartNotifyEventHandler} /*,
    _taskEvent {*this, &AsyncSerialDriver_UART::taskEventHandler},
    _task {128, Task::Priority::normal, nullptr, &_taskEvent, nullptr},
    _taskLock {} */ {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriver_UART::initializeImpl() {

    SerialDriverBase::initializeImpl();

	_devUART->setNotifyEvent(_uartNotifyEvent);
	_devUART->enable();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriver_UART::deinitializeImpl() {

	_devUART->disable();
	_devUART->disableNotifyEvent();

    SerialDriverBase::deinitializeImpl();
}

/*
void AsyncSerialDriver_UART::taskEventHandler(
    const TaskCallbackArgs &args) {

    while (true) {
        _taskLock.wait(unsigned(-1));
    }
}
*/

/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes a transmetre.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UART::startTxImpl(
	const uint8_t *buffer,
	unsigned length) {

    eosAssert(buffer != nullptr);
    eosAssert(length > 0);

	if (isBusy())
		return false;

	else {
		notifyTxStart();

		_devUART->transmit_IRQ(buffer, length);

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
bool AsyncSerialDriver_UART::startRxImpl(
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
/// \param    args: Parametres del event.
///
void AsyncSerialDriver_UART::uartNotifyEventHandler(
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
