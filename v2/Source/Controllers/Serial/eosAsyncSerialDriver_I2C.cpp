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

		_txData = data;
		_txLength = dataLength;
		_txCount = 0;

		_hI2C->enable();
		_hI2C->enableInterrupt(I2CInterrupt::tx);

		// En aquest moment es genera una interrupcio txEmpty
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

	if (_hI2C->getFlag(I2CFlag::addr) && _hI2C->isInterruptEnabled(I2CInterrupt::addr)) {
		_hI2C->clearFlag(I2CFlag::addr);
		_hI2C->disableInterrupt(I2CInterrupt::addr);
		_hI2C->enableInterrupt(I2CInterrupt::rx);
	}

	if (_hI2C->getFlag(I2CFlag::rxne) && _hI2C->isInterruptEnabled(I2CInterrupt::rx)) {
		if (_rxCount < _rxSize) {
			_rxCount++;
			*_rxData++ = _hI2C->read();
			if (_rxCount == _rxSize) {
				_hI2C->disableInterrupt(I2CInterrupt::rx);
				notifyRxCompleted(_rxCount);
			}
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
