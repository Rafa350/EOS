#include "eos.h"
#include "Controllers/Serial/eosCircularSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Conmstructor.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txBufferSize: Tamany del buffer de transmissio.
/// \param    rxBuffer: Buffer de recepcio.
/// \param    rxBufferSize: Tamany del buffer de recepcio.
///
CircularSerialDriver::CircularSerialDriver(
	uint8_t *txBuffer,
	uint16_t txBufferSize,
	uint8_t *rxBuffer,
	uint8_t rxBufferSize) :

	_txBufferFullCallback(nullptr),
	_rxBufferNotEmptyCallback(nullptr),
	_txBuffer(txBuffer, txBufferSize),
	_rxBuffer(rxBuffer, rxBufferSize) {

}


void CircularSerialDriver::notifyTxBufferFull() {

	if (_txBufferFullCallback != nullptr) {
		TxBufferFullEventArgs args;
		_txBufferFullCallback->execute(args);
	}
}


void CircularSerialDriver::notifyRxBufferNotEmpty() {

	if (_rxBufferNotEmptyCallback != nullptr) {
		RxBufferNotEmptyEventArgs args;
		_rxBufferNotEmptyCallback->execute(args);
	}
}


void CircularSerialDriver::initialize() {

	initializeImpl();
}


void CircularSerialDriver::deinitialize() {

	deinitializeImpl();
}


void CircularSerialDriver::txPush(
	uint8_t data) {

	_txBuffer.push(data);
}


void CircularSerialDriver::rxPush(
	uint8_t data) {

	_rxBuffer.push(data);
}


uint16_t CircularSerialDriver::transmit(
	const uint8_t *data,
	uint16_t dataLength) {

	transmitImpl(data, dataLength);
}


