#include "eos.h"
#include "eosAssert.h"
#include "HTL/htl.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "Controllers/USBDevice/ST/st_usbd_ctlreq.h"
#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"
#include "System/eosMath.h"


using namespace eos;
using namespace htl;


static constexpr uint8_t __ifaceQty = 2;


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

	USBDeviceClass {drvUSBD, reserveIface(__ifaceQty)},
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
   	// TODO: Provisional
   	pdev->ep_in[_cmdEpAddr & 0x0F].bInterval = hs ? CDC_HS_BINTERVAL : CDC_FS_BINTERVAL;
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
	pdev->ep_in[_inEpAddr & 0x0F].is_used = 0;

	// Close EP OUT
	//
	USBD_LL_CloseEP(pdev, _outEpAddr);
	pdev->ep_out[_outEpAddr & 0x0F].is_used = 0;

	// Close Command IN EP
	//
	USBD_LL_CloseEP(pdev, _cmdEpAddr);
	pdev->ep_in[_cmdEpAddr & 0x0F].is_used = 0;
	pdev->ep_in[_cmdEpAddr & 0x0F].bInterval = 0;

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
					auto len = min(CDC_REQ_MAX_DATA_SIZE, (unsigned) req->length);
					USBD_CtlSendData(pdev, (uint8_t *) _cdc.data, len);
				}
				else {
					_req_requestID = getCDCRequestID(req);
					_req_length = min(USB_MAX_EP0_SIZE, (unsigned) req->length);
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

	// Si hi ha una solicitut pendent, la procesa
	//
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
	EpAddr epAddr) {

	auto pdev = _drvUSBD->getHandle();

	PCD_HandleTypeDef *pcd = (PCD_HandleTypeDef *)pdev->pData;

	if ((pdev->ep_in[epAddr & 0x0F].total_length > 0) &&
       ((pdev->ep_in[epAddr & 0x0F].total_length % pcd->IN_ep[epAddr & 0x0F].maxpacket) == 0)) {

		pdev->ep_in[epAddr & 0x0F].total_length = 0;
		USBD_LL_Transmit(pdev, epAddr, nullptr, 0);
	}
  	else {
  		_interface->txDataCompleted(_txBuffer, _txLength, epAddr);
  		_state = State::idle;
  	}

    return USBD_OK;
}


int8_t USBDeviceClassCDC::classDataOut(
	EpAddr epAddr) {

	auto pdev = _drvUSBD->getHandle();

	_rxLength = USBD_LL_GetRxDataSize(pdev, epAddr);
	_interface->rxDataAvailable(_rxBuffer, _rxLength);
	_state = State::idle;

	return USBD_OK;
}


int8_t USBDeviceClassCDC::classSOF() {

	return USBD_FAIL;
}


int8_t USBDeviceClassCDC::classIsoINIncomplete(
	EpAddr apAddr) {

	return USBD_FAIL;
}


