#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_I2CMaster.h"


using namespace eos;


constexpr htl::i2c::I2CAddr __addr = 0x52;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
///
SerialDriver_I2CMaster::SerialDriver_I2CMaster(
	htl::i2c::I2CMasterDevice * devI2C) :

	_devI2C {devI2C},
	_i2cNotificationEvent {*this, &SerialDriver_I2CMaster::i2cNotificationEventHandler} {

	eosAssert(devI2C != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CMaster::onInitialize() {

    _devI2C->setNotificationEvent(_i2cNotificationEvent);
    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CMaster::onDeinitialize() {

	_devI2C->disableNotificationEvent();
	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'inici de la transmissio de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: El nombre de bytes en el buffer.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CMaster::onTransmit(
	const uint8_t *buffer,
	unsigned length) {

	eosAssert(buffer != nullptr);
	eosAssert(length != 0);

	return _devI2C->transmit_IRQ(__addr, buffer, length).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'inici de la recepcio de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CMaster::onReceive(
	uint8_t *buffer,
	unsigned bufferSize) {

	eosAssert(buffer != nullptr);
	eosAssert(bufferSize != 0);

	return _devI2C->receive_IRQ(__addr, buffer, bufferSize).isSuccess();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la cancelacio de la comunicacio.
/// \return   True si tot es correcte.
///
bool SerialDriver_I2CMaster::onAbort() {

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Reb les notificacions del dispositiu I2C.
/// \param    sender: El remitent
/// \param    args: Parametres del event.
///
void SerialDriver_I2CMaster::i2cNotificationEventHandler(
	htl::i2c::I2CMasterDevice * const sender,
	htl::i2c::NotificationEventArgs * const args) {

	eosAssert(args != nullptr);
	eosAssert(sender == _devI2C);

	switch(args->id) {
		case htl::i2c::NotificationID::txCompleted:
			notifyTxCompleted(args->txCompleted.length, args->irq);
			break;

		case htl::i2c::NotificationID::rxCompleted:
			notifyRxCompleted(args->rxCompleted.length, args->irq);
			break;
	}
}
