#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSlaveSerialDriver_I2CSlave.h"
#include "HTL/htlI2C.h"

#include <cmath>


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
/// \param    buffer: El buffer de dades
/// \param    bufferSize: El nombre de bytes en el buffer de dades.
///
void SlaveSerialDriver_I2CSlave::onListen(
    const uint8_t *txBuffer,
    unsigned txBufferSize,
    uint8_t *rxBuffer,
    unsigned rxBufferSize) {

    _txBuffer = txBuffer;
    _txBufferSize = txBufferSize;
    _txCount = 0;

    _rxBuffer = rxBuffer;
    _rxBufferSize = rxBufferSize;
    _rxCount = 0;

    _devI2C->listen_IRQ(_txBuffer, _txBufferSize, _rxBuffer, _rxBufferSize);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de notificacio.
/// \param    args: Parametres del event
///
void SlaveSerialDriver_I2CSlave::i2cNotifyEventHandler(
	I2CNotifyEventArgs &args) {

	switch (args.id) {
	    case htl::i2c::NotifyID::txDataRequest: {
	        if (_txCount < _txBufferSize) {
                auto count = std::min(args.TxDataRequest.bufferSize, _txBufferSize);
                if (count > 0) {
                    memcpy(args.TxDataRequest.buffer, _txBuffer, count);
                    _txCount += count;
                }
                args.TxDataRequest.length = count;
	        }
	        else
                args.TxDataRequest.length = 0;
	        break;
	    }

		case htl::i2c::NotifyID::txCompleted:
			notifyTxCompleted(args.TxCompleted.length);
			break;

        // Recepcio parcial de dades
	    //
        case htl::i2c::NotifyID::rxDataAvailable:
            break;

        // Recepcio complerta de dades
        //
        case htl::i2c::NotifyID::rxCompleted:
            notifyRxCompleted(args.RxCompleted.length);
            break;

        default:
			break;
	}
}


