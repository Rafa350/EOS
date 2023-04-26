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
	_txCompletedCallback(*this, &AsyncSerialDriver_UART::txCompletedHandler){
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_UART::initializeImpl() {

    AsyncSerialDriver::initializeImpl();

	_uart->enableTxCompletedCallback(_txCompletedCallback);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_UART::deinitializeImpl() {

	_uart->disableTxCompletedCallback();

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

		_rxData = data;
		_rxSize = dataSize;
		_rxCount = 0;

		/*
		_hUART->enableRX();
		_hUART->enableInterrupt(UARTInterrupt::rxNotEmpty);
        #ifdef EOS_PLATFORM_STM32
			_hUART->enableInterrupt(UARTInterrupt::rxTimeout);
        #endif
*/
		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles en la UART.

		return true;
	}
}


void AsyncSerialDriver_UART::txCompletedHandler(
	const uint8_t *buffer,
	uint16_t size) {

	notifyTxCompleted(size);
}


/*

/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions.
/// \param    event: El event.
///
#if defined(EOS_PLATFORM_STM32)
void AsyncSerialDriver_UART::interruptHandler() {

	if (_hUART->isInterruptEnabled(UARTInterrupt::txEmpty)) {

		if (_hUART->getFlag(UARTFlag::txEmpty)) {
			if (_txCount < _txLength) {
				_txCount++;
				_hUART->write(*_txData++);
				if (_txCount == _txLength) {
					_hUART->disableInterrupt(UARTInterrupt::txEmpty);
					_hUART->enableInterrupt(UARTInterrupt::txComplete);
				}
			}
		}
	}

	if (_hUART->isInterruptEnabled(UARTInterrupt::txComplete)) {

		if (_hUART->getFlag(UARTFlag::txComplete)) {
			_hUART->clearFlag(UARTFlag::txComplete);
			_hUART->disableInterrupt(UARTInterrupt::txEmpty);
			_hUART->disableInterrupt(UARTInterrupt::txComplete);
			_hUART->disableTX();
			notifyTxCompleted(_txCount);
		}
	}

	if (_hUART->isInterruptEnabled(UARTInterrupt::rxNotEmpty)) {

		if (_hUART->getFlag(UARTFlag::rxNotEmpty)) {
			if (_rxCount < _rxSize) {
				_rxCount++;
				*_rxData++ = _hUART->read();
				if (_rxCount == _rxSize) {
					_hUART->disableInterrupt(UARTInterrupt::rxNotEmpty);
					_hUART->disableInterrupt(UARTInterrupt::rxTimeout);
					_hUART->disableRX();
					notifyRxCompleted(_rxCount);
				}
			}
		}
	}

	if (_hUART->isInterruptEnabled(UARTInterrupt::rxTimeout)) {

		if (_hUART->getFlag(UARTFlag::rxTimeout)) {
			_hUART->clearFlag(UARTFlag::rxTimeout);
			_hUART->disableInterrupt(UARTInterrupt::rxNotEmpty);
			_hUART->disableInterrupt(UARTInterrupt::rxTimeout);
			_hUART->disableRX();
			notifyRxCompleted(_rxCount);
		}
	}
}


#elif defined (EOS_PLATFORM_PIC32)
void AsyncSerialDriver_UART::interruptHandler() {

    if (_hUART->getFlag(UARTFlag::txEmpty)) {
        if (_txCount < _txLength) {
            _txCount++;
            _hUART->write(*_txData++);
        }
        else {
            _hUART->disableInterrupt(UARTInterrupt::txEmpty);
            notifyTxCompleted(_txCount);
        }
    }

    if (_hUART->getFlag(UARTFlag::rxNotEmpty)) {
    }
}


#else
#error "Undefined EOS_PLATFORM_XXXX"
#endif
*/

