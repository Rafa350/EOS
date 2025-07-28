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

	_devClasses.pushFront(devClass);

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

	for (auto cls: _devClasses)
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

	for (auto cls: _devClasses)
		cls->classDeinitialize(_usbd.dev_config);

	_state = State::ready;

	return Results::success;
}


USBD_StatusTypeDef USBDeviceDriver::setClassConfig(
	uint8_t configIdx) {

	auto ok = true;

	for (auto cls: _devClasses) {
		if (cls->classInitialize(configIdx) != USBD_OK)
			ok = false;
	}

	return ok ? USBD_OK : USBD_FAIL;
}


USBD_StatusTypeDef USBDeviceDriver::clearClassConfig(
	uint8_t configIdx) {

	auto ok = true;

	for (auto cls: _devClasses) {
		if (cls->classDeinitialize(configIdx) != USBD_OK)
			ok = false;
	}

	return ok ? USBD_OK : USBD_FAIL;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la clase de dispositiu associat al endpoint
/// \param    epAddr: El endpoint.
/// \return   La classe associada. Null en cas d'error.
///
USBDeviceClass *USBDeviceDriver::getClassFromEndPoint(
	EpAddr epAddr) const {

	for (auto cls: _devClasses)
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

	for (auto cls: _devClasses)
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
		if (cls != nullptr)
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
		if (cls != nullptr)
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
			//return USBD_LL_StallEP(getHandle(), request->requestType & 0x80) == USBD_OK;
			ctlError();
			return false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut dirigides al dispositiu
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest(
	USBD_SetupReqTypedef *request) {

	switch (request->getType()) {
		case USBDRequestType::clase:
		case USBDRequestType::vendor:
			return processDeviceRequestOnClass(request);

		case USBDRequestType::standard:
			switch (request->getRequestID()) {
				case USBDRequestID::clearFeature:
					return processDeviceRequest_ClearFeature(request);

				case USBDRequestID::getConfiguration:
					return  processDeviceRequest_GetConfiguration(request);

				case USBDRequestID::getDescriptor:
					return  processDeviceRequest_GetDescriptor(request);

				case USBDRequestID::getStatus:
					return processDeviceRequest_GetStatus(request);

				case USBDRequestID::setAddress:
					return processDeviceRequest_SetAddress(request);

				case USBDRequestID::setConfiguration:
					return processDeviceRequest_SetConfiguration(request);

				case USBDRequestID::setDescriptor:
					break;

				case USBDRequestID::setFeature:
					return processDeviceRequest_SetFeature(request);
			}
			break;
		break;
	}

	ctlError();
	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut dirigides al dispositiu
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequestOnClass(
	USBD_SetupReqTypedef *request) {

	// TODO:: Revisar
	for (auto cls: _devClasses) {
		if (cls->classSetup(request) == USBD_OK)
			return true;
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'GET_DESCRIPTOR'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_GetDescriptor(
	USBD_SetupReqTypedef *request) {

	auto ok = false;
    auto pdev = getHandle();

    auto buffer = __responseData;
    auto bufferSize = sizeof(__responseData);
    unsigned length;

    // Verifica la solicitut
    //
	if ((request->getRequestID() == USBDRequestID::getDescriptor) &&
		(request->getDirection() == USBDRequestDirection::deviceToHost)) {

		switch (request->getDescriptorType()) {
			case USBDRequestValueDescriptorType::bos:
				break;

			case USBDRequestValueDescriptorType::iad:
				break;

			case USBDRequestValueDescriptorType::interface:
				break;

			case USBDRequestValueDescriptorType::endPoint:
				break;

			case USBDRequestValueDescriptorType::device:
				ok = buildDeviceDescriptor(buffer, bufferSize, length);
				break;

			case USBDRequestValueDescriptorType::deviceQualifier: {
				ok = buildDeviceQualifierDescriptor(buffer, bufferSize, length);
				break;
			}

			case USBDRequestValueDescriptorType::configuration:
				ok = buildConfigurationDescriptor(buffer, bufferSize, length, pdev->dev_speed == USBD_SPEED_HIGH);
				break;

			case USBDRequestValueDescriptorType::otherSpeedConfiguration:
				break;

			case USBDRequestValueDescriptorType::string:
				switch (request->getDescriptorIndex()) {
					case USBD_IDX_LANGID_STR:
						ok = buildLangIDStrDescriptor(buffer, bufferSize, length);
						break;

					case USBD_IDX_CONFIG_STR:
						ok = buildConfigurationStrDescriptor(buffer, bufferSize, length);
						break;

					case USBD_IDX_INTERFACE_STR:
						ok = buildInterfaceStrDescriptor(buffer, bufferSize, length);
						break;

					case USBD_IDX_MFC_STR:
						ok = buildManufacturerStrDescriptor(buffer, bufferSize, length);
						break;

					case USBD_IDX_PRODUCT_STR:
						ok = buildProductStrDescriptor(buffer, bufferSize, length);
						break;

					case USBD_IDX_SERIAL_STR:
						ok = buildSerialStrDescriptor(buffer, bufferSize, length);
						break;
				}
			break;
		}
	}

    if (ok) {
		if (request->length > 0) {
			length = min(length, (unsigned) request->length);
			ctlSendData(buffer, length);
		}
		else
			ctlSendStatus();
    }
    else
    	ctlError();

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'SET_ADDRESS'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetAddress(
	USBD_SetupReqTypedef *request) {

    auto ok = false;

    // Comprova la solicitut
    //
	if ((request->getRequestID() == USBDRequestID::setAddress) &&
		(request->getDirection() == USBDRequestDirection::hostToDevice) &&
		(request->value <= 0x007F) &&
		(request->index == 0) &&
		(request->length == 0)) {

	    auto pdev = getHandle();

	    // Comprova l'estat del dispositiu
		//
	    if (pdev->dev_state != USBD_STATE_CONFIGURED) {

			uint8_t addr = request->value;
	    	pdev->dev_address = addr;

	    	// Primer respon abans de fer el canvi efectiu d'adressa
	    	//
			ctlSendStatus();

			// Canvia l'adressa i ajusta el nou estat del dispositiu
			//
			USBD_LL_SetUSBAddress(pdev, addr);
	    	if (addr != 0)
	    		pdev->dev_state = USBD_STATE_ADDRESSED;
	    	else
	    		pdev->dev_state = USBD_STATE_DEFAULT;

	    	ok = true;
	    }
	}

	// En cas d'error, ho comunica al host
	//
	if (!ok)
		ctlError();

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'CLEAR_FEATURE'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_ClearFeature(
	USBD_SetupReqTypedef *request) {

    auto ok = false;

	if ((request->getRequestID() == USBDRequestID::clearFeature) &&
		(request->getDirection() == USBDRequestDirection::hostToDevice) &&
		(request->length == 0)) {

		auto pdev = getHandle();

		// Comprova l'estat del dispositiu
		//
		if ((pdev->dev_state == USBD_STATE_DEFAULT) ||
			(pdev->dev_state == USBD_STATE_ADDRESSED) ||
			(pdev->dev_state == USBD_STATE_CONFIGURED)) {

			switch (request->value) {
				case USB_FEATURE_REMOTE_WAKEUP:
					pdev->dev_remote_wakeup = 0;
					ok = true;
					break;
			}
		}
	}

    if (ok)
    	ctlSendStatus();
    else
		ctlError();

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'SET_FEATURE'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetFeature(
	USBD_SetupReqTypedef *request) {

    auto ok = false;

	if ((request->getRequestID() == USBDRequestID::setFeature) &&
	    (request->getDirection() == USBDRequestDirection::hostToDevice) &&
		(request->length == 0)) {

		auto pdev = getHandle();

		switch (request->value) {
			case USB_FEATURE_REMOTE_WAKEUP:
				pdev->dev_remote_wakeup = 1;
				ok = true;
				break;

			case USB_FEATURE_TEST_MODE:
				pdev->dev_test_mode = loByte(request->index);
				ok = true;
				break;
		}
	}

    if (ok)
    	ctlSendStatus();
	else
	    ctlError();

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'GET_CONFIGURATION'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_GetConfiguration(
	USBD_SetupReqTypedef *request) {

    bool ok = false;

    // Verifica la solicitut
    //
    if ((request->getRequestID() == USBDRequestID::getConfiguration) &&
       	(request->getDirection() == USBDRequestDirection::deviceToHost) &&
    	(request->value == 0) &&
    	(request->index == 0) &&
    	(request->length == 1)) {

        auto pdev = getHandle();

        switch (pdev->dev_state) {
			case USBD_STATE_DEFAULT:
			case USBD_STATE_ADDRESSED:
				pdev->dev_default_config = 0;
				ctlSendData((uint8_t*) &pdev->dev_default_config, 1);
				ok = true;
				break;

			case USBD_STATE_CONFIGURED:
				ctlSendData((uint8_t*) &pdev->dev_config, 1);
				ok = true;
				break;
		}
	}

    if (!ok)
		ctlError();

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'SET_CONFIGURATION'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_SetConfiguration(
	USBD_SetupReqTypedef *request) {

    bool ok = false;

    // Verifica la sol·licitut
    //
	if ((request->getRequestID() == USBDRequestID::setConfiguration) &&
		(request->getDirection() == USBDRequestDirection::hostToDevice) &&
		(loByte(request->value) <= USBD_MAX_NUM_CONFIGURATION) &&
		(request->index == 0) &&
		(request->length == 0)) {

		auto pdev = getHandle();

		static uint8_t cfgidx = loByte(request->value);

		switch (pdev->dev_state) {
			case USBD_STATE_ADDRESSED:
				if (cfgidx != 0) {

					pdev->dev_config = cfgidx;
					ok = setClassConfig(cfgidx) == USBD_OK;
					if (!ok) {
						ctlError();
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
						ctlError();
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
				ctlError();
				USBD_ClrClassConfig(pdev, cfgidx);
				break;
		}
	}
	else
		ctlError();

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'GET_STATUS'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processDeviceRequest_GetStatus(
	USBD_SetupReqTypedef *request) {

    bool ok = false;

    // Verifica la sol·licitut
    //
    if ((request->getRequestID() == USBDRequestID::getStatus) &&
       	(request->getDirection() == USBDRequestDirection::deviceToHost) &&
    	(request->value == 0) &&
    	(request->length == 2)) {

        auto pdev = getHandle();

        if ((pdev->dev_state == USBD_STATE_DEFAULT) ||
			(pdev->dev_state == USBD_STATE_ADDRESSED) ||
			(pdev->dev_state == USBD_STATE_CONFIGURED)) {

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
		}
    }

    if (!ok)
	   ctlError();

    return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut dirigides al interficie
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processInterfaceRequest(
	USBD_SetupReqTypedef *request) {

	switch (request->getType()) {
		case USBDRequestType::clase:
		case USBDRequestType::vendor:
			return processInterfaceRequestOnClass(request);

		case USBDRequestType::standard:
			switch (request->getRequestID()) {
				case USBDRequestID::getStatus:
					return processInterfaceRequest_GetStatus(request);

				default:
					return processInterfaceRequestOnClass(request);
			}
			break;
	}

	ctlError();
	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut dirigides al interficie
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processInterfaceRequestOnClass(
	USBD_SetupReqTypedef *request) {

	auto iface = request->getInterfaceNumber();
	auto cls = getClassFromInterface(iface);
	if (cls != nullptr)
		return cls->processInterfaceRequest(request);

	ctlError();
	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'GET_STATUS'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processInterfaceRequest_GetStatus(
	USBD_SetupReqTypedef *request) {

    if ((request->getRequestID() == USBDRequestID::getStatus) &&
       	(request->getDirection() == USBDRequestDirection::deviceToHost) &&
    	(request->length == 2)) {

    	const uint16_t status = 0;
	    ctlSendData((uint8_t*) &status, 2);
    }

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'endPoint'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest(
	USBD_SetupReqTypedef *request) {

	switch (request->getType()) {
		case USBDRequestType::clase:
		case USBDRequestType::vendor:
			return processEndPointRequestOnClass(request);

		case USBDRequestType::standard:
			switch (request->getRequestID()) {
				case USBDRequestID::setFeature:
					return processEndPointRequest_SetFeature(request);

				case USBDRequestID::clearFeature:
					return processEndPointRequest_ClearFeature(request);

				case USBDRequestID::getStatus:
					return processEndPointRequest_GetStatus(request);

				case USBDRequestID::synchFrame:
					break;
			}
			break;
	}

	ctlError();
	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'endPoint'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequestOnClass(
	USBD_SetupReqTypedef *request) {

	auto epAddr = EpAddr(request->getEndPointNumber());
	auto cls = getClassFromEndPoint(epAddr);
	if (cls != nullptr)
		return cls->classSetup(request) == USBD_OK;

	ctlError();
	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'SET_FEATURE'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest_SetFeature(
	USBD_SetupReqTypedef *request) {

	auto ok = false;

	// Verifica la sol·licitut
	//
	if ((request->getRequestID() == USBDRequestID::setFeature) &&
		(request->getDirection() == USBDRequestDirection::hostToDevice) &&
		(request->length == 0)) {

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
	}

	if (!ok)
		ctlError();

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'CLEAR_FEATURE'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest_ClearFeature(
	USBD_SetupReqTypedef *request) {

	auto ok = false;

	// Verifica la solicitut
	//
	if ((request->getRequestID() == USBDRequestID::clearFeature) &&
		(request->getDirection() == USBDRequestDirection::hostToDevice) &&
		(request->length == 0)) {

		auto pdev = getHandle();
		auto epAddr = EpAddr(request->getEndPointNumber());

		switch (pdev->dev_state) {
			case USBD_STATE_ADDRESSED:
				if (!epAddr.isEP0()) {
					USBD_LL_StallEP(pdev, epAddr);
					USBD_LL_StallEP(pdev, 0x80);
					ok = true;
				}
				else
					ctlError();
				break;

			case USBD_STATE_CONFIGURED:
				if (request->value == USB_FEATURE_EP_HALT) {
					if (epAddr.isEP0())
						USBD_LL_ClearStallEP(pdev, epAddr);
					ctlSendStatus();
					auto cls = getClassFromEndPoint(epAddr);
					if (cls != nullptr)
						ok = cls->classSetup(request) == USBD_OK;
				}
				else
					ctlError();
				break;

			default:
				ctlError();
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'GET_STATUS'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processEndPointRequest_GetStatus(
	USBD_SetupReqTypedef *request) {

	auto ok = false;

	if ((request->getRequestID() == USBDRequestID::getStatus) &&
		(request->getDirection() == USBDRequestDirection::deviceToHost) &&
		(request->length == 2)) {

		auto pdev = getHandle();
		auto epAddr = EpAddr(request->getEndPointNumber());
		auto pep = epAddr.isIN() ? &pdev->ep_in[epAddr & 0x7F] : &pdev->ep_out[epAddr & 0x7F];

		switch (pdev->dev_state) {
			case USBD_STATE_ADDRESSED:
				if (epAddr.isEP0()) {
					pep->status = 0;
					ok = true;
				}
				break;

			case USBD_STATE_CONFIGURED:
				if (pep->is_used == 1) {
					if (epAddr.isEP0())
						pep->status = 0;
					else if (USBD_LL_IsStallEP(pdev, epAddr) != 0)
						pep->status = 1;
					else
						pep->status = 0;
					ok = true;
				}
				break;
		}

		if (ok) {
			uint16_t status = pep->status;
			ctlSendData((uint8_t*) &status, 2);
		}
	}

	if (!ok)
		ctlError();

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descriptor del dispositiu.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Longitut de les dades transferides al buffer
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::buildDeviceDescriptor(
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
bool USBDeviceDriver::buildDeviceQualifierDescriptor(
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
///           les clases que suporta el driver. Per unificar tant dispositius
///           simples com combinats, s'utilitza el descriptor IAD en totes
///           les classes de dispositiu, encara que nomes tinguin una
///           sola interficie.
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Longitutu de les dades transferides al buffer
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::buildConfigurationDescriptor(
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
	unsigned ifaceLength;
	for (auto cls: _devClasses) {
		if (!cls->buildInterfaceDescriptors(ptr, ptrEnd - ptr, hs, ifaceLength))
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
bool USBDeviceDriver::buildLangIDStrDescriptor(
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
/// \param    buffer: Buffer de dades
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Tamany de les dades transferides al buffer.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::buildManufacturerStrDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

    return buildStringDescriptor(_manufacturerStr, buffer, bufferSize, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string del nom del producte.
/// \param    buffer: Buffer de dades
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Tamany de les dades transferides al buffer.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::buildProductStrDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

    return buildStringDescriptor(_productStr, buffer, bufferSize, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string del interface.
/// \param    buffer: Buffer de dades
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Tamany de les dades transferides al buffer.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::buildInterfaceStrDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

    return buildStringDescriptor("__interfaceStr__", buffer, bufferSize, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string de la configuracio.
/// \param    buffer: Buffer de dades
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Tamany de les dades transferides al buffer.
/// \return   True si tot es correcte.

///
bool USBDeviceDriver::buildConfigurationStrDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

    return buildStringDescriptor("__default_configuration__", buffer, bufferSize, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el discriptor de la string del numero de serie.
/// \param    buffer: Buffer de dades
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Tamany de les dades transferides al buffer.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::buildSerialStrDescriptor(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) const {

	return buildStringDescriptor(_serialNumberStr, buffer, bufferSize, length);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un descriptor de cadena
/// \param    str: El punter a la string.
/// \param    buffer: Buffer de dades
/// \param    bufferSize: Tamany del buffer de dades.
/// \param    length: Tamany de les dades transferides al buffer.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::buildStringDescriptor(
	const char *str,
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned &length) {

	if (str == nullptr)
		return false;

	auto ptr = buffer;
	auto ptrEnd = buffer + bufferSize;

	auto size = sizeof(USBD_StringDescriptorHeader) + (sizeof(uint16_t) * ((strlen(str) - 1)));

	if (ptr + size > ptrEnd)
		return false;
	auto descriptor = (USBD_StringDescriptorHeader*) ptr;
	descriptor->bLength = size;
	descriptor->bDescriptorType = (uint8_t) DescriptorType::string;
	for (auto i = 0; str[i] != '\0'; i++)
		descriptor->wChar[i] = (uint16_t) str[i];
	ptr += size;

	length = ptr - buffer;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Respon a una solicitut erronia.
///
void USBDeviceDriver::ctlError() {

	auto pdev = getHandle();
	USBD_LL_StallEP(pdev, 0x80);
	USBD_LL_StallEP(pdev, 0x00);
}


/// ----------------------------------------------------------------------
/// \brief    Respon a una solicitut sense retornar dades.
///
void USBDeviceDriver::ctlSendStatus() {

	USBD_CtlSendStatus(getHandle());
}


/// ----------------------------------------------------------------------
/// \brief    Respon a una solicitut amb retorn de dades.
/// \param    data: Les dades.
/// \param    length: La longitut de les dades en bytes.
///
void USBDeviceDriver::ctlSendData(
	uint8_t *data,
	unsigned length) {

	USBD_CtlSendData(getHandle(), data, length);
}


/// ----------------------------------------------------------------------
/// \brief    Continua amb el retorn de dades d'una solicitut.
/// \param    data: Les dades.
/// \param    length: La longitut de les dades en bytes.
///
void USBDeviceDriver::ctlContinueSendData(
    uint8_t *data,
	unsigned length) {

	USBD_LL_Transmit(getHandle(), 0x00, data, length);
}
