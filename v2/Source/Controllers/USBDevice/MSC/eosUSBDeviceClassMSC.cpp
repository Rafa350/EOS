#include "eos.h"
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"
#include "Controllers/USBDevice/MSC/eosSCSIProcessor.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "System/eosMath.h"


using namespace eos;


static constexpr uint8_t __ifaceQty = 1;


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
/// \param    devUSBD: El dispositiu USB
/// \param    iface: El interface que gestiona.
/// \param    storage: El magatzem de dades
///
USBDeviceClassMSC::USBDeviceClassMSC(
	USBDeviceDriver *drvUSBD,
	const USBDeviceClassMSCConfiguration *configuration) :

	USBDeviceClass {drvUSBD, reserveIface(__ifaceQty)},
	_storage {configuration->storage},
	_scsi {new SCSIProcessor(configuration->storage, drvUSBD->getHandle())},
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

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut dirigides al interficie
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceClassMSC::processInterfaceRequest(
	USBD_SetupReqTypedef *request) {

	auto ok = false;
	auto pdev = _drvUSBD->getHandle();

	switch (request->getType()) {
		case USBDRequestType::clase:

			switch (getMSCRequestID(request)) {
				case  MSCRequestID::botGetMaxLun:
					return processInterfaceRequest_GetMaxLUN(request);

				case MSCRequestID::botReset:
					return processInterfaceRequest_BotReset(request);

				default:
					ctlError();
					return false;
			}
			break;

		case USBDRequestType::standard:
			switch (request->getRequestID()) {

				case USBDRequestID::getStatus:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						uint16_t status = 0;
						ctlSendData((uint8_t*) &status, sizeof(status));
						ok = true;
					}
					break;

				case USBDRequestID::getInterface:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						ctlSendData((uint8_t*) &_msc.interface, 1);
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
							USBD_LL_FlushEP(pdev, LOBYTE(request->index));
							botCplClrFeature(EpAddr(LOBYTE(request->index)));
						}
					}
					ok = true;
					break;

				default:
					ctlError();
					return false;
			}
			break;

		default:
			ctlError();
			return false;
	}

	if (!ok)
		ctlError();

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'GET_MAX_LUN'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceClassMSC::processInterfaceRequest_GetMaxLUN(
	USBD_SetupReqTypedef *request) {

	auto ok = false;

	// Verifica la sol·licitut
	//
	if ((request->value == 0) &&
		(request->length == 1) &&
		(request->getDirection() == USBDRequestDirection::deviceToHost)) {

		uint8_t maxLun = min(_storage->getMaxLun(), MSC_BOT_MAX_LUN);
		_msc.max_lun = maxLun;

		ctlSendData(&maxLun, 1);

		ok = true;
	}

	if (!ok)
		ctlError();

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'BOT_RESET'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceClassMSC::processInterfaceRequest_BotReset(
	USBD_SetupReqTypedef *request) {

	auto ok = false;

	// Verifica la sol·lisitut
	//
	if ((request->value  == 0) &&
		(request->length == 0) &&
		(request->getDirection() == USBDRequestDirection::hostToDevice)) {

		botReset();

		ctlSendStatus();

		ok = true;
	}

	if (!ok)
		ctlError();

	return ok;
}


int8_t USBDeviceClassMSC::classInitialize(
	uint8_t configIdx) {

	auto pdev = _drvUSBD->getHandle();
	auto hs = pdev->dev_speed == USBD_SPEED_HIGH;

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
	uint8_t configIdx) {

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

	auto ok = false;
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
						ctlSendData(&maxLun, 1); // !Atencio buffer/length
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
						ctlSendData((uint8_t*) &status, sizeof(status));
						ok = true;
					}
					break;

				case USBDRequestID::getInterface:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						ctlSendData((uint8_t*) &_msc.interface, 1);
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
							USBD_LL_FlushEP(pdev, LOBYTE(request->index));
							botCplClrFeature(EpAddr(LOBYTE(request->index)));
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
		ctlError();

	return ok ? USBD_OK : USBD_FAIL;
}


