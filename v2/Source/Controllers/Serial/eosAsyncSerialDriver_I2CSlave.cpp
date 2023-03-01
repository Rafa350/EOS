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
	I2CHandler hI2C):

	_hI2C(hI2C) {

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

	_hI2C->setInterruptFunction(nullptr, nullptr);

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

	else if (isBusy())
		return false;

	else {
		notifyTxStart();

		_txData = data;
		_txLength = dataLength;
		_txCount = 0;

		_hI2C->setInterruptFunction(txInterruptFunction, this);
		_hI2C->enable();
		_hI2C->enableInterrupt(I2CInterrupt::addr);

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

	else if (isBusy())
		return false;

	else {
		notifyRxStart();

		_rxData = data;
		_rxSize = dataSize;
		_rxCount = 0;

		_hI2C->setInterruptFunction(rxInterruptFunction, this);
		_hI2C->enable();
		_hI2C->enableInterrupt(I2CInterrupt::addr);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions per transmissio.
///
void AsyncSerialDriver_I2CSlave::txInterruptHandler() {

	// Coincidencia amb l'adressa
	//
	if (_hI2C->getFlag(I2CFlag::addr)) {
		_hI2C->clearFlag(I2CFlag::addr);
		_hI2C->disableInterrupt(I2CInterrupt::addr);
		_hI2C->enableInterrupt(I2CInterrupt::stop);
		_hI2C->enableInterrupt(I2CInterrupt::tx);
		_hI2C->write(*_txData++);
		_txCount++;
	}

	// Deteccio de la condicio stop
	//
	else if (_hI2C->getFlag(I2CFlag::stop)) {
		_hI2C->clearFlag(I2CFlag::stop);
		_hI2C->disableInterrupt(I2CInterrupt::tx);
		_hI2C->disableInterrupt(I2CInterrupt::stop);
		_hI2C->setInterruptFunction(nullptr, nullptr);
		_hI2C->disable();
		notifyTxCompleted(_rxCount);
	}

	// Deteccio de NACK
	//
	else if (_hI2C->getFlag(I2CFlag::nack)) {
		_hI2C->clearFlag(I2CFlag::nack);
	}

	// Buffer de tramsmssio buit
	//
	else if (_hI2C->getFlag(I2CFlag::txis)) {
		if (_txCount < _txLength) {
			_hI2C->write(*_txData++);
			_txCount++;
		}
		else
			_hI2C->disableInterrupt(I2CInterrupt::tx);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions per recepcio.
///
void AsyncSerialDriver_I2CSlave::rxInterruptHandler() {

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


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions per transmissio.
/// \param    param: L'objecte AsyncSerialDriver_I2C.
///
void AsyncSerialDriver_I2CSlave::txInterruptFunction(
	htl::I2CInterruptParam param) {

	AsyncSerialDriver_I2CSlave *driver = reinterpret_cast<AsyncSerialDriver_I2CSlave*>(param);
	driver->txInterruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions per recepcio.
/// \param    param: L'objecte AsyncSerialDriver_I2C.
///
void AsyncSerialDriver_I2CSlave::rxInterruptFunction(
	htl::I2CInterruptParam param) {

	AsyncSerialDriver_I2CSlave *driver = reinterpret_cast<AsyncSerialDriver_I2CSlave*>(param);
	driver->rxInterruptHandler();
}

