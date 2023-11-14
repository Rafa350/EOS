#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_I2CSlave.h"
#include "HTL/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
///
AsyncSerialDriver_I2CSlave::AsyncSerialDriver_I2CSlave(
	i2c::I2CSlaveDevice *devI2C) :

	_devI2C {devI2C},
	_i2cNotifyEvent {*this, &AsyncSerialDriver_I2CSlave::i2cNotifyEventHandler} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_I2CSlave::initializeImpl() {

	AsyncSerialDriver::initializeImpl();

	_devI2C->setNotifyEvent(_i2cNotifyEvent);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_I2CSlave::deinitializeImpl() {

	_devI2C->disableNotifyEvent();

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

		//_i2c->enable();
		//_i2c->enableInterrupt(I2CInterrupt::addr);

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

		////************************************
		/// PROVISIONAL fins implementar receive
		_devI2C->listen(data, dataSize);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de notificacio.
/// \param    sender: L'objecte que ha generat l'event
/// \param    args: Parametres del event
///
void AsyncSerialDriver_I2CSlave::i2cNotifyEventHandler(
	htl::i2c::I2CSlaveDevice *sender,
	htl::i2c::NotifyEventArgs &args) {

	switch (args.id) {
		case htl::i2c::NotifyID::txCompleted:
			notifyTxCompleted(args.TxCompleted.length);
			break;

		default:
			break;
	}
}


