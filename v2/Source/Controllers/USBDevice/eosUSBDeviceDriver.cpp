#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "System/eosMath.h"


using namespace eos;


static uint8_t __responseData[internal::maxRequestResponseDataSize] __attribute__((aligned(4)));


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    configuration: La configuracio del dispositiu
///
USBDeviceDriver::USBDeviceDriver(
	const USBDeviceDriverConfiguration *configuration) :

	_state {State::reset},
	_manufacturerStr {configuration->manufacturerStr},
	_productStr {configuration->productStr},
	_serialNumberStr {configuration->serialNumberStr},
	_languageID {configuration->languageID},
	_productID {configuration->productID},
	_vendorID {configuration->vendorID},
	_maxEp0Size {configuration->maxEp0Size},
	_maxPower {configuration->maxPower} {
}


/// ----------------------------------------------------------------------
/// \brief    Registra una clase de dispositiu.
/// \param    devClasss: La clase a registrar.
/// \return   El resultst de l'operacio.
///
Result USBDeviceDriver::registerClass(
	USBDeviceClass *devClass) {

	if (_state != State::reset)
		return Results::errorState;

	_classes.pushFront(devClass);

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \param    descriptors: Els descriptors del dispositiu USB
/// \return   El resultst de l'operacio.
///
Result USBDeviceDriver::initialize() {

	if (_state != State::reset)
		return Results::errorState;

	_usbd._instance = this;

	if (USBD_Init(&_usbd, nullptr, 0) != USBD_StatusTypeDef::USBD_OK)
		return Results::error;

	for (auto cls: _classes)
		cls->initialize();

	_state = State::ready;

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia les operacions de USB. Es controla tot per interrupcions.
/// \return   El resultat de l'operacio
///
Result USBDeviceDriver::start() {

	if (_state != State::ready)
		return Results::errorState;

	if (USBD_LL_Start(&_usbd) != USBD_StatusTypeDef::USBD_OK)
		return Results::error;

	_state = State::running;

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza les operacions del USB.
/// \return   El resultat de l'operacio
///
Result USBDeviceDriver::stop() {

	if (_state != State::running)
		return Results::errorState;

	if (USBD_LL_Stop(&_usbd) != USBD_StatusTypeDef::USBD_OK)
		return Results::error;

	for (auto cls: _classes)
		cls->classDeinitialize(_usbd.dev_config);

	_state = State::ready;

	return Results::success;
}


USBD_StatusTypeDef USBDeviceDriver::setClassConfig(
	uint8_t configIdx) {

	USBD_StatusTypeDef ret = USBD_OK;

	for (auto cls: _classes) {
		if (cls->classInitialize(configIdx) != USBD_OK)
			ret = USBD_FAIL;
	}

	return ret;
}


USBD_StatusTypeDef USBDeviceDriver::clearClassConfig(
	uint8_t configIdx) {

	USBD_StatusTypeDef ret = USBD_OK;

	for (auto cls: _classes) {
		if (cls->classDeinitialize(configIdx) != USBD_OK)
			ret = USBD_FAIL;
	}

	return ret;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la clase de dispositiu associat al endpoint
/// \param    epAddr: El endpoint.
/// \return   La classe associada. Null en cas d'error.
///
USBDeviceClass *USBDeviceDriver::getClassFromEndPoint(
	EpAddr epAddr) const {

	for (auto cls: _classes)
		if (cls->usesEndPoint(epAddr))
			return cls;

	return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la clase de dispositiu associat al interface
/// \param    iface: El interface.
/// \return   La classe associada. Null en cas d'error.
///
USBDeviceClass *USBDeviceDriver::getClassFromInterface(
	uint8_t iface) const {

	for (auto cls: _classes)
		if (cls->usesIface(iface))
			return cls;

	return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona el setup
/// \param    data: Dades de configuracio.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::setupStage(
	uint8_t *data) {

	auto pdev = getHandle();

	pdev->request.requestType = data[0];
	pdev->request.requestID = data[1];
	pdev->request.value = (uint16_t) data[2] | ((uint16_t) data[3] << 8);
	pdev->request.index = (uint16_t) data[4] | ((uint16_t) data[5] << 8);
	pdev->request.length = data[6];

	pdev->ep0_state = USBD_EP0_SETUP;
	pdev->ep0_data_len = data[6];

	return processRequest(&pdev->request);
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona l'arribada de dades del host.
/// \param    epAddr: El endpoint.
///
bool USBDeviceDriver::dataOutStage(
	EpAddr epAddr) {

	bool ok = false;

	if (epAddr == 0) {

	}

	else {
		auto cls = getClassFromEndPoint(epAddr);
		if (cls == nullptr)
			return false;
		ok = cls->classDataOut(epAddr) == USBD_OK;
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Gestion la sortida de dades cap el host.
/// \param    epAddr: El endpoint.
///
bool USBDeviceDriver::dataInStage(
	EpAddr epAddr) {

	bool ok = false;

	if (epAddr == 0) {
	}

	else {
		auto cls = getClassFromEndPoint(epAddr);
		if (cls == nullptr)
			return false;
		ok = cls->classDataIn(epAddr) == USBD_OK;
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Despatxa una solicitut.
/// \param    request: La solicitut.
/// \return   El resultat de l'operacio.
///
bool USBDeviceDriver::processRequest(
	USBD_SetupReqTypedef *request) {

	switch (request->getRecipient()) {

		case USBDRequestRecipient::device:
			return processDeviceRequest(request);

		case USBDRequestRecipient::interface:
			return processInterfaceRequest(request);

		case USBDRequestRecipient::endPoint:
			return processEndPointRequest(request);

		default:
			return USBD_LL_StallEP(getHandle(), request->requestType & 0x80) == USBD_OK;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'device'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest(
	USBD_SetupReqTypedef *request) {

	auto ok = false;

	switch (request->getType()) {

		case USBDRequestType::clase:
		case USBDRequestType::vendor: {
			// TODO: Revisar
			auto cls = getClass();
			ok = cls->classSetup(request) == USBD_OK;
			break;
		}

		case USBDRequestType::standard:
			switch (request->getRequestID()) {

				case USBDRequestID::getDescriptor:
					if (request->getDirection() == USBDRequestDirection::deviceToHost)
						ok = processDeviceRequest_GetDescriptor(request);
					break;

				case USBDRequestID::setAddress:
					if (request->getDirection() == USBDRequestDirection::hostToDevice)
						ok = processDeviceRequest_SetAddress(request);
					break;

				case USBDRequestID::setConfiguration:
					if (request->getDirection() == USBDRequestDirection::hostToDevice)
						ok = processDeviceRequest_SetConfiguration(request);
					break;

				case USBDRequestID::getConfiguration:
					if (request->getDirection() == USBDRequestDirection::deviceToHost)
						ok = processDeviceRequest_GetConfiguration(request);
					break;

				case USBDRequestID::getStatus:
					if (request->getDirection() == USBDRequestDirection::deviceToHost)
						ok = processDeviceRequest_GetStatus(request);
					break;

				case USBDRequestID::setFeature:
					if (request->getDirection() == USBDRequestDirection::hostToDevice)
						ok = processDeviceRequest_SetFeature(request);
					break;

				case USBDRequestID::clearFeature:
					if (request->getDirection() == USBDRequestDirection::hostToDevice)
						ok = processDeviceRequest_ClearFeature(request);
					break;

				default:
					ctlError(request);
					break;
			}
			break;

		default:
			ctlError(request);
			break;
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'getDescriptor'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_GetDescriptor(
	USBD_SetupReqTypedef *request) {

	unsigned length = 0;
	uint8_t *data = nullptr;

	auto ok = false;
    auto pdev = getHandle();

    switch (request->getValueDescriptorType()) {

        case USBDRequestValueDescriptorType::device:
            ok = getDeviceDescriptor(__responseData, sizeof(__responseData), length);
           	data = __responseData;
            break;

        case USBDRequestValueDescriptorType::configuration:
        	ok = getConfigurationDescriptor(__responseData, sizeof(__responseData), length, pdev->dev_speed == USBD_SPEED_HIGH);
        	data = __responseData;
        	break;

        case USBDRequestValueDescriptorType::string: {
        	auto idx = request->getValueDescriptorIndex();
        	switch (idx) {
        		case USBD_IDX_LANGID_STR:
        			ok = getLangIDStrDescriptor(__responseData, sizeof(__responseData), length);
        			data = __responseData;
        			break;

        		case USBD_IDX_CONFIG_STR:
        			ok = getConfigurationStrDescriptor(data, length);
        			break;

        		case USBD_IDX_INTERFACE_STR:
        			ok = getInterfaceStrDescriptor(data, length);
        			break;

        		case USBD_IDX_MFC_STR:
        			ok = getManufacturerStrDescriptor(data, length);
        			break;

        		case USBD_IDX_PRODUCT_STR:
        			ok = getProductStrDescriptor(data, length);
        			break;

        		case USBD_IDX_SERIAL_STR:
        			ok = getSerialStrDescriptor(data, length);
        			break;

        		default:
        			break;
        	}
        	break;
        }

    	case USBDRequestValueDescriptorType::deviceQualifier: {
   			ok = getDeviceQualifierDescriptor(__responseData, sizeof(__responseData), length);
   			data = __responseData;
    		break;
    	}

    	case USBDRequestValueDescriptorType::otherSpeedConfiguration:
    		break;

    	default:
    		break;
    }

    if (ok) {
		if (request->length != 0) {
			length = min(length, (unsigned) request->length);
			ctlSendData(data, length);
		}
		else
			ctlSendStatus();
    }
    else
    	ctlError(request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'setAddress'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetAddress(
	USBD_SetupReqTypedef *request) {

    auto ok = false;
    auto pdev = getHandle();

	if ((request->index == 0) &&
		(request->length == 0) &&
		(request->value <= 0x007F)) {

		uint8_t addr = request->value;
	    if (pdev->dev_state != USBD_STATE_CONFIGURED) {

	    	pdev->dev_address = addr;
	    	USBD_LL_SetUSBAddress(pdev, addr);
	    	ctlSendStatus();
	    	if (addr != 0)
	    		pdev->dev_state = USBD_STATE_ADDRESSED;
	    	else
	    		pdev->dev_state = USBD_STATE_DEFAULT;
	    	ok = true;
	    }
	}

	if (!ok)
		ctlError(request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'clearFeature'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_ClearFeature(
	USBD_SetupReqTypedef *request) {

    auto ok = false;
    auto pdev = getHandle();

    switch (pdev->dev_state) {
		case USBD_STATE_DEFAULT:
		case USBD_STATE_ADDRESSED:
		case USBD_STATE_CONFIGURED:
			if (request->value == USB_FEATURE_REMOTE_WAKEUP) {
				pdev->dev_remote_wakeup = 0;
				ctlSendStatus();
			}
			ok = true;
			break;
	}

    if (!ok)
		ctlError(request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'setFeature'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetFeature(
	USBD_SetupReqTypedef *request) {

    auto ok = false;
    auto pdev = getHandle();

    if (request->value == USB_FEATURE_REMOTE_WAKEUP) {
	    pdev->dev_remote_wakeup = 1;
	    ctlSendStatus();
	    ok = true;
    }
	else if (request->value == USB_FEATURE_TEST_MODE) {
		pdev->dev_test_mode = (uint8_t)(request->index >> 8);
	    ctlSendStatus();
	    ok = true;
	}

    if (!ok)
	    ctlError(request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'getConfiguration'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_GetConfiguration(
	USBD_SetupReqTypedef *request) {

    bool ok = false;
    auto pdev = getHandle();

    if (request->length == 1) {
		switch (pdev->dev_state) {
			case USBD_STATE_DEFAULT:
			case USBD_STATE_ADDRESSED:
				pdev->dev_default_config = 0U;
				ctlSendData((uint8_t *)&pdev->dev_default_config, 1);
				ok = true;
				break;

			case USBD_STATE_CONFIGURED:
				ctlSendData((uint8_t *)&pdev->dev_config, 1);
				ok = true;
				break;
		}
	}

    if (!ok)
		ctlError(request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'setConfiguration'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetConfiguration(
	USBD_SetupReqTypedef *request) {

    bool ok = false;
    auto pdev = getHandle();

	static uint8_t cfgidx;

	cfgidx = (uint8_t)(request->value);

	if (cfgidx > USBD_MAX_NUM_CONFIGURATION) {
		ctlError(request);
		return false;
	}

	switch (pdev->dev_state) {
		case USBD_STATE_ADDRESSED:
			if (cfgidx != 0) {

				pdev->dev_config = cfgidx;
				ok = setClassConfig(cfgidx) == USBD_OK;
				if (!ok) {
					ctlError(request);
					pdev->dev_state = USBD_STATE_ADDRESSED;
				}
				else {
					ctlSendStatus();
					pdev->dev_state = USBD_STATE_CONFIGURED;
				}
			}
			else {
				ctlSendStatus();
				ok = true;
			}
			break;

		case USBD_STATE_CONFIGURED:
			if (cfgidx == 0) {
				pdev->dev_state = USBD_STATE_ADDRESSED;
				pdev->dev_config = cfgidx;
				USBD_ClrClassConfig(pdev, cfgidx);
				ctlSendStatus();
				ok = true;
			}
			else if (cfgidx != pdev->dev_config) {
				/* Clear old configuration */
				USBD_ClrClassConfig(pdev, (uint8_t)pdev->dev_config);

				/* set new configuration */
				pdev->dev_config = cfgidx;

				ok = USBD_SetClassConfig(pdev, cfgidx) == USBD_OK;
				if (!ok) {
					ctlError(request);
					USBD_ClrClassConfig(pdev, (uint8_t) pdev->dev_config);
					pdev->dev_state = USBD_STATE_ADDRESSED;
				}
				else
					ctlSendStatus();
			}
			else {
				ctlSendStatus();
				ok = true;
			}
			break;

		default:
			ctlError(request);
			USBD_ClrClassConfig(pdev, cfgidx);
			break;
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'getStatus'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_GetStatus(
	USBD_SetupReqTypedef *request) {

    bool ok = false;
    auto pdev = getHandle();

    switch (pdev->dev_state) {
    	case USBD_STATE_DEFAULT:
	    case USBD_STATE_ADDRESSED:
	    case USBD_STATE_CONFIGURED:
	    	if (request->length == 2) {
#if (USBD_SELF_POWERED == 1)
	    		pdev->dev_config_status = USB_CONFIG_SELF_POWERED;
#else
	    		pdev->dev_config_status = 0;
#endif // USBD_SELF_POWERED

	    		if (pdev->dev_remote_wakeup != 0)
	    			pdev->dev_config_status |= USB_CONFIG_REMOTE_WAKEUP;

	    		ctlSendData((uint8_t*) &pdev->dev_config_status, 2);
	    		ok = true;
	    	}
	    	break;
    }

    if (!ok)
	   ctlError(request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'interface'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processInterfaceRequest(
	USBD_SetupReqTypedef *request) {

	auto ok = false;
    auto pdev = getHandle();

	switch (request->getType()) {

		case USBDRequestType::clase:
		case USBDRequestType::vendor:
		case USBDRequestType::standard:

			switch (pdev->dev_state) {

				case USBD_STATE_DEFAULT:
				case USBD_STATE_ADDRESSED:
				case USBD_STATE_CONFIGURED: {

					auto iface = LOBYTE(request->index);
					auto cls = getClassFromInterface(iface);
					if (cls != nullptr) {
						ok = cls->classSetup(request) == USBD_OK;
						if ((request->length == 0) && (ok))
							ctlSendStatus();
					}
					break;
				}
			}
			break;
	}

	if (!ok)
		ctlError(request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'endPoint'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest(
	USBD_SetupReqTypedef *request) {

	auto ok = false;
	USBD_EndpointTypeDef *pep;
	uint8_t idx;
	USBD_StatusTypeDef ret = USBD_OK;

	// Provisional per proves
    auto pdev = getHandle();

	auto epAddr = EpAddr(LOBYTE(request->index));

	switch (request->getType()) {

		case USBDRequestType::clase:
		case USBDRequestType::vendor: {
			auto cls = getClassFromEndPoint(epAddr);
			if (cls != nullptr)
				ok = cls->classSetup(request) == USBD_OK;
			break;
		}

		case USBDRequestType::standard:
			switch (request->getRequestID()) {

				case USBDRequestID::setFeature:
					ok = processEndPointRequest_SetFeature(request);
					break;

				case USBDRequestID::clearFeature:
					ok = processEndPointRequest_ClearFeature(request);
					break;

				case USBDRequestID::getStatus:
					switch (pdev->dev_state) {
						case USBD_STATE_ADDRESSED:
							if ((epAddr != 0x00U) && (epAddr != 0x80U)) {
								ctlError(request);
								break;
							}
							pep = ((epAddr & 0x80U) == 0x80U) ? &pdev->ep_in[epAddr & 0x7FU] : &pdev->ep_out[epAddr & 0x7FU];
							pep->status = 0x0000U;

							ctlSendData((uint8_t *)&pep->status, 2U);
							break;

						case USBD_STATE_CONFIGURED:
							if ((epAddr & 0x80U) == 0x80U) {
								if (pdev->ep_in[epAddr & 0xFU].is_used == 0U) {
									ctlError(request);
									break;
								}
							}
							else {
								if (pdev->ep_out[epAddr & 0xFU].is_used == 0U) {
									ctlError(request);
									break;
								}
							}

							pep = ((epAddr & 0x80U) == 0x80U) ? &pdev->ep_in[epAddr & 0x7FU] : &pdev->ep_out[epAddr & 0x7FU];
							if ((epAddr == 0x00U) || (epAddr == 0x80U)) {
								pep->status = 0x0000U;
							}
							else if (USBD_LL_IsStallEP(pdev, epAddr) != 0U) {
								pep->status = 0x0001U;
							}
							else {
								pep->status = 0x0000U;
							}

							ctlSendData((uint8_t *)&pep->status, 2U);
							break;

						default:
							ctlError(request);
							break;
					}
					break;

				default:
					ctlError(request);
					break;
			}
			break;

		default:
			ctlError(request);
			break;
	}

	return ret == USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'sertFeature'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest_SetFeature(
	USBD_SetupReqTypedef *request) {

    auto ok = false;
    auto pdev = getHandle();
	auto epAddr = EpAddr(LOBYTE(request->index));

	switch (pdev->dev_state) {
		case USBD_STATE_ADDRESSED:
			if ((epAddr != 0x00) && (epAddr != 0x80)) {
				USBD_LL_StallEP(pdev, epAddr);
				USBD_LL_StallEP(pdev, 0x80);
				ok = true;
			}
			break;

		case USBD_STATE_CONFIGURED:
			if (request->value == USB_FEATURE_EP_HALT) {
				if ((epAddr != 0x00) && (epAddr != 0x80) && (request->length == 0))
					USBD_LL_StallEP(pdev, epAddr);
			}
			ctlSendStatus();
			ok = true;
			break;
	}

	if (!ok)
		ctlError(request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'clearFeature'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest_ClearFeature(
	USBD_SetupReqTypedef *request) {

	auto ok = false;
	auto pdev = getHandle();
	auto epAddr = EpAddr(LOBYTE(request->index));

	switch (pdev->dev_state) {
		case USBD_STATE_ADDRESSED:
			if ((epAddr != 0x00) && (epAddr != 0x80)) {
				USBD_LL_StallEP(pdev, epAddr);
				USBD_LL_StallEP(pdev, 0x80);
				ok = true;
			}
			break;

		case USBD_STATE_CONFIGURED:
			if (request->value == USB_FEATURE_EP_HALT) {
				if ((epAddr & 0x7F) != 0x00)
					USBD_LL_ClearStallEP(pdev, epAddr);
				ctlSendStatus();
				auto cls = getClassFromEndPoint(epAddr);
				if (cls != nullptr)
					ok = cls->classSetup(request) == USBD_OK;
			}
			break;

		default:
			break;
	}

	if (!ok)
		ctlError(request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'getStatus'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest_GetStatus(
	USBD_SetupReqTypedef *request) {

	auto ok = false;

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descriptor del dispositiu.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Longitut de les dades transferides al buffer
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::getDeviceDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

	auto ptr = buffer;
	auto ptrEnd = buffer + bufferSize;

	if (ptr + sizeof(USBD_DeviceDescriptor) > ptrEnd)
		return false;
	auto descriptor = (USBD_DeviceDescriptor*) ptr;
	descriptor->bLength = sizeof(USBD_DeviceDescriptor);
	descriptor->bDescriptorType = (uint8_t) DescriptorType::device;
	descriptor->bcdUSB = bcdUSB;
	descriptor->bDeviceClass = (uint8_t) ClassID::miscelaneous;
	descriptor->bDeviceSubClass = 0x02; // Common class
	descriptor->bDeviceProtocol = 0x01; // IAD protocol
	descriptor->bMaxPacketSize = _maxEp0Size;
	descriptor->idVendor = _vendorID;
	descriptor->idProduct = _productID;
	descriptor->bcdDevice = 0x0100;
	descriptor->iManufacturer = _manufacturerStr == nullptr ? 0 : USBD_IDX_MFC_STR;
	descriptor->iProduct = _productStr == nullptr ? 0 : USBD_IDX_PRODUCT_STR;
	descriptor->iSerialNumber = _serialNumberStr == nullptr ? 0 : USBD_IDX_SERIAL_STR;
	descriptor->bMaxConfigurations = 1;
	ptr += sizeof(USBD_DeviceDescriptor);

	length = ptr - buffer;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descriptor del dispositiu.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \param    length: Longitut de les dades transferides al buffer.
/// \return   True si tot es correcte.
/// \remarks  El descriptor utilitza sembre IAD
///
bool USBDeviceDriver::getDeviceQualifierDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

	auto ptr = buffer;
	auto ptrEnd = buffer + bufferSize;

	if (ptr + sizeof(USBD_DeviceQualifierDescriptor) > ptrEnd)
		return false;
	auto descriptor = (USBD_DeviceQualifierDescriptor*) ptr;
	descriptor->bLength = sizeof(USBD_DeviceQualifierDescriptor);
	descriptor->bDescriptorType = (uint8_t) DescriptorType::deviceQualifier;
	descriptor->bcdUSB = bcdUSB;
	descriptor->bDeviceClass = (uint8_t) ClassID::miscelaneous;
	descriptor->bDeviceSubClass = 0x02; // Common class
	descriptor->bDeviceProtocol = 0x01; // IAD protocol
	descriptor->bMaxPacketSize0 = _maxEp0Size;
	descriptor->bNumConfigurations = 1;
	descriptor->bReserved = 0;
	ptr += sizeof(USBD_DeviceQualifierDescriptor);

	length = ptr - buffer;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descriptor de configuracio. El genera combinant totes
///           les clases que suporta el driver
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Longitutu de les dades transferides al buffer
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::getConfigurationDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length,
	bool hs) const {

	uint8_t *ptr;
	uint8_t *ptrEnd;

	ptr = buffer;
	ptrEnd = buffer + bufferSize;

	// Configuration descriptor
	//
	if (ptr + sizeof(USBD_ConfigurationDescriptor) > ptrEnd)
		return false;
	auto descriptor = (USBD_ConfigurationDescriptor*) ptr;
	descriptor->bLength = sizeof(USBD_ConfigurationDescriptor);
	descriptor->bDescriptorType = (uint8_t) DescriptorType::configuration;
	descriptor->wTotalLength = sizeof(USBD_ConfigurationDescriptor);
	descriptor->iConfiguration = 0;
	descriptor->bConfigurationValue = 1;
	descriptor->iConfiguration = 0;
	descriptor->bmAttributes = 0xC0;
	descriptor->bMaxPower = _maxPower;
	ptr += sizeof(USBD_ConfigurationDescriptor);

	// Interface descriptors
	//
	for (auto cls: _classes) {
		auto ifaceLength = cls->classGetInterfaceDescriptors(ptr, ptrEnd - ptr, hs);
		if (ifaceLength == 0)
			return false;
		descriptor->wTotalLength += ifaceLength;
		ptr += ifaceLength;
	}

	// Conta i renumera els interfaces
	//
	ptr =  buffer;
	ptrEnd = buffer + descriptor->wTotalLength;

	uint8_t ifaceNumber = 0;
	while (ptr < ptrEnd) {
		auto header = (USBD_DescriptorHeader*) ptr;
		if ((header->bLength == sizeof(USBD_InterfaceDescriptor)) &&
			(header->bDescriptorType == (uint8_t) DescriptorType::interface)) {

			auto ifaceDescriptor = (USBD_InterfaceDescriptor*) header;
			ifaceDescriptor->bInterfaceNumber = ifaceNumber++;
		}
		else if ((header->bLength == sizeof(USBD_InterfaceAssociationDescriptor)) &&
			(header->bDescriptorType == (uint8_t) DescriptorType::interfaceAssociation)) {

			auto ifaceAssociationDescriptor = (USBD_InterfaceAssociationDescriptor*) header;
			ifaceAssociationDescriptor->bFirstInterface = ifaceNumber;
		}
		ptr += header->bLength;
	}
	descriptor->bNumInterfaces = ifaceNumber;

	length = descriptor->wTotalLength;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descriptor de llenguatge
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Longitut de les dades transferides al buffer
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::getLangIDStrDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

	constexpr unsigned maxLanguages = 1;

	auto size = sizeof(USBD_LangIDDescriptorHeader) + ((sizeof(uint16_t) * (maxLanguages - 1)));

	auto ptr = buffer;
	auto ptrEnd = buffer + bufferSize;

	if (ptr + size > ptrEnd)
		return false;
	auto descriptor = (USBD_LangIDDescriptorHeader*) ptr;
	descriptor->bLength = size;
	descriptor->bDescriptorType = (uint8_t) DescriptorType::string;
	descriptor->wLangID[0] = _languageID;
	ptr += size;

	length = ptr - buffer;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string del nom del fabricant.
/// \param    data: Punter al descriptor.
/// \param    length: Longitut del descriptor.
/// \return   Trus si tot es correcte.
///
bool USBDeviceDriver::getManufacturerStrDescriptor(
	uint8_t* &data,
	unsigned &length) const {

    return getStringDescriptor(_manufacturerStr, data, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string del nom del producte.
/// \param    data: Punter al descriptor.
/// \param    length: Longitut del descriptor.
/// \return   Trus si tot es correcte.
///
bool USBDeviceDriver::getProductStrDescriptor(
	uint8_t* &data,
	unsigned &length) const {

    return getStringDescriptor(_productStr, data, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string del interface.
/// \param    data: Punter al descriptor.
/// \param    length: Longitut del descriptor.
/// \return   Trus si tot es correcte.
///
bool USBDeviceDriver::getInterfaceStrDescriptor(
	uint8_t* &data,
	unsigned &length) const {

    return getStringDescriptor("__interfaceStr__", data, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string de la configuracio.
/// \param    data: Punter al descriptor.
/// \param    length: Longitut del descriptor.
/// \return   Trus si tot es correcte.
///
bool USBDeviceDriver::getConfigurationStrDescriptor(
	uint8_t* &data,
	unsigned &length) const {

    return getStringDescriptor("__default_configuration__", data, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string del numero de serie.
/// \param    data: Punter al descriptor.
/// \param    length: Longitut del descriptor.
/// \return   Trus si tot es correcte.
///
bool USBDeviceDriver::getSerialStrDescriptor(
	uint8_t *&data,
	unsigned &length) const {

	return getStringDescriptor(_serialNumberStr, data, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un descriptor de cadena
/// \param    str: El punter a la string.
/// \param    data: Punter al descriptor.
/// \param    length: La longitut del descriptor.
/// \return   True si tot es correcte.
/// \remarks  Retorna un buffer intern estatic.
///
bool USBDeviceDriver::getStringDescriptor(
	const char *str,
	uint8_t *&data,
	unsigned &length) const {

	if (str == nullptr)
		return false;

	auto size = sizeof(USBD_StringDescriptorHeader) + (sizeof(uint16_t) * ((strlen(str) - 1)));

	auto ptr = __responseData;
	auto ptrEnd = ptr + sizeof(__responseData);

	if (ptr + size > ptrEnd)
		return false;
	auto descriptor = (USBD_StringDescriptorHeader*) ptr;
	descriptor->bLength = size;
	descriptor->bDescriptorType = (uint8_t) DescriptorType::string;
	for (auto i = 0; str[i] != '\0'; i++)
		descriptor->wChar[i] = (uint16_t) str[i];
	ptr += size;

	data = __responseData;
	length = ptr - __responseData;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Respon com a error a una solicitut.
/// \param    request: La soligitut que ha generat l'error.
///
void USBDeviceDriver::ctlError(
	USBD_SetupReqTypedef *request) {

	auto pdev = getHandle();
	USBD_LL_StallEP(pdev, 0x80);
	USBD_LL_StallEP(pdev, 0x00);
}


/// ----------------------------------------------------------------------
/// \brief    Respon a una solicitut amb l'estat.
///
void USBDeviceDriver::ctlSendStatus() {

	USBD_CtlSendStatus(getHandle());
}


/// ----------------------------------------------------------------------
/// \brief    Respon a una solicitut amb dades.
/// \param    data: Les dades.
/// \param    length: La longitut de les dades en bytes.
///
void USBDeviceDriver::ctlSendData(
	uint8_t *data,
	unsigned length) {

	USBD_CtlSendData(getHandle(), data, length);
}
