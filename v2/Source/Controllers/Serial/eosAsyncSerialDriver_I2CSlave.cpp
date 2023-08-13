#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver_I2CSlave.h"
#include "HTL/htlI2C.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hI2C: El modul I2C a utilitzar.
///
AsyncSerialDriver_I2CSlave::AsyncSerialDriver_I2CSlave(
	i2c::I2CSlaveDeviceHandler i2c) :

	_i2c(i2c),
	_addressMatchEvent(*this, &AsyncSerialDriver_I2CSlave::addressMatchEventHandler),
	_rxDataEvent(*this, &AsyncSerialDriver_I2CSlave::rxDataEventHandler),
	_rxCompletedEvent(*this, &AsyncSerialDriver_I2CSlave::rxCompletedEventHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void AsyncSerialDriver_I2CSlave::initializeImpl() {

	AsyncSerialDriver::initializeImpl();

	_i2c->enableAddressMatchCallback(_addressMatchEvent);
	_i2c->enableRxDataCallback(_rxDataEvent);
	_i2c->enableRxCompletedCallback(_rxCompletedEvent);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void AsyncSerialDriver_I2CSlave::deinitializeImpl() {

	_i2c->disableAddressMatchCallback();
	_i2c->disableRxDataCallback();
	_i2c->disableRxCompletedCallback();

	AsyncSerialDriver::deinitializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Transmioteix un bloc de dades.
/// \param    data: El bloc de dades.
/// \param    dataLength: Longitut del bloc de dades.
///
bool AsyncSerialDriver_I2CSlave::transmitImpl(
	const uint8_t *data,
	int dataLength) {

	if ((data == nullptr) || (dataLength == 0))
		return false;

	else {
		notifyTxStart();

		_txData = data;
		_txLength = dataLength;
		_txCount = 0;

		//_i2c->enable();
		//_i2c->enableInterrupt(I2CInterrupt::addr);

		// En aquest moment es genera una interrupcio
		// i comença la transmissio controlada per interrupcions.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    data: Buffer de dades.
/// \param    dataSize: Tamany del buffer de dades.
///
bool AsyncSerialDriver_I2CSlave::receiveImpl(
	uint8_t *data,
	int dataSize) {

	if ((data == nullptr) || (dataSize == 0))
		return false;

	else {
		notifyRxStart();

		////************************************
		/// PROVISIONAL fins implementar receive
		_i2c->listen(data, dataSize);

		// En aquest moment, es generen interrupcions
		// cada cop que hi han dades disposibles.

		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha coincidencia amb l'adressa
/// \param    addr: L'adressa I2C.
///
void AsyncSerialDriver_I2CSlave::addressMatchEventHandler(
	uint16_t addr) {

}


/// ----------------------------------------------------------------------
/// \brief    Es crida qwuan han arribat dades i el buffer es ple. Permet
///           buidar-lo i continuar la recepcio.
/// \param    buffer: Buffer de dades.
/// \param    count: Nombre de bytes en el buffer.
///
void AsyncSerialDriver_I2CSlave::rxDataEventHandler(
	const uint8_t *buffer,
	uint16_t count) {

}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant han arribat les dades i ha finalitzat la comunicacio.
/// \param    buffer: El buffer de dades.
/// \param    count: El nombre de bytes en el buffer.
///
void AsyncSerialDriver_I2CSlave::rxCompletedEventHandler(
	const uint8_t *buffer,
	uint16_t count) {

	notifyTxCompleted(count);
}


