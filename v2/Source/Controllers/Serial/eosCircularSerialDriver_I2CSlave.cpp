#include "eos.h"
#include "Controllers/Serial/eosCircularSerialDriver_I2CSlave.h"
#include "htl/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txBufferSize: Tamany del buffer de transmissio.
/// \param    rxBuffer: Buffer de recepcio.
/// \param    rxBufferSize: Tamany del buffer de recepcio.
/// \param    dev: El dispositiu I2C.
///
CircularSerialDriver_I2CSlave::CircularSerialDriver_I2CSlave(
	uint8_t *txBuffer,
	uint16_t txBufferSize,
	uint8_t *rxBuffer,
	uint8_t rxBufferSize,
	htl::i2c::I2CSlaveDevice *dev) :

	CircularSerialDriver(txBuffer, txBufferSize, rxBuffer, rxBufferSize),
	_dev(dev),
	_i2cNotifyEvent(*this, &CircularSerialDriver_I2CSlave::i2cNotifyEventHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void CircularSerialDriver_I2CSlave::initializeImpl() {

	_dev->setNotifyEvent(_i2cNotifyEvent, true);
	_dev->listen_IRQ(_buffer, sizeof(_buffer));
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void CircularSerialDriver_I2CSlave::deinitializeImpl() {

	_dev->endListen();
	_dev->disableNotifyEvent();
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    data: El bloc de dades.
/// \param    dataLength: Longitut en bytes del bloc de dades.
/// \return   El nombre de bytes realment transmessos.
///
uint16_t CircularSerialDriver_I2CSlave::transmitImpl(
	const uint8_t *data,
	uint16_t dataLength) {

	uint16_t dataCount = 0;
	while ((dataCount < dataLength) && txAvailableSpace())
		txPush(data[dataCount++]);

	return dataCount;
}


/// ----------------------------------------------------------------------
/// \brief    Recepcio d'un bloc de dades.
/// \param    data: El bloc de on deixar les dades.
/// \param    dataLength: Tamany en bytes del bloc de dades.
/// \return   El nombre de bytes realment rebuts.
///
uint16_t CircularSerialDriver_I2CSlave::receiveImpl(
	uint8_t *data,
	uint16_t dataSize) {

	uint16_t dataCount = 0;
	while ((dataCount < dataSize) && rxAvailableData())
		data[dataCount++] = rxPop();

	return dataCount;
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha coincidencia amb l'adressa I2C
/// \param    addr: L'adressa.
///
void CircularSerialDriver_I2CSlave::i2cNotifyEventHandler(
	htl::i2c::I2CSlaveDevice *sender,
	htl::i2c::NotifyEventArgs &args) {

	switch (args.id) {
		case htl::i2c::NotifyID::addressMatch:
			break;

		case htl::i2c::NotifyID::rxDataAvailable:
			if (args.RxDataAvailable.length > 0) {
				uint16_t availableSpace = rxAvailableSpace();
				if (availableSpace >= args.RxDataAvailable.length)
					rxPush(args.RxDataAvailable.buffer, args.RxDataAvailable.length);
			}
			break;

		case htl::i2c::NotifyID::rxCompleted:
			if (args.RxCompleted.length > 0) {
				uint16_t availableSpace = rxAvailableSpace();
				if (availableSpace >= args.RxCompleted.length)
					rxPush(args.RxCompleted.buffer, args.RxCompleted.length);
			}
			if (rxAvailableData() > 0)
				notifyRxBufferNotEmpty();
			break;

		case htl::i2c::NotifyID::txDataRequest: {
			uint16_t availableData = txAvailableData();
			uint16_t count = 0;
			while ((availableData > 0) && (count < args.TxDataRequest.size)) {
				args.TxDataRequest.buffer[count++] = txPop();
				availableData--;
			}
			args.TxDataRequest.length = count;
			break;
		}

		case htl::i2c::NotifyID::txCompleted:
			break;
	}
}
