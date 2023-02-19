#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_I2C.h"
#include "HTL/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hI2C: El modul I2C a utilitzar.
///
AsyncSerialDriver_I2C::AsyncSerialDriver_I2C(
	I2CHandler hI2C):

	_hI2C(hI2C) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_I2C::initializeImpl() {

	AsyncSerialDriver::initializeImpl();

	_hI2C->setInterruptFunction(interruptFunction, this);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_I2C::deinitializeImpl() {

	_hI2C->setInterruptFunction(nullptr, nullptr);

	AsyncSerialDriver::deinitializeImpl();
}


bool AsyncSerialDriver_I2C::transmitImpl(
	const uint8_t *data,
	int dataLength) {

	if ((data == nullptr) || (dataLength == 0))
		return false;

	else if (isBusy())
		return false;

	else {
		notifyTxStart();

		_flags.rxMode = 0;
		_txData = data;
		_txLength = dataLength;
		_txCount = 0;

		_hI2C->enable();
		_hI2C->enableInterrupt(I2CInterrupt::tx);

		// En aquest moment es genera una interrupcio
		// i comença la transmissio controlada per interrupcions.

		return true;
	}
}


bool AsyncSerialDriver_I2C::receiveImpl(
	uint8_t *data,
	int dataSize) {

	if ((data == nullptr) || (dataSize == 0))
		return false;

	else if (isBusy())
		return false;

	else {
		notifyRxStart();

		_flags.rxMode = 1;
		_rxData = data;
		_rxSize = dataSize;
		_rxCount = 0;

		_hI2C->enable();
		_hI2C->enableInterrupt(I2CInterrupt::addr);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions.
///
void AsyncSerialDriver_I2C::interruptHandler() {

	if (_hI2C->isInterruptEnabled(I2CInterrupt::addr)) {

		if (_hI2C->getFlag(I2CFlag::addr)) {
			_hI2C->clearFlag(I2CFlag::addr);
			_hI2C->disableInterrupt(I2CInterrupt::addr);
			_hI2C->enableInterrupt(I2CInterrupt::stop);
			if (_flags.rxMode)
				_hI2C->enableInterrupt(I2CInterrupt::rx);
			else
				_hI2C->enableInterrupt(I2CInterrupt::tx);
			return;
		}
	}

	if (_hI2C->isInterruptEnabled(I2CInterrupt::rx)) {

		if (_hI2C->getFlag(I2CFlag::rxne)) {
			uint8_t data = _hI2C->read();
			if (_rxCount < _rxSize) {
				*_rxData++ = data;
				_rxCount++;

				// Si es l'ultim, tots els que es rebin despres contestaran NACK
				//
				if (_rxCount == _rxSize)
					_hI2C->nack();
			}
			return;
		}
	}

	if (_hI2C->isInterruptEnabled(I2CInterrupt::stop)) {

		if (_hI2C->getFlag(I2CFlag::stop)) {
			_hI2C->clearFlag(I2CFlag::stop);
			_hI2C->disableInterrupt(I2CInterrupt::stop);
			notifyRxCompleted(_rxCount);
			return;
		}
	}

	if (_hI2C->isInterruptEnabled(I2CInterrupt::tx)) {

		if (_hI2C->getFlag(I2CFlag::txis)) {
			if (_txCount < _txLength) {
				_hI2C->write(*_txData++);
			}
			return;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les interrupcions.
/// \param    param: L'objecte AsyncSerialDriver_I2C.
///
void AsyncSerialDriver_I2C::interruptFunction(
	htl::I2CInterruptParam param) {

	AsyncSerialDriver_I2C *driver = reinterpret_cast<AsyncSerialDriver_I2C*>(param);
	driver->interruptHandler();
}
