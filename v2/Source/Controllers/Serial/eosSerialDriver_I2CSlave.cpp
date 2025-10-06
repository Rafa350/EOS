#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_I2CSlave.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
///
SerialDriver_I2CSlave::SerialDriver_I2CSlave(
	htl::i2c::I2CSlaveDevice * devI2C) :

	_devI2C {devI2C},
	_i2cNotifyEvent {*this, &SerialDriver_I2CSlave::i2cNotifyEventHandler} {

	eosAssert(devI2C != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CSlave::onInitialize() {

    _devI2C->setNotifyEvent(_i2cNotifyEvent);
    return _devI2C->listen_IRQ(true).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CSlave::onDeinitialize() {

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

	return
		_devI2C->abort().isSuccess() &&
		_devI2C->listen_IRQ(true).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Rebl es notificacions del dispositiu I2C.
/// \param    id: Identificador del event.
/// \param    args: Parametres del event.
///
void SerialDriver_I2CSlave::i2cNotifyEventHandler(
	htl::i2c::I2CSlaveDevice * const sender,
	htl::i2c::NotifyEventArgs * const args) {

	eosAssert(args != nullptr);
	eosAssert(sender == _devI2C);

	// En cas de transmissio procesa les notificacions de transmissio
	//
	if (getState() == State::transmiting) {

		// Notifica l'inici de la transmissio de dades.
		//
		if (args->id == htl::i2c::NotifyID::txStart) {
			args->txStart.buffer = _buffer;
			args->txStart.length = _bufferSize;
		}

		// Notifica el final de la transmissio de dades.
		//
		else if (args->id == htl::i2c::NotifyID::txCompleted)
			notifyTxCompleted(args->txCompleted.length, args->irq);
	}

	// En cas de recepcio, procesa les notificacions de recepcio
	//
	else if (getState() == State::receiving) {

		// Notifica l'inici de la recepcio de dades.
		//
		if (args->id == htl::i2c::NotifyID::rxStart) {
			args->rxStart.buffer = _buffer;
			args->rxStart.bufferSize = _bufferSize;
		}

		// Notifica el final de la Recepcio de dades.
		//
		else if (args->id == htl::i2c::NotifyID::rxCompleted)
			notifyRxCompleted(args->rxCompleted.length, args->irq);
	}
}
