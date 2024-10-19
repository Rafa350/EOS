#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_I2CSlave.h"
#include "HTL/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
///
SerialDriver_I2CSlave::SerialDriver_I2CSlave(
	DevI2C *devI2C) :

	_devI2C {devI2C},
	_i2cNotifyEvent {*this, &SerialDriver_I2CSlave::i2cNotifyEventHandler},
	_rxBuffer {nullptr},
	_rxBufferSize {0},
	_txBuffer {nullptr},
	_txLength {0} {

}


/// ----------------------------------------------------------------------
/// \brief    Procesas la inicialitzacio del driver.
///
void SerialDriver_I2CSlave::onInitialize() {

    _devI2C->setNotifyEvent(_i2cNotifyEvent);
    _devI2C->listen_IRQ();
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
/// \param    length: Nombre de bytes a transmetre.
///
void SerialDriver_I2CSlave::onTransmit(
    const uint8_t *buffer,
    unsigned length) {

    _txBuffer = buffer;
    _txLength = length;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'inici de la recepcio de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany en bytes del buffer de dades.
///
void SerialDriver_I2CSlave::onReceive(
    uint8_t *buffer,
    unsigned bufferSize) {

    _rxBuffer = buffer;
    _rxBufferSize = bufferSize;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de notificacio.
/// \param    args: Parametres del event
///
void SerialDriver_I2CSlave::i2cNotifyEventHandler(
	I2CNotifyEventArgs &args) {

	switch (args.id) {

	    // Inici de la transmissio de dades.
	    //
	    case htl::i2c::NotifyID::txStart: {
            args.txStart.buffer = (uint8_t*) _txBuffer;
            args.txStart.length = _txLength;
	        break;
	    }

	    // Transmissio de dades finalitzada
	    //
		case htl::i2c::NotifyID::txCompleted:
			notifyTxCompleted(args.txCompleted.length);
			_txBuffer = nullptr;
			_txLength = 0;
			break;

        // Inici de la recepcio de dades.
	    //
        case htl::i2c::NotifyID::rxStart:
            args.rxStart.buffer = _rxBuffer;
            args.rxStart.bufferSize = _rxBufferSize;
            break;

        // Recepcio de dades finalitzada.
        //
        case htl::i2c::NotifyID::rxCompleted:
            notifyRxCompleted(args.rxCompleted.length);
            _rxBuffer = nullptr;
            _rxBufferSize = 0;
            break;
	}
}


