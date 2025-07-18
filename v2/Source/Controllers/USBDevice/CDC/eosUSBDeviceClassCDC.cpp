#include "eos.h"
#include "eosAssert.h"
#include "HTL/htl.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "Controllers/USBDevice/ST/st_usbd_ctlreq.h"
#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
/// \param    devUSBD: El dispositiu USB
/// \param    configuration: La configuracio.
/// \param    interface: El interface de comunicacio
///
USBDeviceClassCDC::USBDeviceClassCDC(
	USBDeviceDriver *drvUSBD,
	const USBDeviceClassCDCConfiguration *configuration,
	CDCInterface *interface) :

	USBDeviceClass {drvUSBD, configuration->iface},
	_inEpAddr {configuration->inEpAddr},
	_outEpAddr {configuration->outEpAddr},
	_cmdEpAddr {configuration->cmdEpAddr},
	_interface {interface},
	_state {State::reset},
	_txBuffer {nullptr},
	_txLength {0},
	_rxBuffer {nullptr},
	_rxBufferSize {0},
	_rxLength {0} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \return   El resultat de l'operacio.
///
Result USBDeviceClassCDC::initializeImpl() {

	auto pdev = _drvUSBD->getHandle();
	USBD_RegisterClass(pdev, this);

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    buffer: El bloc de dades.
/// \param    length: Longitut de les dades en bytes.
///
Result USBDeviceClassCDC::transmit(
	const uint8_t *buffer,
	unsigned length) {

	if ((buffer == nullptr) || (length == 0))
		return Results::errorParameter;

	if (_state != State::idle)
		return Results::errorState;

	auto pdev = _drvUSBD->getHandle();
	pdev->ep_in[_inEpAddr & 0x0F].total_length = length;
	if (USBD_LL_Transmit(pdev, _inEpAddr, (uint8_t*) buffer, length) != USBD_OK)
		return Results::error;

	_txBuffer = buffer;
	_txLength = length;
 	_state = State::transmiting;

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
///
Result USBDeviceClassCDC::receive(
	uint8_t *buffer,
	unsigned bufferSize) {

	if ((buffer == nullptr) || (bufferSize == 0))
		return Results::errorParameter;

	if (_state != State::idle)
		return Results::errorState;

	auto pdev = _drvUSBD->getHandle();
	if (USBD_LL_PrepareReceive(pdev, _outEpAddr, buffer, bufferSize) != USBD_OK)
		return Results::error;

	_rxBuffer = buffer;
	_rxBufferSize = bufferSize;
	_state = State::receiving;

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que finalitzin les operacions pendents.
/// \param    timeout: Temps limit.
/// \return   El resultat de l'operacio.
///
Result USBDeviceClassCDC::wait(
	unsigned timeout) {

	auto expireTime = getTick() + timeout;

	while (_state != State::idle) {
		if (hasTickExpired(expireTime))
			return Results::timeout;
	}

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Inicializa la clase.
///
int8_t USBDeviceClassCDC::classInitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();
	bool hs = pdev->dev_speed == USBD_SPEED_HIGH;

    // Prepara EP IN
   	//
   	USBD_LL_OpenEP(pdev, _inEpAddr, USBD_EP_TYPE_BULK, hs ? CDC_DATA_HS_IN_PACKET_SIZE : CDC_DATA_FS_IN_PACKET_SIZE);
   	pdev->ep_in[_inEpAddr & 0x0F].is_used = 1;

   	// Prepara EP OUT
   	//
   	USBD_LL_OpenEP(pdev, _outEpAddr, USBD_EP_TYPE_BULK, hs ? CDC_DATA_HS_OUT_PACKET_SIZE : CDC_DATA_FS_OUT_PACKET_SIZE);
   	pdev->ep_out[_outEpAddr & 0x0F].is_used = 1;

   	// Prepara EP CMD
   	//
   	pdev->ep_in[_cmdEpAddr & 0xFU].bInterval = hs ? CDC_HS_BINTERVAL : CDC_FS_BINTERVAL;
    USBD_LL_OpenEP(pdev, _cmdEpAddr, USBD_EP_TYPE_INTR, CDC_CMD_PACKET_SIZE);
    pdev->ep_in[_cmdEpAddr & 0x0F].is_used = 1;

  	_state = State::idle;

  	// Inicialitza l'interficie
    //
  	_interface->initialize(this);

  	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief     Desinicialitza la clase.
///
int8_t USBDeviceClassCDC::classDeinitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	// Close EP IN
	//
	USBD_LL_CloseEP(pdev, _inEpAddr);
	pdev->ep_in[_inEpAddr & 0xFU].is_used = 0U;

	// Close EP OUT
	//
	USBD_LL_CloseEP(pdev, _outEpAddr);
	pdev->ep_out[_outEpAddr & 0xFU].is_used = 0;

	// Close Command IN EP
	//
	USBD_LL_CloseEP(pdev, _cmdEpAddr);
	pdev->ep_in[_cmdEpAddr & 0xFU].is_used = 0;
	pdev->ep_in[_cmdEpAddr & 0xFU].bInterval = 0;

	// Desinicialitza l'interficie.
	//
	_interface->deinitialize(this);

	_state = State::reset;

	return USBD_OK;
}


int8_t USBDeviceClassCDC::classSetup(
	USBD_SetupReqTypedef *req) {

	auto pdev = _drvUSBD->getHandle();

	USBD_StatusTypeDef ret = USBD_OK;

	switch (req->getType()) {

		case USBDRequestType::clase:
			if (req->length != 0) {
				if (req->getDirection() == USBDRequestDirection::deviceToHost) {
					_interface->control(getCDCRequestID(req), (uint8_t *)_cdc.data, req->length);
					auto len = MIN(CDC_REQ_MAX_DATA_SIZE, req->length);
					USBD_CtlSendData(pdev, (uint8_t *) _cdc.data, len);
				}
				else {
					_req_requestID = getCDCRequestID(req);
					_req_length = (uint8_t) MIN(req->length, USB_MAX_EP0_SIZE);
					USBD_CtlPrepareRx(pdev, (uint8_t*) _cdc.data, _req_length);
				}
			}
			else
				_interface->control(getCDCRequestID(req), (uint8_t*) req, 0);
			break;

		case USBDRequestType::standard:
			switch (req->getRequestID()) {
				case USBDRequestID::getStatus:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						uint16_t status = 0;
						USBD_CtlSendData(pdev, (uint8_t*) &status, sizeof(status));
					}
					else
						ret = USBD_FAIL;
					break;

				case USBDRequestID::getInterface:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						uint8_t iface = 0;
						USBD_CtlSendData(pdev, &iface, sizeof(iface));
					}
					else
						ret = USBD_FAIL;
					break;

				case USBDRequestID::setInterface:
					if (pdev->dev_state != USBD_STATE_CONFIGURED)
						ret = USBD_FAIL;
					break;

				case USBDRequestID::clearFeature:
					break;

				default:
					ret = USBD_FAIL;
					break;
			}
			break;

		default:
			ret = USBD_FAIL;
			break;
	}

	if (ret == USBD_FAIL)
		USBD_CtlError(pdev, req);

	return ret;
}


int8_t USBDeviceClassCDC::classEP0TxSent() {

	return USBD_FAIL;
}


int8_t USBDeviceClassCDC::classEP0RxReady() {

	if (_req_requestID != (CDCRequestID) 0xFF) {
		_interface->control(_req_requestID, (uint8_t *)_cdc.data, _req_length);
		_req_requestID = (CDCRequestID) 0xFF;
	}

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Envia dades al endpoint.
/// \param    epnum: El endpoint.
/// \return   El resultat de l'operacio.
///
int8_t USBDeviceClassCDC::classDataIn(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	PCD_HandleTypeDef *pcd = (PCD_HandleTypeDef *)pdev->pData;

	if ((pdev->ep_in[epnum & 0xFU].total_length > 0) &&
       ((pdev->ep_in[epnum & 0xFU].total_length % pcd->IN_ep[epnum & 0xFU].maxpacket) == 0)) {

		pdev->ep_in[epnum & 0xFU].total_length = 0;
		USBD_LL_Transmit(pdev, epnum, nullptr, 0);
	}
  	else {
  		_interface->txDataCompleted(_txBuffer, _txLength, epnum);
  		_state = State::idle;
  	}

    return USBD_OK;
}


int8_t USBDeviceClassCDC::classDataOut(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	_rxLength = USBD_LL_GetRxDataSize(pdev, epnum);
	_interface->rxDataAvailable(_rxBuffer, _rxLength);
	_state = State::idle;

	return USBD_OK;
}


int8_t USBDeviceClassCDC::classSOF() {

	return USBD_FAIL;
}


int8_t USBDeviceClassCDC::classIsoINIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}


int8_t USBDeviceClassCDC::classIsoOUTIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}

