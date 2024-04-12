#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSlaveSerialDriver_I2CSlave.h"
#include "HTL/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
/// \param    buffer: El buffer.
/// \param    bufferSize: Tamany en bytes del buffer.
///
SlaveSerialDriver_I2CSlave::SlaveSerialDriver_I2CSlave(
	DevI2C *devI2C) :

	_devI2C {devI2C},
	_i2cNotifyEvent {*this, &SlaveSerialDriver_I2CSlave::i2cNotifyEventHandler} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SlaveSerialDriver_I2CSlave::onInitialize() {

    _devI2C->setNotifyEvent(_i2cNotifyEvent);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SlaveSerialDriver_I2CSlave::onDeinitialize() {

    if (!_devI2C->isReady())
        _devI2C->abortListen();
    _devI2C->disableNotifyEvent();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    txBuffer: El buffer de tranmissio
/// \param    txBufferSize: El tamany en bytes del buffer de transmissio..
/// \param    rxBuffer: El buffer de recepcio.
/// \param    rxBufferSize: El tamany en bytes del buffer de recepcio.
///
void SlaveSerialDriver_I2CSlave::onListen(
    const uint8_t *txBuffer,
    unsigned txBufferSize,
    uint8_t *rxBuffer,
    unsigned rxBufferSize) {

    _txBuffer = txBuffer;
    _txBufferSize = txBufferSize;

    _rxBuffer = rxBuffer;
    _rxBufferSize = rxBufferSize;

    _devI2C->listen_IRQ();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de notificacio.
/// \param    args: Parametres del event
///
void SlaveSerialDriver_I2CSlave::i2cNotifyEventHandler(
	I2CNotifyEventArgs &args) {

	switch (args.id) {

	    // Inici de la transmissio de dades.
	    //
	    case htl::i2c::NotifyID::txStart: {
            args.TxStart.buffer = (uint8_t*) _txBuffer;
            args.TxStart.length = _txBufferSize;
            notifyTxStart();
	        break;
	    }

	    // Transmissio de dades finalitzada
	    //
		case htl::i2c::NotifyID::txCompleted:
			notifyTxCompleted(args.TxCompleted.length);
			break;

        // Inici de la recepcio de dades.
	    //
        case htl::i2c::NotifyID::rxStart:
            args.RxStart.buffer = _rxBuffer;
            args.RxStart.bufferSize = _rxBufferSize;
            notifyRxStart();
            break;

        // Recepcio de dades finalitzada.
        //
        case htl::i2c::NotifyID::rxCompleted:
            notifyRxCompleted(args.RxCompleted.length);
            break;
	}
}


