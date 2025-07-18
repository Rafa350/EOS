#include "eos.h"
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"
#include "Controllers/USBDevice/MSC/eosSCSIProcessor.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
/// \param    devUSBD: El dispositiu USB
/// \param    iface: El interface que gestiona.
/// \param    storage: El magatzem de dades
///
USBDeviceClassMSC::USBDeviceClassMSC(
	USBDeviceDriver *drvUSBD,
	const USBDeviceClassMSCConfiguration *configuration,
	MSCStorage *storage) :

	USBDeviceClass {drvUSBD, configuration->iface},
	_storage {storage},
	_scsi {new SCSIProcessor(storage, drvUSBD->getHandle())},
	_inEpAddr {configuration->inEpAddr},
	_outEpAddr {configuration->outEpAddr} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \return   El resultat de l'operacio.
///
Result USBDeviceClassMSC::initializeImpl() {

	// Inicialitza el magatzem de dades
	//
	if (_storage->initialize() != Results::success)
		return Results::error;

	// Inicialitza el procesador SCSI
	//
	if (_scsi->initialize(_inEpAddr, _outEpAddr, &_msc) != Results::success)
		return Results::error;

	// TODO: Provisional
	auto pdev = _drvUSBD->getHandle();
	USBD_RegisterClass(pdev, this);

	return Results::success;
}


int8_t USBDeviceClassMSC::classInitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();
	bool hs = pdev->dev_speed == USBD_SPEED_HIGH;

    // Open EP OUT
	//
    USBD_LL_OpenEP(pdev, _outEpAddr, USBD_EP_TYPE_BULK, hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);
    pdev->ep_out[_outEpAddr & 0x0F].is_used = 1;

    // Open EP IN
    //
	USBD_LL_OpenEP(pdev, _inEpAddr, USBD_EP_TYPE_BULK, hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);
	pdev->ep_in[_inEpAddr & 0x0F].is_used = 1;

	botInitialize();

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classDeinitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	// Close EP OUT
	//
	USBD_LL_CloseEP(pdev, _outEpAddr);
	pdev->ep_out[_outEpAddr & 0x0F].is_used = 0;

	// Close EP IN
	//
	USBD_LL_CloseEP(pdev, _inEpAddr);
	pdev->ep_in[_inEpAddr & 0x0F].is_used = 0;

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

						uint8_t maxLun = min(_storage->getMaxLun(), MSC_BOT_MAX_LUN);
						_msc.max_lun = maxLun;
						USBD_CtlSendData(pdev, &maxLun, 1); // !Atencio buffer/length
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
						USBD_CtlSendData(pdev, (uint8_t*) &status, 2); // !Atencio buffer/length
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


/// ----------------------------------------------------------------------
/// \brief    Obte els descriptors del interface.
/// \param    buffer: Buffer on deixar les dades.
/// \param    bufferSize: Tamany del buffer.
/// \return   El nombre de bytes escrits en el buffer. Zero en cas d'error.
///
unsigned USBDeviceClassMSC::classGetInterfaceDescriptors(
	uint8_t *buffer,
	unsigned bufferSize,
	bool hs) {

	auto size = sizeof(USBD_InterfaceDescriptor) + sizeof(USBD_EndPointDescriptor) * 2;
	if (bufferSize < size)
		return 0;

	unsigned maxPacketSize = hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET;

	// Interface
	//
	auto ifaceDescriptor = (USBD_InterfaceDescriptor*) buffer;
	ifaceDescriptor->bLength = sizeof(USBD_InterfaceDescriptor);
	ifaceDescriptor->bDescriptorType = (uint8_t) DescriptorType::interface;
	ifaceDescriptor->bInterfaceNumber = _iface;
	ifaceDescriptor->bAlternateSetting = 0;
	ifaceDescriptor->bNumEndPoints = 2;
	ifaceDescriptor->bInterfaceClass = (uint8_t) ClassID::msc;
	ifaceDescriptor->bInterfaceSubClass = 0x06;
	ifaceDescriptor->bInterfaceProtocol = 0x50;
	ifaceDescriptor->iInterface = 5;

	// EndPoint 1
	//
	auto ep1Descriptor = (USBD_EndPointDescriptor*) (buffer + sizeof(USBD_InterfaceDescriptor));
	ep1Descriptor->bLength = sizeof(USBD_EndPointDescriptor);
	ep1Descriptor->bDescriptorType = (uint8_t) DescriptorType::endPoint;
	ep1Descriptor->bEndPointAddress = _inEpAddr;
	ep1Descriptor->bmAttributes = 0x02;
	ep1Descriptor->wMaxPacketSize = maxPacketSize;
	ep1Descriptor->bInterval = 0;

	// EndPoint 2
	//
	auto ep2Descriptor = (USBD_EndPointDescriptor*) (buffer + sizeof(USBD_InterfaceDescriptor) + sizeof(USBD_EndPointDescriptor));
	ep2Descriptor->bLength = sizeof(USBD_EndPointDescriptor);
	ep2Descriptor->bDescriptorType = (uint8_t) DescriptorType::endPoint;
	ep2Descriptor->bEndPointAddress = _outEpAddr;
	ep2Descriptor->bmAttributes = 0x02;
	ep2Descriptor->wMaxPacketSize = maxPacketSize;
	ep2Descriptor->bInterval = 0;

	return size;
}


