#include "eos.h"
#include "Controllers/Serial/eosCircularSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Conmstructor.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txBufferSize: Tamany del buffer de transmissio.
/// \param    rxBuffer: Buffer de recepcio.
/// \param    rxBufferSize: Tamany del buffer de recepcio.
///
CircularSerialDriver::CircularSerialDriver(
	uint8_t *txBuffer,
	uint16_t txBufferSize,
	uint8_t *rxBuffer,
	uint16_t rxBufferSize) :

	_txBufferEmptyCallback(nullptr),
	_rxBufferNotEmptyCallback(nullptr),
	_txBuffer(txBuffer, txBufferSize),
	_rxBuffer(rxBuffer, rxBufferSize) {

}


/// ----------------------------------------------------------------------
/// \brief    Notifica que el buffer de transmissio es buit.
///
void CircularSerialDriver::notifyTxBufferEmpty() {

	if (_txBufferEmptyCallback != nullptr) {

		TxBufferEmptyEventArgs args;
		args.availableSpace = txAvailableSpace();

		_txBufferEmptyCallback->execute(args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que el buffer de recepcio no es buit.
///
void CircularSerialDriver::notifyRxBufferNotEmpty() {

	if (_rxBufferNotEmptyCallback != nullptr) {

		RxBufferNotEmptyEventArgs args;
		args.availableData = rxAvailableData();

		_rxBufferNotEmptyCallback->execute(args);
	}
}


void CircularSerialDriver::enableTxBufferEmptyCallback(
	const ITxBufferEmptyCallback &callback) {

	_txBufferEmptyCallback = &callback;
}


void CircularSerialDriver::enableRxBufferNotEmptyCallback(
	const IRxBufferNotEmptyCallback &callback) {

	_rxBufferNotEmptyCallback = &callback;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialutza el driver.
///
void CircularSerialDriver::initialize() {

	initializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void CircularSerialDriver::deinitialize() {

	deinitializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'espai disponible en el buffer de transmissio.
/// \return   El nombre de bytes dispoibles.
///
uint16_t CircularSerialDriver::txAvailableSpace() const {

	return _txBuffer.getCapacity() - _txBuffer.getSize();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'espai disponible en el buffer de recepcio.
/// \return   El nombre de bytes dispoibles.
///
uint16_t CircularSerialDriver::rxAvailableSpace() const {

	return _rxBuffer.getCapacity() - _rxBuffer.getSize();
}


/// ----------------------------------------------------------------------
/// \brief    Trasmiteix un bloc de dades.
/// \param    data: Bloc de dades.
/// \param    dataLength: Longitut del bloc en bytes.
/// \return   El nombre real de bytes transmessos.
///
uint16_t CircularSerialDriver::transmit(
	const uint8_t *data,
	uint16_t dataLength) {

	return transmitImpl(data, dataLength);
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    data: Bloc de dades.
/// \param    dataSIze: TYemeny del bloc en bytes.
/// \return   El nombre real de bytes rebuts.
///
uint16_t CircularSerialDriver::receive(
	uint8_t *data,
	uint16_t dataSize) {

	return receiveImpl(data, dataSize);
}