unsigned USBDeviceClassCDC::classGetInterfaceDescriptors(
	uint8_t *buffer,
	unsigned bufferSize,
	bool hs) {

	return false;
}


bool USBDeviceClassCDC::classGetHSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto cmdEpDesc = _drvUSBD->getEpDescriptor(_cmdEpAddr);
	if (cmdEpDesc == nullptr)
		return false;

	auto outEpDesc = _drvUSBD->getEpDescriptor(_outEpAddr);
	if (outEpDesc == nullptr)
		return false;

	auto inEpDesc = _drvUSBD->getEpDescriptor(_inEpAddr);
	if (inEpDesc == nullptr)
		return false;

	cmdEpDesc->bInterval = CDC_HS_BINTERVAL;
	outEpDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;
	inEpDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;

	auto configurationDescriptor = _drvUSBD->getConfigurationDescriptor();
	data = (uint8_t*) configurationDescriptor;
	length = configurationDescriptor->wTotalLength;

	return true;
}


bool USBDeviceClassCDC::classGetFSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto cmdEpDesc = _drvUSBD->getEpDescriptor(_cmdEpAddr);
	if (cmdEpDesc == nullptr)
		return false;

	auto outEpDesc = _drvUSBD->getEpDescriptor(_outEpAddr);
	if (outEpDesc == nullptr)
		return false;

	auto inEpDesc = _drvUSBD->getEpDescriptor(_inEpAddr);
	if (inEpDesc == nullptr)
		return false;

	cmdEpDesc->bInterval = CDC_FS_BINTERVAL;
	outEpDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;
	inEpDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto configurationDescriptor = _drvUSBD->getConfigurationDescriptor();
	data = (uint8_t*) configurationDescriptor;
	length = configurationDescriptor->wTotalLength;

	return true;
}


