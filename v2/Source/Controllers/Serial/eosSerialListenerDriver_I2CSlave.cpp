#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialListenerDriver_I2CSlave.h"

#include <algorithm>


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devI2C: El dispositiu I2C a utilitzar.
///
SerialListenerDriver_I2CSlave::SerialListenerDriver_I2CSlave(
	DevI2C *devI2C,
	uint8_t *txBuffer,
	unsigned txBufferSize,
	uint8_t *rxBuffer,
	unsigned rxBufferSize) :

	SerialListenerDriver {txBuffer, txBufferSize, rxBuffer, rxBufferSize},

	_devI2C {devI2C},
	_devI2CNotifyEvent {*this, &SerialListenerDriver_I2CSlave::devI2CNotifyEventHandler} {

	_bufferSize = 10;
	_buffer = new uint8_t(_bufferSize);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
SerialListenerDriver_I2CSlave::~SerialListenerDriver_I2CSlave() {

	delete _buffer;
}


/// ----------------------------------------------------------------------
/// \brief    Procesas la inicialitzacio del driver.
///
void SerialListenerDriver_I2CSlave::onInitialize() {

    _devI2C->setNotifyEvent(_devI2CNotifyEvent);
    _devI2C->listen_IRQ(true);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la desinicialitzacio del driver.
///
void SerialListenerDriver_I2CSlave::onDeinitialize() {

	_devI2C->abortListen();
    _devI2C->disableNotifyEvent();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de notificacio del dispositiu I2C
/// \param    args: Parametres del event
///
void SerialListenerDriver_I2CSlave::devI2CNotifyEventHandler(
	I2CNotifyID id,
	I2CNotifyEventArgs * const args) {

	switch (id) {

	    // Inici de la transmissio de dades.
	    //
	    case I2CNotifyID::txStart: {
	    	if (args->txStart.first) {
	    		args->txStart.buffer = _buffer;
	    		args->txStart.length = txBufferRead(_buffer, _bufferSize, args->irq);
	    	}
	        break;
	    }

	    // Transmissio de dades finalitzada
	    //
		case I2CNotifyID::txCompleted:
			break;

        // Inici de la recepcio de dades.
	    //
        case I2CNotifyID::rxStart:
        	if (args->rxStart.first) {
        		args->rxStart.buffer = _buffer;
        		args->rxStart.bufferSize = _bufferSize;
        	}
            break;

        // Recepcio de dades finalitzada.
        //
        case I2CNotifyID::rxCompleted:
        	rxBufferWrite(_buffer, args->rxCompleted.length, args->irq);
            break;

        default:
        	break;
	}
}
