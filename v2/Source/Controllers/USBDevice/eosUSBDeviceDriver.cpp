#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    descriptors: Els descriptors del dispositiu
///
USBDeviceDriver::USBDeviceDriver(
	const USBDeviceDescriptors *descriptors) :
	_descriptors {descriptors},
	_state {State::reset} {
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
Result USBDeviceDriver::initialize(
	USBD_DescriptorsTypeDef *descriptors) {

	if (_state != State::reset)
		return Results::errorState;

	// TODO: Provisional
	_usbd._instance = this;

	if (USBD_Init(&_usbd, descriptors, 0) != USBD_StatusTypeDef::USBD_OK)
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

	while (!_classes.empty()) {
		auto cls = _classes.front();
		cls->classDeinitialize(_usbd.dev_config);
		_classes.remove(cls);
	}

	_state = State::ready;

	return Results::success;
}


USBD_StatusTypeDef USBDeviceDriver::setClassConfig(
	uint8_t cfgidx) {

	USBD_StatusTypeDef ret = USBD_OK;

	for (auto cls: _classes)
		cls->classInitialize(cfgidx);

	return ret;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la clase de dispositiu associat al endPoint
/// \param    epAddr: El endpoint.
/// \return   La classe associada. Null en cas d'error.
///
USBDeviceClass *USBDeviceDriver::getClassFromEndPoint(
	uint8_t epAddr) const {

	for (auto cls: _classes)
		if (cls->usesEndPoint(epAddr))
			return cls;

	return nullptr;
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
		case USBDRequestType::vendor:
			ok = getClass()->classSetup(request) == USBD_OK;
			break;

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
					USBD_CtlError(getHandle(), request);
					break;
			}
			break;

		default:
			USBD_CtlError(getHandle(), request);
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

	// Provisional per proves
    auto pdev = getHandle();

	auto ok = false;

    switch (request->getValueDescriptorType()) {

        case USBDRequestValueDescriptorType::device:
            ok = getDeviceDescriptor(data, length);
            break;

        case USBDRequestValueDescriptorType::configuration: {
        	auto classe = getClass();
        	if (classe != nullptr) {
				if (pdev->dev_speed == USBD_SPEED_HIGH) {
					ok = classe->classGetHSConfigurationDescriptor(data, length);
					if (ok)
						data[1] = USB_DESC_TYPE_CONFIGURATION;
				}
				else {
					ok = classe->classGetFSConfigurationDescriptor(data, length);
					if (ok)
						data[1] = USB_DESC_TYPE_CONFIGURATION;
				}
        	}
        	break;
        }

        case USBDRequestValueDescriptorType::string:
        	switch (request->getValueDescriptorIndex()) {

        		case USBD_IDX_LANGID_STR:
        			ok = getLangIDStrDescriptor(data, length);
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

        		case USBD_IDX_CONFIG_STR:
        			ok = getConfigurationStrDescriptor(data, length);
        			break;

        		case USBD_IDX_INTERFACE_STR:
        			ok = getInterfaceStrDescriptor(data, length);
        			break;
        	}
        	break;

    	case USBDRequestValueDescriptorType::deviceQualifier: {
   			ok = getClass()->classGetDeviceQualifierDescriptor(data, length);
    		break;
    	}

    	case USBDRequestValueDescriptorType::otherSpeedConfiguration: {
			if (pdev->dev_speed == USBD_SPEED_HIGH) {
				ok = getClass()->classGetOtherSpeedConfigurationDescriptor(data, length);
				if (ok)
					data[1] = USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION;
			}
    		break;
    	}
    }

    if (ok) {
		if (request->length != 0) {
			length = min(length, (unsigned) request->length);
			USBD_CtlSendData(pdev, data, length);
		}
		else
			USBD_CtlSendStatus(pdev);
    }
    else
    	USBD_CtlError(pdev, request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'setAddress'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetAddress(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();

    auto ok = false;

	if ((request->index == 0) &&
		(request->length == 0) &&
		(request->value <= 0x007F)) {

		uint8_t addr = request->value;
	    if (pdev->dev_state != USBD_STATE_CONFIGURED) {
	    	pdev->dev_address = addr;
	    	USBD_LL_SetUSBAddress(pdev, addr);
	    	USBD_CtlSendStatus(pdev);
	    	if (addr != 0U)
	    		pdev->dev_state = USBD_STATE_ADDRESSED;
	    	else
	    		pdev->dev_state = USBD_STATE_DEFAULT;
	    	ok = true;
	    }
	}

	if (!ok)
		USBD_CtlError(pdev, request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'clearFeature'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_ClearFeature(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();

    auto ok = false;

    switch (pdev->dev_state) {
		case USBD_STATE_DEFAULT:
		case USBD_STATE_ADDRESSED:
		case USBD_STATE_CONFIGURED:
			if (request->value == USB_FEATURE_REMOTE_WAKEUP) {
				pdev->dev_remote_wakeup = 0;
				USBD_CtlSendStatus(pdev);
			}
			ok = true;
			break;
	}

    if (!ok)
		USBD_CtlError(pdev, request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'setFeature'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetFeature(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();

    auto ok = false;

    if (request->value == USB_FEATURE_REMOTE_WAKEUP) {
	    pdev->dev_remote_wakeup = 1;
	    USBD_CtlSendStatus(pdev);
	    ok = true;
    }
	else if (request->value == USB_FEATURE_TEST_MODE) {
		pdev->dev_test_mode = (uint8_t)(request->index >> 8);
	    USBD_CtlSendStatus(pdev);
	    ok = true;
	}

    if (!ok)
	    USBD_CtlError(pdev, request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'getConfiguration'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_GetConfiguration(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();

    bool ok = false;

    if (request->length == 1) {
		switch (pdev->dev_state) {
			case USBD_STATE_DEFAULT:
			case USBD_STATE_ADDRESSED:
				pdev->dev_default_config = 0U;
				USBD_CtlSendData(pdev, (uint8_t *)&pdev->dev_default_config, 1);
				ok = true;
				break;

			case USBD_STATE_CONFIGURED:
				USBD_CtlSendData(pdev, (uint8_t *)&pdev->dev_config, 1);
				ok = true;
				break;
		}
	}

    if (!ok)
		USBD_CtlError(pdev, request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'setConfiguration'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetConfiguration(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();

    bool ok = false;

	static uint8_t cfgidx;

	cfgidx = (uint8_t)(request->value);

	if (cfgidx > USBD_MAX_NUM_CONFIGURATION) {
		USBD_CtlError(pdev, request);
		return false;
	}

	switch (pdev->dev_state) {
		case USBD_STATE_ADDRESSED:
			if (cfgidx != 0) {

				pdev->dev_config = cfgidx;
				ok = USBD_SetClassConfig(pdev, cfgidx) == USBD_OK;
				if (!ok) {
					USBD_CtlError(pdev, request);
					pdev->dev_state = USBD_STATE_ADDRESSED;
				}
				else {
					USBD_CtlSendStatus(pdev);
					pdev->dev_state = USBD_STATE_CONFIGURED;

#if USBD_USER_REGISTER_CALLBACK == 1
					if (pdev->DevStateCallback != nullptr)
						pdev->DevStateCallback(USBD_STATE_CONFIGURED, cfgidx);
#endif
				}
			}
			else {
				USBD_CtlSendStatus(pdev);
				ok = true;
			}
			break;

		case USBD_STATE_CONFIGURED:
			if (cfgidx == 0) {
				pdev->dev_state = USBD_STATE_ADDRESSED;
				pdev->dev_config = cfgidx;
				USBD_ClrClassConfig(pdev, cfgidx);
				USBD_CtlSendStatus(pdev);
				ok = true;
			}
			else if (cfgidx != pdev->dev_config) {
				/* Clear old configuration */
				USBD_ClrClassConfig(pdev, (uint8_t)pdev->dev_config);

				/* set new configuration */
				pdev->dev_config = cfgidx;

				ok = USBD_SetClassConfig(pdev, cfgidx) == USBD_OK;
				if (!ok) {
					USBD_CtlError(pdev, request);
					USBD_ClrClassConfig(pdev, (uint8_t) pdev->dev_config);
					pdev->dev_state = USBD_STATE_ADDRESSED;
				}
				else
					USBD_CtlSendStatus(pdev);
			}
			else {
				USBD_CtlSendStatus(pdev);
				ok = true;
			}
			break;

		default:
			USBD_CtlError(pdev, request);
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

	// Provisional per proves
    auto pdev = getHandle();

    bool ok = false;

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

	    		USBD_CtlSendData(pdev, (uint8_t*) &pdev->dev_config_status, 2);
	    		ok = true;
	    	}
	    	break;
    }

    if (!ok)
	   USBD_CtlError(pdev, request);

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'interface'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processInterfaceRequest(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();
	bool ok = false;

	switch (request->getType()) {

		case USBDRequestType::clase:
		case USBDRequestType::vendor:
		case USBDRequestType::standard:
			switch (pdev->dev_state) {

				case USBD_STATE_DEFAULT:
				case USBD_STATE_ADDRESSED:
				case USBD_STATE_CONFIGURED:
					if (LOBYTE(request->index) <= USBD_MAX_NUM_INTERFACES) {

						// Get the class index relative to this interface
						//
						auto idx = USBD_CoreFindIF(pdev, LOBYTE(request->index));
						if ((idx != 0xFF) && (idx < USBD_MAX_SUPPORTED_CLASS)) {
							pdev->classId = idx;
							ok = getClass()->classSetup(request) == USBD_OK;
						}
						if ((request->length == 0) && (ok)) {
							USBD_CtlSendStatus(pdev);
						}
					}
					break;
			}
			break;
	}

	if (!ok)
		USBD_CtlError(pdev, request);

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'endPoint'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest(
	USBD_SetupReqTypedef *request) {

	USBD_EndpointTypeDef *pep;
	uint8_t idx;
	USBD_StatusTypeDef ret = USBD_OK;

	// Provisional per proves
    auto pdev = getHandle();

	auto epAddr = LOBYTE(request->index);

	switch (request->getType()) {
		case USBDRequestType::clase:
		case USBDRequestType::vendor:

			/* Get the class index relative to this endpoint */
			idx = USBD_CoreFindEP(pdev, epAddr);

			if (((uint8_t)idx != 0xFF) && (idx < USBD_MAX_SUPPORTED_CLASS)) {
				pdev->classId = idx;
				ret = (USBD_StatusTypeDef)  getClass()->classSetup(request);
			}
			break;

		case USBDRequestType::standard:

			switch (request->getRequestID()) {
				case USBDRequestID::setFeature:
					switch (pdev->dev_state) {
						case USBD_STATE_ADDRESSED:
							if ((epAddr != 0x00) && (epAddr != 0x80)) {
								USBD_LL_StallEP(pdev, epAddr);
								USBD_LL_StallEP(pdev, 0x80U);
							}
							else
								USBD_CtlError(pdev, request);
							break;

						case USBD_STATE_CONFIGURED:
							if (request->value == USB_FEATURE_EP_HALT) {
								if ((epAddr != 0x00U) && (epAddr != 0x80U) && (request->length == 0x00U)) {
									USBD_LL_StallEP(pdev, epAddr);
								}
							}
							USBD_CtlSendStatus(pdev);
							break;

						default:
							USBD_CtlError(pdev, request);
							break;
					}
					break;

				case USBDRequestID::clearFeature:
					switch (pdev->dev_state) {
						case USBD_STATE_ADDRESSED:
							if ((epAddr != 0x00U) && (epAddr != 0x80U)) {
								USBD_LL_StallEP(pdev, epAddr);
								USBD_LL_StallEP(pdev, 0x80U);
							}
							else {
								USBD_CtlError(pdev, request);
							}
							break;

						case USBD_STATE_CONFIGURED:
							if (request->value == USB_FEATURE_EP_HALT) {
								if ((epAddr & 0x7FU) != 0x00U) {
									USBD_LL_ClearStallEP(pdev, epAddr);
								}
								USBD_CtlSendStatus(pdev);

								/* Get the class index relative to this interface */
								idx = USBD_CoreFindEP(pdev, epAddr);
								if (((uint8_t)idx != 0xFFU) && (idx < USBD_MAX_SUPPORTED_CLASS)) {
									pdev->classId = idx;
									/* Call the class data out function to manage the request */
									ret = (USBD_StatusTypeDef)(getClass()->classSetup(request));
								}
							}
							break;

						default:
							USBD_CtlError(pdev, request);
							break;
					}
					break;

				case USBDRequestID::getStatus:
					switch (pdev->dev_state) {
						case USBD_STATE_ADDRESSED:
							if ((epAddr != 0x00U) && (epAddr != 0x80U)) {
								USBD_CtlError(pdev, request);
								break;
							}
							pep = ((epAddr & 0x80U) == 0x80U) ? &pdev->ep_in[epAddr & 0x7FU] : &pdev->ep_out[epAddr & 0x7FU];
							pep->status = 0x0000U;

							USBD_CtlSendData(pdev, (uint8_t *)&pep->status, 2U);
							break;

						case USBD_STATE_CONFIGURED:
							if ((epAddr & 0x80U) == 0x80U) {
								if (pdev->ep_in[epAddr & 0xFU].is_used == 0U) {
									USBD_CtlError(pdev, request);
									break;
								}
							}
							else {
								if (pdev->ep_out[epAddr & 0xFU].is_used == 0U) {
									USBD_CtlError(pdev, request);
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

							USBD_CtlSendData(pdev, (uint8_t *)&pep->status, 2U);
							break;

						default:
							USBD_CtlError(pdev, request);
							break;
					}
					break;

				default:
					USBD_CtlError(pdev, request);
					break;
			}
			break;

		default:
			USBD_CtlError(pdev, request);
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
/// \param    data: Punter al descriptor.
/// \param    length: Longitutu en bytes del descriptor.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::getDeviceDescriptor(
	uint8_t* &data,
	unsigned &length) const {

	if (_descriptors != nullptr) {
		data = _descriptors->device;
		if (data == nullptr)
			length = 0;
		else {
			length = data[0];
			return true;
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descriptor de llenguatge
/// \param    data: Punter al descriptor.
/// \param    length: Longitutu en bytes del descriptor.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::getLangIDStrDescriptor(
	uint8_t* &data,
	unsigned &length) const {

	if (_descriptors != nullptr) {
		data = _descriptors->langID;
		if (data == nullptr)
			length = 0;
		else {
			length = data[0];
			return true;
		}
	}

	return false;
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

    return getStringDescriptor(_descriptors->manufacturer, data, length);
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

    return getStringDescriptor(_descriptors->product, data, length);
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

    return getStringDescriptor(_descriptors->interface, data, length);
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

    return getStringDescriptor(_descriptors->configuration, data, length);
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

	static const char *serial = "FFFFFFFEFFFF";

	return getStringDescriptor(serial, data, length);
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

	static uint8_t buffer[USBD_MAX_STR_DESC_SIZ];

	if (str == nullptr) {

		data = nullptr;
		length = 0;

		return false;
	}

	else {

		data = buffer;
		length = MIN(sizeof(buffer), (strlen(str) * 2) + 2);

		unsigned i = 0;
		buffer[i++] = length;
		buffer[i++] = USB_DESC_TYPE_STRING;
		while (*str != 0) {
			buffer[i++] = *str++;
			buffer[i++] = 0;
		}

		return true;
	}
}
