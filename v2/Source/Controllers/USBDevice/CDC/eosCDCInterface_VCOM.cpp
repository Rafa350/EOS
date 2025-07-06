#include "eos.h"
#include "Controllers/USBDevice/CDC/eosCDCInterface_VCOM.h"
#include "Controllers/USBDevice/CDC/eosCDCDefinitions.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio
///
int8_t CDCInterface_VCOM::initialize(
	USBDeviceClassCDC *cdc) {

	_lineCoding.dwDTERate = 115200;
	_lineCoding.bCharFormat = 0;
	_lineCoding.bParityType = 0;
	_lineCoding.bDataBits = 0;

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio
///
int8_t CDCInterface_VCOM::deinitialize(
	USBDeviceClassCDC *cdc) {

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les solicituts
/// \param    requestID: Codi de la solicitut.
/// \param    data: Buffer de dades.
/// \param    dataSize: Tamany del buffer de dades.
///
int8_t CDCInterface_VCOM::control(
	CDCRequestID requestID,
	uint8_t *data,
	unsigned dataSize) {

	switch (requestID) {
		case CDCRequestID::sendEncapsulatedCommand:
			break;

		case CDCRequestID::getEncapsulatedResponse:
			break;

		case CDCRequestID::setCommFeature:
			break;

		case CDCRequestID::getCommFeature:
			break;

		case CDCRequestID::clearCommFeature:
			break;

		case CDCRequestID::setLineCoding:
			setLineCoding(data, dataSize);
			break;

		case CDCRequestID::getLineCoding:
			getLineCoding(data, dataSize);
			break;

		case CDCRequestID::setControlLineState:
			break;

		case CDCRequestID::sendBreak:
			break;

		default:
			break;
	}

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la solicitut 'SetLineCoding'
/// \param    data: Les dades.
/// \param    dataSize: Tamany de les dades.
///
void CDCInterface_VCOM::setLineCoding(
	uint8_t *data,
	unsigned dataSize) {

	memcpy(&_lineCoding, data, sizeof(_lineCoding));
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la solicitut 'GetLineCoding'
/// \param    data: Les dades.
/// \param    dataSize: Tamany de les dades.
///
void CDCInterface_VCOM::getLineCoding(
	uint8_t *data,
	unsigned dataSize) {

	memcpy(data, &_lineCoding, dataSize);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que hi han dades disponibles
/// \param    data: Buffer de dades.
/// \param    length: Longitut de les dades en bytes.
///
void CDCInterface_VCOM::rxDataAvailable(
	const uint8_t *buffer,
	unsigned length) {

}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la transmissio.
///
void CDCInterface_VCOM::txDataCompleted(
	const uint8_t *buffer,
	unsigned length,
	uint8_t epnum) {

}
