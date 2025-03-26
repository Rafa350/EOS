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
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del driver.
///
void SerialDriver_I2CSlave::onInitialize() {

    _devI2C->setNotifyEvent(_i2cNotifyEvent);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
///
void SerialDriver_I2CSlave::onDeinitialize() {

	_devI2C->abortListen();
    _devI2C->disableNotifyEvent();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'inici de la transmissio de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: El nombre de bytes en el buffer.
///
void SerialDriver_I2CSlave::onTransmit(
	const uint8_t *buffer,
	unsigned length) {

	_buffer = (uint8_t *) buffer;
	_bufferSize = length;

    _devI2C->listen_IRQ(true);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'inici de la recepcio de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
///
void SerialDriver_I2CSlave::onReceive(
	uint8_t *buffer,
	unsigned bufferSize) {

	_buffer = buffer;
	_bufferSize = bufferSize;

    _devI2C->listen_IRQ(true);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la cancelacio de la comunicacio.
///
void SerialDriver_I2CSlave::onAbort() {

	_devI2C->abortListen();
}


/// ----------------------------------------------------------------------
/// \brief    Rebles notificacions del dispositiu I2C.
/// \param    id: Identificador del event.
/// \param    args: Parametres del event.
///
void SerialDriver_I2CSlave::i2cNotifyEventHandler(
	I2CNotifyID id,
	I2CNotifyEventArgs * const args) {

	// En cas de transmissio procesa les notificacions de transmissio
	//
	if (getState() == State::transmiting) {

		// Notifica l'inici de la transmissio de dades.
		// TODO: Transmissio per blocs.
		//
		if (id == I2CNotifyID::txStart) {
			if (args->txStart.first) {
				args->txStart.buffer = _buffer;
				args->txStart.length = _bufferSize;
			}
		}

		// Notifica el final de la transmissio de dades.
		//
		else if (id == I2CNotifyID::txCompleted) {
			notifyTxCompleted(args->txCompleted.length, args->irq);
		}
	}

	// En cas de recepcio, procesa les notificacions de recepcio
	//
	else if (getState() == State::receiving) {

		// Notifica l'inici de la recepcio de dades.
		// TODO: Recepcio per blocs.
		if (id == I2CNotifyID::rxStart) {
			if (args->rxStart.first) {
				args->rxStart.buffer = _buffer;
				args->rxStart.bufferSize = _bufferSize;
			}
		}

		// Notifica el final de la Recepcio de dades.
		//
		else if (id == I2CNotifyID::rxCompleted) {
			notifyRxCompleted(args->rxCompleted.length, args->irq);
		}
	}
}