bool USBDeviceClassCDC::classGetOtherSpeedConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto cmdEpDesc = _drvUSBD->getEpDescriptor(_cmdEpAddr);
	if (cmdEpDesc == nullptr)
		return false;

	auto outEpDesc = _drvUSBD->getEpDescriptor(_outEpAddr);
	if (outEpDesc == nullptr)
		return false;

	auto inEpDesc = _drvUSBD->getEpDescriptor(_inEpAddr);
	if (inEpDesc == nullptr)
		return false;

	cmdEpDesc->bInterval = CDC_FS_BINTERVAL;
	outEpDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;
	inEpDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto configurationDescriptor = _drvUSBD->getConfigurationDescriptor();
	data = (uint8_t*) configurationDescriptor;
	length = configurationDescriptor->wTotalLength;

	return true;
}


bool USBDeviceClassCDC::classGetDeviceQualifierDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto descriptor = _drvUSBD->getConfiguration()->deviceQualifierDescriptor;
	if (descriptor == nullptr)
		return false;

	data = (uint8_t*) descriptor;
	length = descriptor->bLength;

	return true;
}


bool USBDeviceClassCDC::usesEndPoint(
	uint8_t epAddr) const {

	return (epAddr == _inEpAddr) || (epAddr == _outEpAddr);
}

