#include "eos.h"
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"
#include "Controllers/USBDevice/MSC/eosSCSIProcessor.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "System/eosMath.h"


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

	_storage->initialize();

	auto pdev = _drvUSBD->getHandle();
	USBD_RegisterClass(pdev, this);
}


int8_t USBDeviceClassMSC::classInitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();
	bool hs = pdev->dev_speed == USBD_SPEED_HIGH;

    // Open EP OUT
	//
    USBD_LL_OpenEP(pdev, _outEpAdd, USBD_EP_TYPE_BULK, hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);
    pdev->ep_out[_outEpAdd & 0x0F].is_used = 1;

    // Open EP IN
    //
	USBD_LL_OpenEP(pdev, _inEpAdd, USBD_EP_TYPE_BULK, hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);
	pdev->ep_in[_inEpAdd & 0x0F].is_used = 1;

	botInitialize();

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classDeinitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	// Close EP OUT
	//
	USBD_LL_CloseEP(pdev, _outEpAdd);
	pdev->ep_out[_outEpAdd & 0x0F].is_used = 0;

	// Close EP IN
	//
	USBD_LL_CloseEP(pdev, _inEpAdd);
	pdev->ep_in[_inEpAdd & 0x0F].is_used = 0;

	// Free MSC Class Resources
	//
	botDeInitialize();

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classSetup(
	USBD_SetupReqTypedef *request) {

	bool ok = false;

	auto pdev = _drvUSBD->getHandle();

	switch (request->getType()) {

		case USBDRequestType::clase:
			switch (getMSCRequestID(request)) {

				case  MSCRequestID::botGetMaxLun:
					if ((request->value  == 0) &&
						(request->length == 1) &&
						(request->getDirection() == USBDRequestDirection::deviceToHost)) {

						int8_t maxLun = _storage->getMaxLun();
						_msc.max_lun = min((int8_t) MSC_BOT_MAX_LUN, maxLun);
						USBD_CtlSendData(pdev, (uint8_t*) &maxLun, 1);
						ok = true;
					}
					break;

				case MSCRequestID::botReset:
					if ((request->value  == 0) &&
						(request->length == 0) &&
						(request->getDirection() == USBDRequestDirection::hostToDevice)) {

						botReset();
						ok = true;
					}
					break;
			}
			break;

		case USBDRequestType::standard:
			switch (request->getRequestID()) {

				case USBDRequestID::getStatus:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						uint16_t status = 0;
						USBD_CtlSendData(pdev, (uint8_t*) &status, 2);
						ok = true;
					}
					break;

				case USBDRequestID::getInterface:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						USBD_CtlSendData(pdev, (uint8_t*) &_msc.interface, 1);
						ok = true;
					}
					break;

				case USBDRequestID::setInterface:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						_msc.interface = (uint8_t) request->value;
						ok = true;
					}
					break;

				case USBDRequestID::clearFeature:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						if (request->value == USB_FEATURE_EP_HALT)	{
							USBD_LL_FlushEP(pdev, (uint8_t) request->index);
							botCplClrFeature((uint8_t) request->index);
						}
					}
					ok = true;
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}

	if (!ok)
		USBD_CtlError(pdev, request);

	return ok ? USBD_OK : USBD_FAIL;
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


bool USBDeviceClassMSC::classGetHSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = MSC_MAX_HS_PACKET;

	auto pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = MSC_MAX_HS_PACKET;

	data = USBD_MSC_CfgDesc;
	length = sizeof(USBD_MSC_CfgDesc);

	return true;
}


bool USBDeviceClassMSC::classGetFSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	auto pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	data = USBD_MSC_CfgDesc;
	length = sizeof(USBD_MSC_CfgDesc);

	return true;
}


bool USBDeviceClassMSC::classGetOtherSpeedConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	auto pEpOutDesc =(USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_MSC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;


	data = USBD_MSC_CfgDesc;
	length = sizeof(USBD_MSC_CfgDesc);

	return true;
}


bool USBDeviceClassMSC::classGetDeviceQualifierDescriptor(
	uint8_t *&data,
	unsigned &length) {

	data = USBD_MSC_DeviceQualifierDesc;
	length = sizeof(USBD_MSC_DeviceQualifierDesc);

	return true;
}


bool USBDeviceClassMSC::usesEndPoint(
	uint8_t epAdd) const {

	return (epAdd == _inEpAdd) || (epAdd == _outEpAdd);
}



