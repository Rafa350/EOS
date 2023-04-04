#include "eos.h"
#include "Controllers/Serial/eosCircularSerialDriver_I2CSlave.h"
#include "htl/htlI2C.h"


using namespace eos;
using namespace htl;


CircularSerialDriver_I2CSlave::CircularSerialDriver_I2CSlave(
	uint8_t *txBuffer,
	uint16_t txBufferSize,
	uint8_t *rxBuffer,
	uint8_t rxBufferSize,
	htl::I2CHandler hI2C) :

	CircularSerialDriver(txBuffer, txBufferSize, rxBuffer, rxBufferSize),
	_hI2C(hI2C) {

}


void CircularSerialDriver_I2CSlave::initializeImpl() {

}


void CircularSerialDriver_I2CSlave::deinitializeImpl() {

}


uint16_t CircularSerialDriver_I2CSlave::transmitImpl(
	const uint8_t *data,
	uint16_t dataLength) {

	while (dataLength--)
		txPush(*data++);

	return dataLength;
}


void CircularSerialDriver_I2CSlave::rxInterruptHandler() {

	// Coincidencia amb l'adressa
	//
	if (_hI2C->getFlag(I2CFlag::addr)) {
		_hI2C->clearFlag(I2CFlag::addr);
		_hI2C->disableInterrupt(I2CInterrupt::addr);
		_hI2C->enableInterrupt(I2CInterrupt::stop);
		_hI2C->enableInterrupt(I2CInterrupt::rx);
	}

	// Buffer de recepcio ple
	//
	else if (_hI2C->getFlag(I2CFlag::rxne)) {
		uint8_t data = _hI2C->read();
		uint16_t availableSpace = rxAvailableSpace();
		if (availableSpace > 0) {
			rxPush(data);

			// Si nomes queda espai per rebre un byte, fa que generi un NACK
			// automaticamen quant es rebi el proper
			//
			if (availableSpace == 1)
				_hI2C->nack();
		}
	}

	// Deteccio de la condicio stop
	//
	else if (_hI2C->getFlag(I2CFlag::stop)) {
		_hI2C->clearFlag(I2CFlag::stop);
		_hI2C->disableInterrupt(I2CInterrupt::rx);
		_hI2C->disableInterrupt(I2CInterrupt::stop);
		_hI2C->setInterruptFunction(nullptr, nullptr);
		_hI2C->disable();
		//notifyRxCompleted(_rxCount);
	}
}


void CircularSerialDriver_I2CSlave::txInterruptHandler() {

}


void CircularSerialDriver_I2CSlave::rxInterruptFunction(
	htl::I2CInterruptParam param) {

	CircularSerialDriver_I2CSlave *driver = reinterpret_cast<CircularSerialDriver_I2CSlave*>(param);
	driver->rxInterruptHandler();
}


void CircularSerialDriver_I2CSlave::txInterruptFunction(
	htl::I2CInterruptParam param) {

	CircularSerialDriver_I2CSlave *driver = reinterpret_cast<CircularSerialDriver_I2CSlave*>(param);
	driver->txInterruptHandler();
}

