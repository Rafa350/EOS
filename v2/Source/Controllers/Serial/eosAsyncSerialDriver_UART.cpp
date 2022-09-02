#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UART.h"
#include "HAL/halSYS.h"
#include "HTL/htlUART.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    uart: El modul uart a utilitzar.
///
AsyncSerialDriver_UART::AsyncSerialDriver_UART(
	UARTAdapter &uart):

	_uart(uart) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_UART::initialize() {

    AsyncSerialDriver::initialize();

	_uart.setInterruptFunction(interruptHandler, this);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_UART::deinitialize() {

	_uart.setInterruptFunction(nullptr, nullptr);

    AsyncSerialDriver::deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades de forma asincrona.
/// \param    data: El buffer de dades.
/// \param    dataLength: Nombre de bytes en el buffer de dades..
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_UART::transmit(
	const uint8_t *data,
	unsigned dataLength) {

	if ((data == nullptr) || (dataLength == 0))
		return false;

	else if (isBusy())
		return false;

	else {
		notifyTxStart();

		_txData = data;
		_txLength = dataLength;
		_txCount = 0;

		_uart.enableTX();
		_uart.enableInterrupt(UARTEvent::txEmpty);

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
bool AsyncSerialDriver_UART::receive(
	uint8_t *data,
	unsigned dataSize) {

	if ((data == nullptr) || (dataSize == 0))
		return false;

	else if (isBusy())
		return false;

	else {
		notifyRxStart();

		_rxData = data;
		_rxSize = dataSize;
		_rxCount = 0;

		_uart.enableRX();
		_uart.enableInterrupt(UARTEvent::rxNotEmpty);
        #ifdef EOS_PLATFORM_STM32
            _uart.enableInterrupt(UARTEvent::rxTimeout);
        #endif

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles en la UART.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions.
/// \param    event: El event.
///
#if defined(EOS_PLATFORM_STM32)
void AsyncSerialDriver_UART::interruptHandler(
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
			_uart.disableTX();
			notifyTxCompleted(_txCount);
			break;

		case UARTEvent::rxNotEmpty:
			if (_rxCount < _rxSize) {
				_rxCount++;
				*_rxData++ = _uart.read();
				if (_rxCount == _rxSize) {
					_uart.disableInterrupt(UARTEvent::rxNotEmpty);
					_uart.disableInterrupt(UARTEvent::rxTimeout);
					notifyRxCompleted(_rxCount);
				}
			}
			break;

		case UARTEvent::rxTimeout:
			_uart.disableInterrupt(UARTEvent::rxNotEmpty);
			_uart.disableInterrupt(UARTEvent::rxTimeout);
			notifyRxCompleted(_rxCount);
			break;
	}
	#pragma GCC diagnostic pop
}


#elif defined (EOS_PLATFORM_PIC32)
void AsyncSerialDriver_UART::interruptHandler(
	UARTEvent event) {

    switch (event) {
        case UARTEvent::txEmpty:
            if (_txCount < _txLength) {
                _txCount++;
                _uart.write(*_txData++);
            }
            else {
                _uart.disableInterrupt(UARTEvent::txEmpty);
                notifyTxCompleted(_txCount);
            }
            break;

        case UARTEvent::rxNotEmpty:
            break;
    }
}


#else
#error "Undefined EOS_PLATFORM_XXXX"
#endif


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions.
/// \param    event: EL event.
/// \param    param: EL parametre.
///
void AsyncSerialDriver_UART::interruptHandler(
	UARTEvent event,
	UARTInterruptParam param) {

	AsyncSerialDriver_UART *driver = reinterpret_cast<AsyncSerialDriver_UART*>(param);
	driver->interruptHandler(event);
}
