#include "eos.h"
#include "eosAssert.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "Controllers/USBDevice/ST/st_usbd_ctlreq.h"
#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"


using namespace eos;


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
	_interface {interface} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void USBDeviceClassCDC::initialize() {

	auto pdev = _drvUSBD->getHandle();
	USBD_RegisterClass(pdev, this);
}


bool USBDeviceClassCDC::setTxBuffer(
	uint8_t *buffer,
	unsigned length) {

	_cdc.txBuffer = buffer;
	_cdc.txLength = length;

	return true;
}


bool USBDeviceClassCDC::setRxBuffer(
	uint8_t *buffer) {

    _cdc.rxBuffer = buffer;

	return true;
}


bool USBDeviceClassCDC::transmitPacket() {

	if (_cdc.txState == 0) {
		_cdc.txState = 1U;

		auto pdev = _drvUSBD->getHandle();
		pdev->ep_in[_inEpAdd & 0xFU].total_length = _cdc.txLength;
		USBD_LL_Transmit(pdev, _inEpAdd, _cdc.txBuffer, _cdc.txLength);

		return true;
	}
	else
		return false;
}


bool USBDeviceClassCDC::receivePacket() {

	auto pdev = _drvUSBD->getHandle();
	bool hs = pdev->dev_speed == USBD_SPEED_HIGH;

    USBD_LL_PrepareReceive(pdev, _outEpAdd, _cdc.rxBuffer, hs ? CDC_DATA_HS_OUT_PACKET_SIZE : CDC_DATA_FS_OUT_PACKET_SIZE);

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Inicializa la clase.
///
int8_t USBDeviceClassCDC::classInit(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	USBD_memset(&_cdc, 0, sizeof(_cdc));

	pdev->pClassDataCmsit[pdev->classId] = &_cdc;
	pdev->pClassData = pdev->pClassDataCmsit[pdev->classId];

	bool hs = pdev->dev_speed == USBD_SPEED_HIGH;

    // Open EP IN
   	//
   	USBD_LL_OpenEP(pdev, _inEpAdd, USBD_EP_TYPE_BULK, hs ? CDC_DATA_HS_IN_PACKET_SIZE :  CDC_DATA_FS_IN_PACKET_SIZE);
   	pdev->ep_in[_inEpAdd & 0xFU].is_used = 1;

   	// Open EP OUT
   	//
   	USBD_LL_OpenEP(pdev, _outEpAdd, USBD_EP_TYPE_BULK, hs ? CDC_DATA_HS_OUT_PACKET_SIZE : CDC_DATA_FS_OUT_PACKET_SIZE);
   	pdev->ep_out[_outEpAdd & 0xFU].is_used = 1;

   	// Set bInterval for CDC CMD Endpoint
   	//
   	pdev->ep_in[_cmdEpAdd & 0xFU].bInterval = hs ? CDC_HS_BINTERVAL : CDC_FS_BINTERVAL;

    // Open Command IN EP
   	//
    USBD_LL_OpenEP(pdev, _cmdEpAdd, USBD_EP_TYPE_INTR, CDC_CMD_PACKET_SIZE);
    pdev->ep_in[_cmdEpAdd & 0xFU].is_used = 1;

    _cdc.rxBuffer = nullptr;

    // Inicialitza l'interficie
    //
  	_interface->initialize(this);

  	/* Init Xfer states */
  	_cdc.txState = 0;
  	_cdc.rxState = 0;

  	// S'ha d'inicialitzar-se en _interface->initialize();
  	//
  	if (_cdc.rxBuffer == NULL)
  		return USBD_EMEM;

	USBD_LL_PrepareReceive(pdev, _outEpAdd, _cdc.rxBuffer, hs ? CDC_DATA_HS_OUT_PACKET_SIZE : CDC_DATA_FS_OUT_PACKET_SIZE);

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief     Desinicialitza la clase.
///
int8_t USBDeviceClassCDC::classDeinit(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	// Close EP IN
	//
	USBD_LL_CloseEP(pdev, _inEpAdd);
	pdev->ep_in[_inEpAdd & 0xFU].is_used = 0U;

	// Close EP OUT
	//
	USBD_LL_CloseEP(pdev, _outEpAdd);
	pdev->ep_out[_outEpAdd & 0xFU].is_used = 0U;

	// Close Command IN EP
	//
	USBD_LL_CloseEP(pdev, _cmdEpAdd);
	pdev->ep_in[_cmdEpAdd & 0xFU].is_used = 0U;
	pdev->ep_in[_cmdEpAdd & 0xFU].bInterval = 0U;

	// DeInit  physical Interface components
	//
	if (pdev->pClassDataCmsit[pdev->classId] != nullptr) {
		_interface->deinitialize(this);
	    pdev->pClassDataCmsit[pdev->classId] = nullptr;
	    pdev->pClassData = nullptr;
	}

	return USBD_OK;
}


int8_t USBDeviceClassCDC::classSetup(
	USBD_SetupReqTypedef *req) {

	auto pdev = _drvUSBD->getHandle();

	uint16_t len;
	uint8_t ifalt = 0U;
	uint16_t status_info = 0U;

	USBD_StatusTypeDef ret = USBD_OK;

	switch (req->bmRequest & USB_REQ_TYPE_MASK) {
		case USB_REQ_TYPE_CLASS:
			if (req->wLength != 0U) {
				if ((req->bmRequest & 0x80U) != 0U) {
					_interface->control((CDCInterface::ControlCmd)req->bRequest, (uint8_t *)_cdc.data, req->wLength);

					len = MIN(CDC_REQ_MAX_DATA_SIZE, req->wLength);
					USBD_CtlSendData(pdev, (uint8_t *) _cdc.data, len);
				}
				else {
					_cdc.cmdOpCode = req->bRequest;
					_cdc.cmdLength = (uint8_t) MIN(req->wLength, USB_MAX_EP0_SIZE);

					USBD_CtlPrepareRx(pdev, (uint8_t*) _cdc.data, _cdc.cmdLength);
				}
			}
			else
				_interface->control((CDCInterface::ControlCmd) req->bRequest, (uint8_t *)req, 0U);
			break;

		case USB_REQ_TYPE_STANDARD:
			switch (req->bRequest) {
				case USB_REQ_GET_STATUS:
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						USBD_CtlSendData(pdev, (uint8_t *)&status_info, 2U);
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_GET_INTERFACE:
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						USBD_CtlSendData(pdev, &ifalt, 1U);
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_SET_INTERFACE:
					if (pdev->dev_state != USBD_STATE_CONFIGURED) {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_CLEAR_FEATURE:
					break;

				default:
					USBD_CtlError(pdev, req);
					ret = USBD_FAIL;
					break;
			}
			break;

		default:
			USBD_CtlError(pdev, req);
			ret = USBD_FAIL;
			break;
	}

	return ret;
}


int8_t USBDeviceClassCDC::classEP0TxSent() {

	return USBD_FAIL;
}


int8_t USBDeviceClassCDC::classEP0RxReady() {

	if (_cdc.cmdOpCode != 0xFFU) {
		_interface->control((CDCInterface::ControlCmd) _cdc.cmdOpCode, (uint8_t *)_cdc.data, (uint16_t)_cdc.cmdLength);
		_cdc.cmdOpCode = 0xFFU;
	}

	return USBD_OK;
}


int8_t USBDeviceClassCDC::classDataIn(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef *)pdev->pData;

	if ((pdev->ep_in[epnum & 0xFU].total_length > 0U) &&
       ((pdev->ep_in[epnum & 0xFU].total_length % hpcd->IN_ep[epnum & 0xFU].maxpacket) == 0U)) {

		/* Update the packet total length */
		pdev->ep_in[epnum & 0xFU].total_length = 0U;

		/* Send ZLP */
		USBD_LL_Transmit(pdev, epnum, NULL, 0U);
	}
  	else {
  		_cdc.txState = 0U;
  		_interface->txDataCompleted(_cdc.txBuffer, &_cdc.txLength, epnum);
  	}

    return USBD_OK;
}


int8_t USBDeviceClassCDC::classDataOut(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

	if (pdev->pClassDataCmsit[pdev->classId] == nullptr)
		return USBD_FAIL;

	/* Get the received data length */
	hcdc->rxLength = USBD_LL_GetRxDataSize(pdev, epnum);

	/* USB data will be immediately processed, this allow next USB traffic being
  	   NAKed till the end of the application Xfer */
	_interface->rxDataAvailable(hcdc->rxBuffer, &hcdc->rxLength);

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


uint8_t* USBDeviceClassCDC::classGetHSConfigurationDescriptor(
	uint16_t *length) {

	auto pEpCmdDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_HS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;

	*length = (uint16_t)sizeof(USBD_CDC_CfgDesc);

	return USBD_CDC_CfgDesc;
}


uint8_t* USBDeviceClassCDC::classGetFSConfigurationDescriptor(
	uint16_t *length) {

	auto pEpCmdDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_FS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	*length = (uint16_t)sizeof(USBD_CDC_CfgDesc);
	return USBD_CDC_CfgDesc;
}


uint8_t* USBDeviceClassCDC::classGetOtherSpeedConfigurationDescriptor(
	uint16_t *length) {

	auto pEpCmdDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_FS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	*length = (uint16_t)sizeof(USBD_CDC_CfgDesc);
	return USBD_CDC_CfgDesc;
}


uint8_t* USBDeviceClassCDC::classGetDeviceQualifierDescriptor(
	uint16_t *length) {

	*length = (uint16_t)sizeof(USBD_CDC_DeviceQualifierDesc);
	return USBD_CDC_DeviceQualifierDesc;
}
