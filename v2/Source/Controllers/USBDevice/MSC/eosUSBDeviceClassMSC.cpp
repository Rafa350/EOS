#include "eos.h"
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"
#include "Controllers/USBDevice/MSC/eosSCSIProcessor.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"


using namespace eos;


extern uint8_t USBD_MSC_CfgDesc[USB_MSC_CONFIG_DESC_SIZ];
extern uint8_t USBD_MSC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];



/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
///
USBDeviceClassMSC::USBDeviceClassMSC(
	USBDeviceDriver *drvUSBD,
	MSCStorage *storage) :

	USBDeviceClass {drvUSBD},
	_storage {storage},
	_scsi {new SCSIProcessor(storage, drvUSBD->getHandle(), _inEpAdd, _outEpAdd, &_msc)} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void USBDeviceClassMSC::initialize() {

	auto pdev = _drvUSBD->getHandle();
	USBD_RegisterClass(pdev, this);
}


int8_t USBDeviceClassMSC::classInit(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	pdev->pClassDataCmsit[pdev->classId] = &_msc;
	pdev->pClassData = pdev->pClassDataCmsit[pdev->classId];
	pdev->pUserData[pdev->classId] = _storage;

	bool hs = pdev->dev_speed == USBD_SPEED_HIGH;

    // Open EP OUT
	//
    USBD_LL_OpenEP(pdev, _outEpAdd, USBD_EP_TYPE_BULK, hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);
    pdev->ep_out[_outEpAdd & 0xFU].is_used = 1U;

    // Open EP IN
    //
	USBD_LL_OpenEP(pdev, _inEpAdd, USBD_EP_TYPE_BULK, hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);
	pdev->ep_in[_inEpAdd & 0xFU].is_used = 1U;

	botInit();

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classDeinit(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	// Close EP OUT
	//
	USBD_LL_CloseEP(pdev, _outEpAdd);
	pdev->ep_out[_outEpAdd & 0xFU].is_used = 0U;

	// Close EP IN
	//
	USBD_LL_CloseEP(pdev, _inEpAdd);
	pdev->ep_in[_inEpAdd & 0xFU].is_used = 0U;

	// Free MSC Class Resources
	//
	if (pdev->pClassDataCmsit[pdev->classId] != NULL) {
		botDeInit();
		pdev->pClassDataCmsit[pdev->classId]  = NULL;
		pdev->pClassData = NULL;
	}

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classSetup(
	USBD_SetupReqTypedef *req) {

	USBD_StatusTypeDef ret = USBD_OK;
	uint32_t max_lun;
	uint16_t status_info = 0U;

	auto pdev = _drvUSBD->getHandle();

	switch (req->requestType & USB_REQ_TYPE_MASK) {

		case USB_REQ_TYPE_CLASS:
			switch (req->requestID) {
				case BOT_GET_MAX_LUN:
					if ((req->value  == 0U) &&
						(req->length == 1U) &&
						((req->requestType & 0x80U) == 0x80U)) {
						max_lun = _storage->getMaxLun();
						_msc.max_lun = (max_lun > MSC_BOT_MAX_LUN) ? MSC_BOT_MAX_LUN : max_lun;
						USBD_CtlSendData(pdev, (uint8_t*) &_msc.max_lun, 1U);
					}
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case BOT_RESET:
					if ((req->value  == 0U) &&
						(req->length == 0U) &&
						((req->requestType & 0x80U) != 0x80U)) {
						botReset();
					}
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				default:
					USBD_CtlError(pdev, req);
					ret = USBD_FAIL;
					break;
			}
			break;

		case USB_REQ_TYPE_STANDARD:
			switch (req->requestID) {
				case USB_REQ_GET_STATUS:
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						USBD_CtlSendData(pdev, (uint8_t *) &status_info, 2U);
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_GET_INTERFACE:
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						USBD_CtlSendData(pdev, (uint8_t*) &_msc.interface, 1U);
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_SET_INTERFACE:
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						_msc.interface = (uint8_t)(req->value);
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_CLEAR_FEATURE:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						if (req->value == USB_FEATURE_EP_HALT)	{
							USBD_LL_FlushEP(pdev, (uint8_t) req->index);
							botCplClrFeature((uint8_t) req->index);
						}
					}
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


int8_t USBDeviceClassMSC::classEP0TxSent() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classEP0RxReady() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classDataIn(
	uint8_t epnum) {

	botDataIn(epnum);

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classDataOut(
	uint8_t epnum) {

	botDataOut(epnum);

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classSOF() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classIsoINIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classIsoOUTIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}


uint8_t* USBDeviceClassMSC::classGetHSConfigurationDescriptor(
	uint16_t *length) {

	USBD_EpDescTypeDef *pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _inEpAdd);
	if (pEpInDesc != NULL)
		pEpInDesc->wMaxPacketSize = MSC_MAX_HS_PACKET;

	USBD_EpDescTypeDef *pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != NULL)
		pEpOutDesc->wMaxPacketSize = MSC_MAX_HS_PACKET;

	*length = (uint16_t)sizeof(USBD_MSC_CfgDesc);
	return USBD_MSC_CfgDesc;
}


uint8_t* USBDeviceClassMSC::classGetFSConfigurationDescriptor(
	uint16_t *length) {

	USBD_EpDescTypeDef *pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _inEpAdd);
	if (pEpInDesc != NULL)
		pEpInDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	USBD_EpDescTypeDef *pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != NULL)
		pEpOutDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	*length = (uint16_t)sizeof(USBD_MSC_CfgDesc);
	return USBD_MSC_CfgDesc;
}


uint8_t* USBDeviceClassMSC::classGetOtherSpeedConfigurationDescriptor(
	uint16_t *length) {

	USBD_EpDescTypeDef *pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _inEpAdd);
	if (pEpInDesc != NULL)
		pEpInDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	USBD_EpDescTypeDef *pEpOutDesc =(USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != NULL)
		pEpOutDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;


	*length = (uint16_t)sizeof(USBD_MSC_CfgDesc);
	return USBD_MSC_CfgDesc;
}


