#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_I2CSlave.h"
#include "HTL/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hI2C: El modul I2C a utilitzar.
///
AsyncSerialDriver_I2CSlave::AsyncSerialDriver_I2CSlave(
	i2c::I2CSlaveDeviceHandler i2c):

	_i2c(i2c) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_I2CSlave::initializeImpl() {

	AsyncSerialDriver::initializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_I2CSlave::deinitializeImpl() {

	_i2c->setInterruptFunction(nullptr, nullptr);

	AsyncSerialDriver::deinitializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Transmioteix un bloc de dades.
/// \param    data: El bloc de dades.
/// \param    dataLength: Longitut del bloc de dades.
///
bool AsyncSerialDriver_I2CSlave::transmitImpl(
	const uint8_t *data,
	int dataLength) {

	if ((data == nullptr) || (dataLength == 0))
		return false;

	else {
		notifyTxStart();

		_txData = data;
		_txLength = dataLength;
		_txCount = 0;

		_i2c->setInterruptFunction(txInterruptFunction, this);
		_i2c->enable();
		_i2c->enableInterrupt(I2CInterrupt::addr);

		// En aquest moment es genera una interrupcio
		// i comença la transmissio controlada per interrupcions.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    data: Buffer de dades.
/// \param    dataSize: Tamany del buffer de dades.
///
bool AsyncSerialDriver_I2CSlave::receiveImpl(
	uint8_t *data,
	int dataSize) {

	if ((data == nullptr) || (dataSize == 0))
		return false;

	else {
		notifyRxStart();

		_rxData = data;
		_rxSize = dataSize;
		_rxCount = 0;

		_i2c->setInterruptFunction(rxInterruptFunction, this);
		_i2c->enable();
		_i2c->enableInterrupt(I2CInterrupt::addr);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions per transmissio.
///
void AsyncSerialDriver_I2CSlave::txInterruptFunction(
	i2c::I2CInterruptContext *context) {

	switch (context->status) {

		case i2c::I2CInterruptStatus::addrMatch:
			break;

		case i2c::I2CInterruptStatus::rxCompleted:
			notifyTxCompleted(context->count);
			break;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions per recepcio.
///
void AsyncSerialDriver_I2CSlave::rxInterruptFunction(
	i2c::I2CInterruptContext *context) {

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
		if (_rxCount < _rxSize) {
			*_rxData++ = data;
			_rxCount++;

			// Si nomes queda per rebre un, fa que generi un NACK
			// automaticamen quant es rebi l'ultim
			//
			if (_rxCount == _rxSize - 1)
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
		notifyRxCompleted(_rxCount);
	}
}
