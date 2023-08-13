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
	uart::UARTDeviceHandler uart):

	_uart(uart),
	_txCompletedEvent(*this, &AsyncSerialDriver_UART::txCompletedEventHandler),
	_rxCompletedEvent(*this, &AsyncSerialDriver_UART::rxCompletedEventHandler) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_UART::initializeImpl() {

    AsyncSerialDriver::initializeImpl();

	_uart->enableTxCompletedCallback(_txCompletedEvent);
	_uart->enableRxCompletedCallback(_rxCompletedEvent);
	_uart->enable();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_UART::deinitializeImpl() {

	_uart->disable();
	_uart->disableTxCompletedCallback();
	_uart->disableRxCompletedCallback();

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

		_uart->transmit(data,  dataLength);

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

		_uart->receive(data, dataSize);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles en la UART.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant acaba la transmissio.
/// \param    buffer: El buffer de dades.
/// \param    count: En nombre de bytes transmessos.
///
void AsyncSerialDriver_UART::txCompletedEventHandler(
	const uint8_t *buffer,
	uint16_t count) {

	notifyTxCompleted(count);
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant acaba la recepcio.
/// \param    buffer: El buffer de dades.
/// \param    count: El nombre de bytes rebuts.
///
void AsyncSerialDriver_UART::rxCompletedEventHandler(
	const uint8_t *buffer,
	uint16_t count) {

	notifyRxCompleted(count);
}