uint8_t* USBDeviceClassMSC::classGetDeviceQualifierDescriptor(
	uint16_t *length) {

	*length = (uint16_t)sizeof(USBD_MSC_DeviceQualifierDesc);
	return USBD_MSC_DeviceQualifierDesc;
}


void USBDeviceClassMSC::botInit() {

	auto pdev = _drvUSBD->getHandle();

	_msc.bot_state = USBD_BOT_IDLE;
	_msc.bot_status = USBD_BOT_STATUS_NORMAL;

	_scsi->initialize();

	_storage->initialize(0);

	USBD_LL_FlushEP(pdev, _outEpAdd);
	USBD_LL_FlushEP(pdev, _inEpAdd);
	USBD_LL_PrepareReceive(pdev, _outEpAdd, (uint8_t*) &_msc.cbw, USBD_BOT_CBW_LENGTH);
}


void USBDeviceClassMSC::botDeInit() {

    _msc.bot_state = USBD_BOT_IDLE;
}


void USBDeviceClassMSC::botReset() {

	auto pdev = _drvUSBD->getHandle();

	_msc.bot_state  = USBD_BOT_IDLE;
	_msc.bot_status = USBD_BOT_STATUS_RECOVERY;

	USBD_LL_ClearStallEP(pdev, _inEpAdd);
	USBD_LL_ClearStallEP(pdev, _outEpAdd);
	USBD_LL_PrepareReceive(pdev, _outEpAdd, (uint8_t *) &_msc.cbw, USBD_BOT_CBW_LENGTH);
}


void USBDeviceClassMSC::botDataIn(
	uint8_t epnum) {

	switch (_msc.bot_state) {
		case USBD_BOT_DATA_IN:
			if (_scsi->processCmd(_msc.cbw.bLUN, &_msc.cbw.CB[0]) < 0)
				botSendCSW(USBD_CSW_CMD_FAILED);
			break;

		case USBD_BOT_SEND_DATA:
		case USBD_BOT_LAST_DATA_IN:
			botSendCSW(USBD_CSW_CMD_PASSED);
			break;
	}
}


void USBDeviceClassMSC::botDataOut(uint8_t epnum) {

	switch (_msc.bot_state) {
		case USBD_BOT_IDLE:
			botCBWDecode();
			break;

		case USBD_BOT_DATA_OUT:
			if (_scsi->processCmd(_msc.cbw.bLUN, &_msc.cbw.CB[0]) < 0)
				botSendCSW(USBD_CSW_CMD_FAILED);
			break;
	}
}


