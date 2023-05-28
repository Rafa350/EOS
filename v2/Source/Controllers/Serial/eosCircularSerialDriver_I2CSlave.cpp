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
/// \param    i2c: Handler del modul I2C.
///
CircularSerialDriver_I2CSlave::CircularSerialDriver_I2CSlave(
	uint8_t *txBuffer,
	uint16_t txBufferSize,
	uint8_t *rxBuffer,
	uint8_t rxBufferSize,
	htl::i2c::I2CSlaveDeviceHandler i2c) :

	CircularSerialDriver(txBuffer, txBufferSize, rxBuffer, rxBufferSize),
	_i2c(i2c),
	_addressMatchCallback(*this, &CircularSerialDriver_I2CSlave::addressMatchHandler),
	_rxDataCallback(*this, &CircularSerialDriver_I2CSlave::rxDataHandler),
	_rxCompletedCallback(*this, &CircularSerialDriver_I2CSlave::rxCompletedHandler),
	_txDataCallback(*this, &CircularSerialDriver_I2CSlave::txDataHandler),
	_txCompletedCallback(*this, &CircularSerialDriver_I2CSlave::txCompletedHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void CircularSerialDriver_I2CSlave::initializeImpl() {

	_i2c->enableAddressMatchCallback(_addressMatchCallback);
	_i2c->enableRxDataCallback(_rxDataCallback);
	_i2c->enableRxCompletedCallback(_rxCompletedCallback);
	_i2c->enableTxDataCallback(_txDataCallback);
	_i2c->enableTxCompletedCallback(_txCompletedCallback);
	_i2c->listen(_buffer, sizeof(_buffer));
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void CircularSerialDriver_I2CSlave::deinitializeImpl() {

	_i2c->endListen();
	_i2c->disableAddressMatchCallback();
	_i2c->disableRxDataCallback();
	_i2c->disableRxCompletedCallback();
	_i2c->disableTxDataCallback();
	_i2c->disableTxCompletedCallback();
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
void CircularSerialDriver_I2CSlave::addressMatchHandler(
	uint16_t addr) {

	addr = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant el buffer es ple, pero no ha acabat
///           la recepcio.
/// \param    buffer: El buffer de dades.
/// \param    count: Nombre de bytes en el buffer.
///
void CircularSerialDriver_I2CSlave::rxDataHandler(
	const uint8_t *buffer,
	uint16_t count) {

	if (count > 0) {
		uint16_t availableSpace = rxAvailableSpace();
		if (availableSpace >= count)
			rxPush(buffer, count);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant ha acabat la recepcio
/// \param    buffer: El buffer de dades.
/// \param    count: Nombre de bytes en el buffer.
///
void CircularSerialDriver_I2CSlave::rxCompletedHandler(
	const uint8_t *buffer,
	uint16_t count) {

	if (count > 0) {
		uint16_t availableSpace = rxAvailableSpace();
		if (availableSpace >= count)
			rxPush(buffer, count);
	}
	if (rxAvailableData() > 0)
		notifyRxBufferNotEmpty();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant el buffer es buit i calen dades per transmetre.
/// \param    buffer: EL buffer de dades.
/// \param    bufferSize: El tamany del buffer.
/// \param    count: El nombre de bytes en el buffer.
///
void CircularSerialDriver_I2CSlave::txDataHandler(
	uint8_t *buffer,
	uint16_t bufferSize,
	uint16_t &count) {

	uint16_t availableData = txAvailableData();
	count = 0;
	while ((availableData > 0) && (count < bufferSize)) {
		buffer[count++] = txPop();
		availableData--;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es criuda quant ha acabat la transmissio.
///
void CircularSerialDriver_I2CSlave::txCompletedHandler() {

}