int8_t USBDeviceClassMSC::classEP0TxSent() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classEP0RxReady() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classDataIn(
	EpAddr epAddr) {

	botDataIn(epAddr);

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classDataOut(
		EpAddr epAddr) {

	botDataOut(epAddr);

	return USBD_OK;
}


int8_t USBDeviceClassMSC::classSOF() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classIsoINIncomplete(
		EpAddr epAddr) {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classIsoOUTIncomplete(
		EpAddr epAddr) {

	return USBD_FAIL;
}


/// ----------------------------------------------------------------------
/// \brief    Obte els descriptors del interface.
/// \param    buffer: Buffer on deixar les dades.
/// \param    bufferSize: Tamany del buffer.
/// \param    length: El nombre de bytes escrits en el buffer.
/// \return   True si tot es correcte.
///
bool USBDeviceClassMSC::buildInterfaceDescriptors(
	uint8_t *buffer,
	unsigned bufferSize,
	bool hs,
	unsigned &length) {

	auto maxPacketSize = hs ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET;

	auto ptr = buffer;
	auto ptrEnd = buffer + bufferSize;

	// Interface association descriptor
	//
	if (ptr + sizeof(USBD_InterfaceAssociationDescriptor) > ptrEnd)
		return false;
	auto ifaceAssociationDescriptor = (USBD_InterfaceAssociationDescriptor*) ptr;
	ifaceAssociationDescriptor->bLength = sizeof(USBD_InterfaceAssociationDescriptor);
	ifaceAssociationDescriptor->bDescriptorType = (uint8_t) DescriptorType::interfaceAssociation;
	ifaceAssociationDescriptor->bFirstInterface = _iface;
	ifaceAssociationDescriptor->bInterfaceCount = __ifaceQty;
	ifaceAssociationDescriptor->bFunctionClass = (uint8_t) ClassID::msc;
	ifaceAssociationDescriptor->bFunctionSubClass = (uint8_t) MSCSubClassID::scsiTransparentCommandSet;
	ifaceAssociationDescriptor->bFunctionProtocol = (uint8_t) MSCProtocolID::bulkOnlyTransport;
	ifaceAssociationDescriptor->iFunction = 0;
	ptr += sizeof(USBD_InterfaceAssociationDescriptor);

	// Interface descriptor
	//
	if (ptr + sizeof(USBD_InterfaceDescriptor) > ptrEnd)
		return false;
	auto ifaceDescriptor = (USBD_InterfaceDescriptor*) ptr;
	ifaceDescriptor->bLength = sizeof(USBD_InterfaceDescriptor);
	ifaceDescriptor->bDescriptorType = (uint8_t) DescriptorType::interface;
	ifaceDescriptor->bInterfaceNumber = _iface;
	ifaceDescriptor->bAlternateSetting = 0;
	ifaceDescriptor->bNumEndPoints = 2;
	ifaceDescriptor->bInterfaceClass = (uint8_t) ClassID::msc;
	ifaceDescriptor->bInterfaceSubClass = (uint8_t) MSCSubClassID::scsiTransparentCommandSet;
	ifaceDescriptor->bInterfaceProtocol = (uint8_t) MSCProtocolID::bulkOnlyTransport;
	ifaceDescriptor->iInterface = 0;
	ptr += sizeof(USBD_InterfaceDescriptor);

	// IN endpoint descriptor
	//
	if (ptr + sizeof(USBD_EndPointDescriptor) > ptrEnd)
		return false;
	auto inEpDescriptor = (USBD_EndPointDescriptor*) ptr;
	inEpDescriptor->bLength = sizeof(USBD_EndPointDescriptor);
	inEpDescriptor->bDescriptorType = (uint8_t) DescriptorType::endPoint;
	inEpDescriptor->bEndPointAddress = _inEpAddr;
	inEpDescriptor->bmAttributes = 0x02;
	inEpDescriptor->wMaxPacketSize = maxPacketSize;
	inEpDescriptor->bInterval = 0;
	ptr += sizeof(USBD_EndPointDescriptor);

	// OUT endpoint descriptor
	//
	if (ptr + sizeof(USBD_EndPointDescriptor) > ptrEnd)
		return false;
	auto outEpDescriptor = (USBD_EndPointDescriptor*) ptr;
	outEpDescriptor->bLength = sizeof(USBD_EndPointDescriptor);
	outEpDescriptor->bDescriptorType = (uint8_t) DescriptorType::endPoint;
	outEpDescriptor->bEndPointAddress = _outEpAddr;
	outEpDescriptor->bmAttributes = 0x02;
	outEpDescriptor->wMaxPacketSize = maxPacketSize;
	outEpDescriptor->bInterval = 0;
	ptr += sizeof(USBD_EndPointDescriptor);

	length = ptr - buffer;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si s'utilitza els endpoint especificat.
/// \param    epAddr: L'adressa del endPoint.
/// \return   True si s'utilitza, false en cas contrari.
///
bool USBDeviceClassMSC::usesEndPoint(
	EpAddr epAddr) const {

	return (epAddr == _inEpAddr) || (epAddr == _outEpAddr);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si s'utilitza el interface especificat.
/// \param    ifase: El numero del interface.
/// \return   True si s'utilitza, false en cas contrari.
///
bool USBDeviceClassMSC::usesIface(
	uint8_t iface) const {

	return (iface >= _iface) && (iface < (_iface + __ifaceQty));
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
	EpAddr epAddr) {

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
	EpAddr epAddr) {

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
	EpAddr epAddr) {

	auto pdev = _drvUSBD->getHandle();

	if (_msc.bot_status == USBD_BOT_STATUS_ERROR) {
		USBD_LL_StallEP(pdev, _inEpAddr);
		USBD_LL_StallEP(pdev, _outEpAddr);
	}
	else if (((epAddr & 0x80) == 0x80) && (_msc.bot_status != USBD_BOT_STATUS_RECOVERY))
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
		(_msc.cbw.bCBLength < 1) ||
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

