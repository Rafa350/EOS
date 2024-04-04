#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver_I2CSlave.h"
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
SerialDriver_I2CSlave::SerialDriver_I2CSlave(
	DevI2C *devI2C,
	uint8_t *buffer,
	unsigned bufferSize) :

	_devI2C {devI2C},
	_buffer {buffer},
	_bufferSize {bufferSize},
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

    if (!_devI2C->isReady())
        _devI2C->abortListen();

    _devI2C->disableNotifyEvent();

	AsyncSerialDriver::deinitializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    buffer: El buffer de dades
/// \param    bufferSize: El nombre de bytes en el buffer de dades.
///
bool AsyncSerialDriver_I2CSlave::startTxImpl(
	const uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

	if ((buffer == nullptr) || (bufferSize == 0))
		return false;

	else {
		notifyTxStart();

		_txBuffer = buffer;
		_txBufferSize = bufferSize;
		_txCount = 0;

		if (_devI2C->isReady())
		    _devI2C->listen_IRQ(_buffer, _bufferSize, _buffer, _bufferSize);

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \return   True si tot es correcte.
///
bool AsyncSerialDriver_I2CSlave::startRxImpl(
	uint8_t *buffer,
	unsigned bufferSize) {

    eosAssert(buffer != nullptr);
    eosAssert(bufferSize > 0);

    if ((buffer == nullptr) || (bufferSize == 0))
		return false;

	else {
		notifyRxStart();

		_rxBuffer = buffer;
		_rxBufferSize = bufferSize;
		_rxCount = 0;

        if (_devI2C->isReady())
            _devI2C->listen_IRQ(_buffer, _bufferSize, _buffer, _bufferSize);

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Aborta la comunicacio.
/// \return   True si es correcte.
///
bool AsyncSerialDriver_I2CSlave::abortImpl() {

    if (!_devI2C->isReady())
        _devI2C->abortListen();

    return AsyncSerialDriver::abortImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de notificacio.
/// \param    args: Parametres del event
///
void AsyncSerialDriver_I2CSlave::i2cNotifyEventHandler(
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
        case htl::i2c::NotifyID::rxDataAvailable: {
            auto count = args.RxCompleted.length;
            if (_rxCount + count > _rxBufferSize)
                count = _rxBufferSize - _rxCount;
            if (count > 0) {
                memcpy(&_rxBuffer[_rxCount], args.RxCompleted.buffer, count);
                _rxCount += count;
            }
            break;
        }

        // Recepcio complerta de dades
        //
        case htl::i2c::NotifyID::rxCompleted: {
            auto count = args.RxCompleted.length;
            if (_rxCount + count > _rxBufferSize)
                count = _rxBufferSize - _rxCount;
            if (count > 0)
                memcpy(&_rxBuffer[_rxCount], args.RxCompleted.buffer, count);
            notifyRxCompleted(_rxCount + count);
            break;
        }

        default:
			break;
	}
}