int8_t USBDeviceClassCDC::classIsoOUTIncomplete(
	EpAddr epAddr) {

	return USBD_FAIL;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el interface descriptor
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: Tamany del buffer.
/// \param    hs: Indica velocitat FS
/// \return   El nombre de bytes escrits en el buffer. Zero en cas d'error.
///
unsigned USBDeviceClassCDC::classGetInterfaceDescriptors(
	uint8_t *buffer,
	unsigned bufferSize,
	bool hs) {

	auto maxPacketSize = hs ? CDC_DATA_HS_MAX_PACKET_SIZE : CDC_DATA_FS_MAX_PACKET_SIZE;
	auto ptr = buffer;
	auto ptrEnd = buffer + bufferSize;

	// Interface association descriptor
	//
	if (ptr + sizeof(USBD_InterfaceAssociationDescriptor) > ptrEnd)
		return 0;
	auto ifaceAssociationDescriptor = (USBD_InterfaceAssociationDescriptor*) ptr;
	ifaceAssociationDescriptor->bLength = sizeof(USBD_InterfaceAssociationDescriptor);
	ifaceAssociationDescriptor->bDescriptorType = (uint8_t) DescriptorType::interfaceAssociation;
	ifaceAssociationDescriptor->bFirstInterface = _iface;
	ifaceAssociationDescriptor->bInterfaceCount = __ifaceQty;
	ifaceAssociationDescriptor->bFunctionClass = 2;
	ifaceAssociationDescriptor->bFunctionSubClass = 2;
	ifaceAssociationDescriptor->bFunctionProtocol = 1;
	ifaceAssociationDescriptor->iFunction = 0;
	ptr += sizeof(USBD_InterfaceAssociationDescriptor);

	// Interface descriptor 1
	//
	if (ptr + sizeof(USBD_InterfaceDescriptor) > ptrEnd)
		return 0;
	auto iface1Descriptor = (USBD_InterfaceDescriptor*) ptr;
	iface1Descriptor->bLength = sizeof(USBD_InterfaceDescriptor);
	iface1Descriptor->bDescriptorType = (uint8_t) DescriptorType::interface;
	iface1Descriptor->bInterfaceNumber = _iface;
	iface1Descriptor->bAlternateSetting = 0;
	iface1Descriptor->bNumEndPoints = 1;
	iface1Descriptor->bInterfaceClass = (uint8_t) ClassID::cdc;
	iface1Descriptor->bInterfaceSubClass = 0x02;
	iface1Descriptor->bInterfaceProtocol = 0x01;
	iface1Descriptor->iInterface = 0;
	ptr += sizeof(USBD_InterfaceDescriptor);

	// Header functional descriptor
	//
	if (ptr + sizeof(CDCHeaderFunctionalDescriptor) > ptrEnd)
		return 0;
	auto headerFunctionalDescriptor = (CDCHeaderFunctionalDescriptor*) ptr;
	headerFunctionalDescriptor->bFunctionLength = sizeof(CDCHeaderFunctionalDescriptor);
	headerFunctionalDescriptor->bDescriptorType = (uint8_t) CDCDescriptorType::cdcInterface;
	headerFunctionalDescriptor->bDescriptorSubType = (uint8_t) CDCDescriptorSubType::cdcHeader;
	headerFunctionalDescriptor->bcdCDC = 0x0110;
	ptr += sizeof(CDCHeaderFunctionalDescriptor);

	// Call management functional descriptor
	//
	if (ptr + sizeof(CDCCallManagementFunctionalDescriptor) > ptrEnd)
		return 0;
	auto callManagementFunctionalDescriptor = (CDCCallManagementFunctionalDescriptor*) ptr;
	callManagementFunctionalDescriptor->bFunctionLength = sizeof(CDCCallManagementFunctionalDescriptor);
	callManagementFunctionalDescriptor->bDescriptorType = (uint8_t) CDCDescriptorType::cdcInterface;
	callManagementFunctionalDescriptor->bDescriptorSubType = (uint8_t) CDCDescriptorSubType::cdcCallManagement;
	callManagementFunctionalDescriptor->bmCapabilities = 0x00;
	callManagementFunctionalDescriptor->bDataInterface = 0x01;
	ptr += sizeof(CDCCallManagementFunctionalDescriptor);

	// ACM functional descriptor
	//
	if (ptr + sizeof(CDCACMFunctionalDescriptor) > ptrEnd)
		return 0;
	auto acmFunctionalDescriptor = (CDCACMFunctionalDescriptor*) ptr;
	acmFunctionalDescriptor->bFunctionLength = sizeof(CDCACMFunctionalDescriptor);
	acmFunctionalDescriptor->bDescriptorType = (uint8_t) CDCDescriptorType::cdcInterface;
	acmFunctionalDescriptor->bDescriptorSubType = (uint8_t) CDCDescriptorSubType::cdcAbstractControlManagement;
	acmFunctionalDescriptor->bmCapabilities = 0x02;
	ptr += sizeof(CDCACMFunctionalDescriptor);

	// Union functional descriptor
	//
	if (ptr + sizeof(CDCUnionFunctionalDescriptor) > ptrEnd)
		return 0;
	auto unionFunctionalDescriptor = (CDCUnionFunctionalDescriptor*) ptr;
	unionFunctionalDescriptor->bFunctionLength = sizeof(CDCUnionFunctionalDescriptor);
	unionFunctionalDescriptor->bDescriptorType = (uint8_t) CDCDescriptorType::cdcInterface;
	unionFunctionalDescriptor->bDescriptorSubType = (uint8_t) CDCDescriptorSubType::cdcUnion;
	unionFunctionalDescriptor->bMasterInterface = 0x00;
	unionFunctionalDescriptor->bSlaveInterface[0] = 0x01;
	ptr += sizeof(CDCUnionFunctionalDescriptor);

	// CMD endpoint descriptor
	//
	if (ptr + sizeof(USBD_EndPointDescriptor) > ptrEnd)
		return 0;
	auto cmdEpDescriptor = (USBD_EndPointDescriptor*) ptr;
	cmdEpDescriptor->bLength = sizeof(USBD_EndPointDescriptor);
	cmdEpDescriptor->bDescriptorType = (uint8_t) DescriptorType::endPoint;
	cmdEpDescriptor->bEndPointAddress = _cmdEpAddr;
	cmdEpDescriptor->bmAttributes = 0x03;
	cmdEpDescriptor->wMaxPacketSize = CDC_CMD_PACKET_SIZE;
	cmdEpDescriptor->bInterval = CDC_FS_BINTERVAL;
	ptr += sizeof(USBD_EndPointDescriptor);

	// Interface descriptor 2
	//
	if (ptr + sizeof(USBD_InterfaceDescriptor) > ptrEnd)
		return 0;
	auto iface2Descriptor = (USBD_InterfaceDescriptor*) ptr;
	iface2Descriptor->bLength = sizeof(USBD_InterfaceDescriptor);
	iface2Descriptor->bDescriptorType = (uint8_t) DescriptorType::interface;
	iface2Descriptor->bInterfaceNumber = _iface + 1;
	iface2Descriptor->bAlternateSetting = 0;
	iface2Descriptor->bNumEndPoints = 2;
	iface2Descriptor->bInterfaceClass = (uint8_t) ClassID::cdcData;
	iface2Descriptor->bInterfaceSubClass = 0x00;
	iface2Descriptor->bInterfaceProtocol = 0x00;
	iface2Descriptor->iInterface = 0;
	ptr += sizeof(USBD_InterfaceDescriptor);

	// OUT endpoint descriptor
	//
	if (ptr + sizeof(USBD_EndPointDescriptor) > ptrEnd)
		return 0;
	auto outEpDescriptor = (USBD_EndPointDescriptor*) ptr;
	outEpDescriptor->bLength = sizeof(USBD_EndPointDescriptor);
	outEpDescriptor->bDescriptorType = (uint8_t) DescriptorType::endPoint;
	outEpDescriptor->bEndPointAddress = _outEpAddr;
	outEpDescriptor->bmAttributes = 0x02;
	outEpDescriptor->wMaxPacketSize = maxPacketSize;
	outEpDescriptor->bInterval = 0;
	ptr += sizeof(USBD_EndPointDescriptor);

	// IN endpoint destriptor
	//
	if (ptr + sizeof(USBD_EndPointDescriptor) > ptrEnd)
		return 0;
	auto inEpDescriptor = (USBD_EndPointDescriptor*) ptr;
	inEpDescriptor->bLength = sizeof(USBD_EndPointDescriptor);
	inEpDescriptor->bDescriptorType = (uint8_t) DescriptorType::endPoint;
	inEpDescriptor->bEndPointAddress = _inEpAddr;
	inEpDescriptor->bmAttributes = 0x02;
	inEpDescriptor->wMaxPacketSize = maxPacketSize;
	inEpDescriptor->bInterval = 0;
	ptr += sizeof(USBD_EndPointDescriptor);

	return ptr - buffer;
}


/// ----------------------------------------------------------------------
/// \brief    Informa si el endpoint esta en us.
/// \param    epAddr: El endpoint.
/// \return   True si esta en un, false en cas contrari.
///
bool USBDeviceClassCDC::usesEndPoint(
	EpAddr epAddr) const {

	return (epAddr == _inEpAddr) || (epAddr == _outEpAddr) || (epAddr == _cmdEpAddr);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si s'utilitza el interface especificat.
/// \param    ifase: El numero del interface.
/// \return   True si s'utilitza, false en cas contrari.
///
bool USBDeviceClassCDC::usesIface(
	uint8_t iface) const {

	return (iface >= _iface) && (iface < (_iface + __ifaceQty));
}