bool USBDeviceClassMSC::classGetHSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpInDesc = _drvUSBD->getEpDescriptor(_inEpAddr);
	if (pEpInDesc == nullptr)
		return false;

	auto pEpOutDesc = _drvUSBD->getEpDescriptor(_outEpAddr);
	if (pEpOutDesc == nullptr)
		return false;

	pEpInDesc->wMaxPacketSize = MSC_MAX_HS_PACKET;
	pEpOutDesc->wMaxPacketSize = MSC_MAX_HS_PACKET;

	auto configurationDescriptor = _drvUSBD->getConfigurationDescriptor();
	data = (uint8_t*) configurationDescriptor;
	length = configurationDescriptor->wTotalLength;

	return true;
}


bool USBDeviceClassMSC::classGetFSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto pEpInDesc = _drvUSBD->getEpDescriptor(_inEpAddr);
	if (pEpInDesc == nullptr)
		return false;

	auto pEpOutDesc = _drvUSBD->getEpDescriptor(_outEpAddr);
	if (pEpOutDesc == nullptr)
		return false;

	pEpInDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;
	pEpOutDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	auto configurationDescriptor = _drvUSBD->getConfigurationDescriptor();
	data = (uint8_t*) configurationDescriptor;
	length = configurationDescriptor->wTotalLength;

	return true;
}


bool USBDeviceClassMSC::classGetOtherSpeedConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto inEpDesc = _drvUSBD->getEpDescriptor(_inEpAddr);
	if (inEpDesc == nullptr)
		return false;

	auto outEpDesc = _drvUSBD->getEpDescriptor(_outEpAddr);
	if (outEpDesc == nullptr)
		return false;

	inEpDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;
	outEpDesc->wMaxPacketSize = MSC_MAX_FS_PACKET;

	auto configurationDescriptor = _drvUSBD->getConfigurationDescriptor();
	data = (uint8_t*) configurationDescriptor;
	length = configurationDescriptor->wTotalLength;


	return true;
}


bool USBDeviceClassMSC::classGetDeviceQualifierDescriptor(
	uint8_t *&data,
	unsigned &length) {

	auto descriptor = (USBD_DeviceQualifierDescriptor*) _drvUSBD->getConfiguration()->deviceQualifierDescriptor;
	if (descriptor == nullptr)
		return false;

	data = (uint8_t*) descriptor;
	length = descriptor->bLength;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si s'utilitza els endPoint especificat.
/// \param    epAddr: L'adressa del endPoint.
/// \return   True si s'utilitza, false en cas contrari.
///
bool USBDeviceClassMSC::usesEndPoint(
	uint8_t epAddr) const {

	return (epAddr == _inEpAddr) || (epAddr == _outEpAddr);
}


void USBDeviceClassMSC::botInitialize() {

	auto pdev = _drvUSBD->getHandle();

	_msc.bot_state = USBD_BOT_IDLE;
	_msc.bot_status = USBD_BOT_STATUS_NORMAL;

	USBD_LL_FlushEP(pdev, _outEpAddr);
	USBD_LL_FlushEP(pdev, _inEpAddr);
	USBD_LL_PrepareReceive(pdev, _outEpAddr, (uint8_t*) &_msc.cbw, USBD_BOT_CBW_LENGTH);
}


void USBDeviceClassMSC::botDeInitialize() {

    _msc.bot_state = USBD_BOT_IDLE;
}


void USBDeviceClassMSC::botReset() {

	auto pdev = _drvUSBD->getHandle();

	_msc.bot_state  = USBD_BOT_IDLE;
	_msc.bot_status = USBD_BOT_STATUS_RECOVERY;

	USBD_LL_ClearStallEP(pdev, _inEpAddr);
	USBD_LL_ClearStallEP(pdev, _outEpAddr);
	USBD_LL_PrepareReceive(pdev, _outEpAddr, (uint8_t *) &_msc.cbw, USBD_BOT_CBW_LENGTH);
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


void USBDeviceClassMSC::botDataOut(
	uint8_t epnum) {

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

	USBD_LL_Transmit(pdev, _inEpAddr, (uint8_t*) &_msc.csw, USBD_BOT_CSW_LENGTH);
	USBD_LL_PrepareReceive(pdev, _outEpAddr, (uint8_t*) &_msc.cbw, USBD_BOT_CBW_LENGTH);
}


void USBDeviceClassMSC::botCplClrFeature(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	if (_msc.bot_status == USBD_BOT_STATUS_ERROR) {
		USBD_LL_StallEP(pdev, _inEpAddr);
		USBD_LL_StallEP(pdev, _outEpAddr);
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

	USBD_LL_Transmit(pdev, _inEpAddr, buffer, min((unsigned) _msc.cbw.dDataLength, length));
}


void USBDeviceClassMSC::botCBWDecode() {

	auto pdev = _drvUSBD->getHandle();

	_msc.csw.dTag = _msc.cbw.dTag;
	_msc.csw.dDataResidue = _msc.cbw.dDataLength;

	if ((USBD_LL_GetRxDataSize(pdev, _outEpAddr) != USBD_BOT_CBW_LENGTH) ||
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
		USBD_LL_StallEP(pdev, _outEpAddr);

	USBD_LL_StallEP(pdev, _inEpAddr);

	if (_msc.bot_status == USBD_BOT_STATUS_ERROR) {
		USBD_LL_StallEP(pdev, _inEpAddr);
		USBD_LL_StallEP(pdev, _outEpAddr);
	}
}