void USBDeviceClassMSC::botSendCSW(
	uint8_t CSW_Status) {

	auto pdev = _drvUSBD->getHandle();

	_msc.csw.dSignature = USBD_BOT_CSW_SIGNATURE;
	_msc.csw.bStatus = CSW_Status;
	_msc.bot_state = USBD_BOT_IDLE;

	USBD_LL_Transmit(pdev, _inEpAdd, (uint8_t*) &_msc.csw, USBD_BOT_CSW_LENGTH);
	USBD_LL_PrepareReceive(pdev, _outEpAdd, (uint8_t*) &_msc.cbw, USBD_BOT_CBW_LENGTH);
}


void USBDeviceClassMSC::botCplClrFeature(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	if (_msc.bot_status == USBD_BOT_STATUS_ERROR) 	{
		USBD_LL_StallEP(pdev, _inEpAdd);
		USBD_LL_StallEP(pdev, _outEpAdd);
	}
	else if (((epnum & 0x80U) == 0x80U) && (_msc.bot_status != USBD_BOT_STATUS_RECOVERY))
		botSendCSW(USBD_CSW_CMD_FAILED);
}


void USBDeviceClassMSC::botSendData(
	uint8_t *buffer,
	unsigned length) {

	auto pdev = _drvUSBD->getHandle();

	length = MIN(_msc.cbw.dDataLength, length);

	_msc.csw.dDataResidue -= length;
	_msc.csw.bStatus = USBD_CSW_CMD_PASSED;
	_msc.bot_state = USBD_BOT_SEND_DATA;

	USBD_LL_Transmit(pdev, _inEpAdd, buffer, length);
}


void USBDeviceClassMSC::botCBWDecode() {

	auto pdev = _drvUSBD->getHandle();

	_msc.csw.dTag = _msc.cbw.dTag;
	_msc.csw.dDataResidue = _msc.cbw.dDataLength;

	if ((USBD_LL_GetRxDataSize(pdev, _outEpAdd) != USBD_BOT_CBW_LENGTH) ||
		(_msc.cbw.dSignature != USBD_BOT_CBW_SIGNATURE) ||
	    (_msc.cbw.bLUN > _msc.max_lun) ||
		(_msc.cbw.bCBLength < 1U) ||
	    (_msc.cbw.bCBLength > 16U)) {
		_scsi->senseCode(_msc.cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
		_msc.bot_status = USBD_BOT_STATUS_ERROR;
		botAbort();
	}

	else {
		if (_scsi->processCmd(_msc.cbw.bLUN, &_msc.cbw.CB[0]) < 0) {
			if (_msc.bot_state == USBD_BOT_NO_DATA) {
				botSendCSW(USBD_CSW_CMD_FAILED);
			}
			else {
				botAbort();
			}
		}

		/* Burst xfer handled internally */
		else if ((_msc.bot_state != USBD_BOT_DATA_IN) &&
				 (_msc.bot_state != USBD_BOT_DATA_OUT) &&
				 (_msc.bot_state != USBD_BOT_LAST_DATA_IN)) {
			if (_msc.bot_data_length > 0U) {
				botSendData(_msc.bot_data, _msc.bot_data_length);
			}
			else if (_msc.bot_data_length == 0U) {
				botSendCSW(USBD_CSW_CMD_PASSED);
			}
			else {
				botAbort();
			}
		}
	}
}


void USBDeviceClassMSC::botAbort() {

	auto pdev = _drvUSBD->getHandle();

	if ((_msc.cbw.bmFlags == 0U) &&
	    (_msc.cbw.dDataLength != 0U) &&
	    (_msc.bot_status == USBD_BOT_STATUS_NORMAL))
		USBD_LL_StallEP(pdev, _outEpAdd);

	USBD_LL_StallEP(pdev, _inEpAdd);

	if (_msc.bot_status == USBD_BOT_STATUS_ERROR) {
		USBD_LL_StallEP(pdev, _inEpAdd);
		USBD_LL_StallEP(pdev, _outEpAdd);
	}
}
