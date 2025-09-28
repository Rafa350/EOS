#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_I2CSlave.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
///
SerialDriver_I2CSlave::SerialDriver_I2CSlave(
	DevI2C *devI2C) :

	_devI2C {devI2C},
	_i2cNotifyEvent {*this, &SerialDriver_I2CSlave::i2cNotifyEventHandler} {

	eosAssert(devI2C != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CSlave::onInitialize() {

	eosAssert(_devI2C != nullptr);

    _devI2C->setNotifyEvent(_i2cNotifyEvent);
    return _devI2C->listen_IRQ(true).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CSlave::onDeinitialize() {

	eosAssert(_devI2C != nullptr);

	_devI2C->disableNotifyEvent();
	return _devI2C->abort().isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'inici de la transmissio de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: El nombre de bytes en el buffer.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CSlave::onTransmit(
	const uint8_t *buffer,
	unsigned length) {

	eosAssert(buffer != nullptr);
	eosAssert(length != 0);

	_buffer = (uint8_t *) buffer;
	_bufferSize = length;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'inici de la recepcio de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CSlave::onReceive(
	uint8_t *buffer,
	unsigned bufferSize) {

	eosAssert(buffer != nullptr);
	eosAssert(bufferSize != 0);

	_buffer = buffer;
	_bufferSize = bufferSize;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la cancelacio de la comunicacio.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CSlave::onAbort() {

	eosAssert(_devI2C != nullptr);

	return
		_devI2C->abort().isSuccess() &&
		_devI2C->listen_IRQ(true).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Rebles notificacions del dispositiu I2C.
/// \param    id: Identificador del event.
/// \param    args: Parametres del event.
///
void SerialDriver_I2CSlave::i2cNotifyEventHandler(
	I2CNotifyID id,
	I2CNotifyEventArgs * const args) {

	eosAssert(args != nullptr);

	// En cas de transmissio procesa les notificacions de transmissio
	//
	if (getState() == State::transmiting) {

		// Notifica l'inici de la transmissio de dades.
		//
		if (id == I2CNotifyID::txStart) {
			args->txStart.buffer = _buffer;
			args->txStart.length = _bufferSize;
		}

		// Notifica el final de la transmissio de dades.
		//
		else if (id == I2CNotifyID::txCompleted)
			notifyTxCompleted(args->txCompleted.length, args->irq);
	}

	// En cas de recepcio, procesa les notificacions de recepcio
	//
	else if (getState() == State::receiving) {

		// Notifica l'inici de la recepcio de dades.
		//
		if (id == I2CNotifyID::rxStart) {
			args->rxStart.buffer = _buffer;
			args->rxStart.bufferSize = _bufferSize;
		}

		// Notifica el final de la Recepcio de dades.
		//
		else if (id == I2CNotifyID::rxCompleted)
			notifyRxCompleted(args->rxCompleted.length, args->irq);
	}
}
