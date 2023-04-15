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
/// \param    hI2C: Handler del modul I2C.
///
CircularSerialDriver_I2CSlave::CircularSerialDriver_I2CSlave(
	uint8_t *txBuffer,
	uint16_t txBufferSize,
	uint8_t *rxBuffer,
	uint8_t rxBufferSize,
	htl::i2c::I2CSlaveDeviceHandler hI2C) :

	CircularSerialDriver(txBuffer, txBufferSize, rxBuffer, rxBufferSize),
	_hI2C(hI2C) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void CircularSerialDriver_I2CSlave::initializeImpl() {

	//_hI2C->setInterruptFunction(interruptFunction, this);
	_hI2C->listen(_buffer, sizeof(_buffer));
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void CircularSerialDriver_I2CSlave::deinitializeImpl() {

	_hI2C->disable();
	_hI2C->setInterruptFunction(nullptr, nullptr);
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
	htl::i2c::I2CInterruptNotify notify) {

	switch (notify) {
		case i2c::I2CInterruptNotify::addrMatch:
			break;

		case i2c::I2CInterruptNotify::rxNotEmpty: {

/*			uint8_t data = _hI2C->read();

			// Si hi ha espai, guarda el byte.
			//
			uint16_t availableSpace = rxAvailableSpace();
			if (availableSpace > 0)
				rxPush(data);*/
			break;
		}

		case i2c::I2CInterruptNotify::completted:
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
    htl::i2c::I2CInterruptNotify notify,
	htl::i2c::I2CInterruptParam param) {

	CircularSerialDriver_I2CSlave *driver = reinterpret_cast<CircularSerialDriver_I2CSlave*>(param);
	driver->interruptHandler(notify);
}
