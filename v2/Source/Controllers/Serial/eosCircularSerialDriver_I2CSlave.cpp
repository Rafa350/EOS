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
	_i2c(i2c) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void CircularSerialDriver_I2CSlave::initializeImpl() {

	_i2c->setInterruptFunction(interruptFunction, this);
	_i2c->listen(_buffer, sizeof(_buffer));
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void CircularSerialDriver_I2CSlave::deinitializeImpl() {

	_i2c->disable();
	_i2c->setInterruptFunction(nullptr, nullptr);
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
/// \brief    Gestio de les interrupcions.
/// \param    notify: La notificacio.
///
void CircularSerialDriver_I2CSlave::interruptHandler(
	i2c::I2CInterruptContext *context) {

	switch (context->status) {
		case i2c::I2CInterruptStatus::addrMatch:
			break;

		case i2c::I2CInterruptStatus::rxPartial: {
			if (context->count > 0) {
				uint16_t availableSpace = rxAvailableSpace();
				if (availableSpace > context->count)
					rxPush(context->buffer, context->count);
			}
			break;
		}

		case i2c::I2CInterruptStatus::rxCompleted:
			if (context->count > 0) {
				uint16_t availableSpace = rxAvailableSpace();
				if (availableSpace > context->count)
					rxPush(context->buffer, context->count);
			}
			if (rxAvailableData() > 0)
				notifyRxBufferNotEmpty();
			break;

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestio de les interrupcions.
/// \param    notify: Notificacio.
/// \param    param: Parametre de la interrupcio.
///
void CircularSerialDriver_I2CSlave::interruptFunction(
	i2c::I2CInterruptContext *context) {

	CircularSerialDriver_I2CSlave *driver = reinterpret_cast<CircularSerialDriver_I2CSlave*>(context->param);
	driver->interruptHandler(context);
}