void USBDeviceClassMSC::botInitialize() {

	auto pdev = _drvUSBD->getHandle();

	_msc.bot_state = USBD_BOT_IDLE;
	_msc.bot_status = USBD_BOT_STATUS_NORMAL;

	_scsi->initialize();

	//_storage->initialize(0);

	USBD_LL_FlushEP(pdev, _outEpAdd);
	USBD_LL_FlushEP(pdev, _inEpAdd);
	USBD_LL_PrepareReceive(pdev, _outEpAdd, (uint8_t*) &_msc.cbw, USBD_BOT_CBW_LENGTH);
}


void USBDeviceClassMSC::botDeInitialize() {

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
			if (!_scsi->processCmd(_msc.cbw.bLUN, &_msc.cbw.CB[0]))
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
			if (!_scsi->processCmd(_msc.cbw.bLUN, &_msc.cbw.CB[0]))
				botSendCSW(USBD_CSW_CMD_FAILED);
			break;
	}
}


void USBDeviceClassMSC::botSendCSW(
	uint8_t cswStatus) {

	auto pdev = _drvUSBD->getHandle();

	_msc.csw.dSignature = USBD_BOT_CSW_SIGNATURE;
	_msc.csw.bStatus = cswStatus;
	_msc.bot_state = USBD_BOT_IDLE;

	USBD_LL_Transmit(pdev, _inEpAdd, (uint8_t*) &_msc.csw, USBD_BOT_CSW_LENGTH);
	USBD_LL_PrepareReceive(pdev, _outEpAdd, (uint8_t*) &_msc.cbw, USBD_BOT_CBW_LENGTH);
}


void USBDeviceClassMSC::botCplClrFeature(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	if (_msc.bot_status == USBD_BOT_STATUS_ERROR) {
		USBD_LL_StallEP(pdev, _inEpAdd);
		USBD_LL_StallEP(pdev, _outEpAdd);
	}
	else if (((epnum & 0x80) == 0x80) && (_msc.bot_status != USBD_BOT_STATUS_RECOVERY))
		botSendCSW(USBD_CSW_CMD_FAILED);
}


void USBDeviceClassMSC::botSendData(
	uint8_t *buffer,
	unsigned length) {

	auto pdev = _drvUSBD->getHandle();

	_msc.csw.dDataResidue -= length;
	_msc.csw.bStatus = USBD_CSW_CMD_PASSED;
	_msc.bot_state = USBD_BOT_SEND_DATA;

	USBD_LL_Transmit(pdev, _inEpAdd, buffer, min((unsigned) _msc.cbw.dDataLength, length));
}


void USBDeviceClassMSC::botCBWDecode() {

	auto pdev = _drvUSBD->getHandle();

	_msc.csw.dTag = _msc.cbw.dTag;
	_msc.csw.dDataResidue = _msc.cbw.dDataLength;

	if ((USBD_LL_GetRxDataSize(pdev, _outEpAdd) != USBD_BOT_CBW_LENGTH) ||
		(_msc.cbw.dSignature != USBD_BOT_CBW_SIGNATURE) ||
	    (_msc.cbw.bLUN > _msc.max_lun) ||
		(_msc.cbw.bCBLength < 1U) ||
	    (_msc.cbw.bCBLength > 16)) {
		_scsi->senseCode(_msc.cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
		_msc.bot_status = USBD_BOT_STATUS_ERROR;
		botAbort();
	}

	else {
		if (!_scsi->processCmd(_msc.cbw.bLUN, &_msc.cbw.CB[0])) {
			if (_msc.bot_state == USBD_BOT_NO_DATA)
				botSendCSW(USBD_CSW_CMD_FAILED);
			else
				botAbort();
		}

		else if ((_msc.bot_state != USBD_BOT_DATA_IN) &&
				 (_msc.bot_state != USBD_BOT_DATA_OUT) &&
				 (_msc.bot_state != USBD_BOT_LAST_DATA_IN)) {
			if (_msc.bot_data_length > 0)
				botSendData(_msc.bot_data, _msc.bot_data_length);
			else if (_msc.bot_data_length == 0)
				botSendCSW(USBD_CSW_CMD_PASSED);
			else
				botAbort();
		}
	}
}


void USBDeviceClassMSC::botAbort() {

	auto pdev = _drvUSBD->getHandle();

	if ((_msc.cbw.bmFlags == 0) &&
	    (_msc.cbw.dDataLength != 0) &&
	    (_msc.bot_status == USBD_BOT_STATUS_NORMAL))
		USBD_LL_StallEP(pdev, _outEpAdd);

	USBD_LL_StallEP(pdev, _inEpAdd);

	if (_msc.bot_status == USBD_BOT_STATUS_ERROR) {
		USBD_LL_StallEP(pdev, _inEpAdd);
		USBD_LL_StallEP(pdev, _outEpAdd);
	}
}

