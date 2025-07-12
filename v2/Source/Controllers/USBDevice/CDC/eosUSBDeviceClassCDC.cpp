#include "eos.h"
#include "eosAssert.h"
#include "HTL/htl.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "Controllers/USBDevice/ST/st_usbd_ctlreq.h"
#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"


using namespace eos;
using namespace htl;


extern uint8_t USBD_CDC_CfgDesc[USB_CDC_CONFIG_DESC_SIZ];
extern uint8_t USBD_CDC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
/// \param    devUSBD: El dispositiu USB
/// \param    interface: El interface de comunicacio
///
USBDeviceClassCDC::USBDeviceClassCDC(
	USBDeviceDriver *drvUSBD,
	CDCInterface *interface) :

	USBDeviceClass {drvUSBD},
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
///
void USBDeviceClassCDC::initialize() {

	auto pdev = _drvUSBD->getHandle();
	USBD_RegisterClass(pdev, this);
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
	pdev->ep_in[_inEpAdd & 0xFU].total_length = length;
	if (USBD_LL_Transmit(pdev, _inEpAdd, (uint8_t*) buffer, length) != USBD_OK)
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
	if (USBD_LL_PrepareReceive(pdev, _outEpAdd, buffer, bufferSize) != USBD_OK)
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
   	USBD_LL_OpenEP(pdev, _inEpAdd, USBD_EP_TYPE_BULK, hs ? CDC_DATA_HS_IN_PACKET_SIZE : CDC_DATA_FS_IN_PACKET_SIZE);
   	pdev->ep_in[_inEpAdd & 0x0F].is_used = 1;

   	// Prepara EP OUT
   	//
   	USBD_LL_OpenEP(pdev, _outEpAdd, USBD_EP_TYPE_BULK, hs ? CDC_DATA_HS_OUT_PACKET_SIZE : CDC_DATA_FS_OUT_PACKET_SIZE);
   	pdev->ep_out[_outEpAdd & 0x0F].is_used = 1;

   	// Prepara EP CMD
   	//
   	pdev->ep_in[_cmdEpAdd & 0xFU].bInterval = hs ? CDC_HS_BINTERVAL : CDC_FS_BINTERVAL;
    USBD_LL_OpenEP(pdev, _cmdEpAdd, USBD_EP_TYPE_INTR, CDC_CMD_PACKET_SIZE);
    pdev->ep_in[_cmdEpAdd & 0x0F].is_used = 1;

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
	USBD_LL_CloseEP(pdev, _inEpAdd);
	pdev->ep_in[_inEpAdd & 0xFU].is_used = 0U;

	// Close EP OUT
	//
	USBD_LL_CloseEP(pdev, _outEpAdd);
	pdev->ep_out[_outEpAdd & 0xFU].is_used = 0;

	// Close Command IN EP
	//
	USBD_LL_CloseEP(pdev, _cmdEpAdd);
	pdev->ep_in[_cmdEpAdd & 0xFU].is_used = 0;
	pdev->ep_in[_cmdEpAdd & 0xFU].bInterval = 0;

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


bool USBDeviceClassCDC::classGetHSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpCmdDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_HS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;

	data = USBD_CDC_CfgDesc;
	length = sizeof(USBD_CDC_CfgDesc);

	return true;
}


bool USBDeviceClassCDC::classGetFSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpCmdDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_FS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	data = USBD_CDC_CfgDesc;
	length = sizeof(USBD_CDC_CfgDesc);

	return true;
}


bool USBDeviceClassCDC::classGetOtherSpeedConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpCmdDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_FS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	data = USBD_CDC_CfgDesc;
	length = sizeof(USBD_CDC_CfgDesc);

	return true;
}


bool USBDeviceClassCDC::classGetDeviceQualifierDescriptor(
	uint8_t *&data,
	unsigned &length) {

	data = USBD_CDC_DeviceQualifierDesc;
	length = sizeof(USBD_CDC_DeviceQualifierDesc);

	return true;
}


bool USBDeviceClassCDC::usesEndPoint(
	uint8_t epAdd) const {

	return (epAdd == _inEpAdd) || (epAdd == _outEpAdd);
}

