#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosAsyncSerialDriver_I2CSlave.h"
#include "HTL/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
///
AsyncSerialDriver_I2CSlave::AsyncSerialDriver_I2CSlave(
	DevI2C *devI2C) :

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
/// \param    buffer: El buffer de dades
/// \param    bufferSize: El nombre de bytes en el buffer de dades.
///
bool AsyncSerialDriver_I2CSlave::transmitImpl(
	const uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

	if ((buffer == nullptr) || (bufferSize == 0))
		return false;

	else {
		notifyTxStart();

		_txData = buffer;
		_txLength = bufferSize;
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
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
///
bool AsyncSerialDriver_I2CSlave::receiveImpl(
	uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

    if ((buffer == nullptr) || (bufferSize == 0))
		return false;

	else {
		notifyRxStart();

        // A partir d'aqui, es generen interrupcions
        // cada cop que hi han dades disposibles.
		//
		_devI2C->listen_IRQ(buffer, bufferSize);

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de notificacio.
/// \param    sender: L'objecte que ha generat l'event
/// \param    args: Parametres del event
///
void AsyncSerialDriver_I2CSlave::i2cNotifyEventHandler(
	DevI2C *sender,
	I2CNotifyEventArgs &args) {

	switch (args.id) {
		case htl::i2c::NotifyID::txCompleted:
			notifyTxCompleted(args.TxCompleted.length);
			break;

		default:
			break;
	}
}


