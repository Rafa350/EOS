#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "HAL/halSYS.h"
#include "HTL/htlUART.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    uart: El modul uart a utilitzar.+
///
SerialDriver::SerialDriver(
	UARTAdapter &uart):

	_uart(uart) {
}


SerialDriver::~SerialDriver() {

}


void SerialDriver::initialize() {

}


void SerialDriver::deinitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Transmet un bloc de dades.
/// \param    data: El buffer de dades.
/// \param    dataLength: Nombre de bytes en el buffer de dades.
/// \param    dataCount: El nombre de bytes enviants.
/// \param    timeout: El timeout.
/// \return   True si tot es correcte.
///
bool SerialDriver::send(
	const uint8_t *data,
	unsigned dataLength,
	unsigned &dataCount,
	unsigned timeout) {

	unsigned startTime = halSYSGetTick();

	dataCount = 0;

	// Desactiva les interrupcions perque no interfereixin
	//
	_uart.clearInterruptFlags();
	_uart.disableInterrupt(UARTEvent::txEmpty);
	_uart.disableInterrupt(UARTEvent::txComplete);

	// Bucle per procesar els bytes de dades.
	//
	while (dataCount < dataLength) {

		// Espera que el buffer de transmissio estigui buit
		///
		while (!_uart.getInterruptFlag(UARTEvent::txEmpty))
			if (halSYSCheckTimeout(startTime, timeout)) {
				return false;
			}

		_uart.write(*data++);
		dataCount++;
	}

	// Espera que finalitzi la transmissio
	//
	while (!_uart.getInterruptFlag(UARTEvent::txComplete))
		if (halSYSCheckTimeout(startTime, timeout)) {
			return false;
		}
	_uart.clearInterruptFlag(UARTEvent::txComplete);

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un blocm  de dades.
/// \param    data: El buffer de dades.
/// \param    dataSize: El tamany del buffer.
/// \param    dataCount: El nombre de bytes rebuts.
/// \param    timeout: El timeout.
/// \return   True si tot es correcte.
///
bool SerialDriver::receive(
	uint8_t *data,
	unsigned dataSize,
	unsigned &dataCount,
	unsigned timeout) {

	unsigned startTime = halSYSGetTick();

	dataCount = 0;

	while (dataCount < dataSize) {

		while (!_uart.getInterruptFlag(UARTEvent::rxNotEmpty))
			if (halSYSCheckTimeout(startTime, timeout)) {
				return false;
			}

		*data++ = _uart.read();
		dataCount++;
	}

	return true;
}

