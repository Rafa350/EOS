#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"


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
		cls->classDeinit(_usbd.dev_config);
		_classes.remove(cls);
	}

	_state = State::ready;

	return Results::success;
}


USBD_StatusTypeDef USBDeviceDriver::setClassConfig(
	uint8_t cfgidx) {

	USBD_StatusTypeDef ret = USBD_OK;

	for (auto cls: _classes)
		cls->classInit(cfgidx);

	return ret;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut.
/// \param    request: La solicitut.
/// \return   El resultat de l'operacio.
///
USBD_StatusTypeDef USBDeviceDriver::processRequest(
	USBD_SetupReqTypedef *request) {

	USBD_StatusTypeDef result = USBD_FAIL;

	switch (request->getRecipient()) {

		case USBDRequestRecipient::device:
			result = processDeviceRequest(request);
			break;

		case USBDRequestRecipient::interface:
			//result = USBD_StdItfReq(pdev, &pdev->request);
			break;

		case USBDRequestRecipient::endPoint:
			//result = USBD_StdEPReq(pdev, &pdev->request);
			break;

		default:
			//result = USBD_LL_StallEP(_usbd.pdev, request->requestType & 0x80);
			break;
	}

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut de tipus 'device'
/// \param    request: La solicitut.
/// \return   El resultat de l'operacio.
///
USBD_StatusTypeDef USBDeviceDriver::processDeviceRequest(
	USBD_SetupReqTypedef *request) {

	USBD_StatusTypeDef result = USBD_FAIL;

	switch (request->getType()) {

		case USBDRequestType::clase:
		case USBDRequestType::vendor:
			result = (USBD_StatusTypeDef) _classes.front()->classSetup(request);
			break;

		case USBDRequestType::standard:

			switch (request->getRequestID()) {

				case USBDRequestID::getDescriptor:
					result = processGetDescriptorRequest(request) ? USBD_OK : USBD_FAIL;
					break;

				case USBDRequestID::setAddress:
					//USBD_SetAddress(pdev, req);
					break;

				case USBDRequestID::setConfiguration:
					//ret = USBD_SetConfig(pdev, req);
					break;

				case USBDRequestID::getConfiguration:
					//USBD_GetConfig(pdev, req);
					break;

				case USBDRequestID::getStatus:
					//USBD_GetStatus(pdev, req);
					break;

				case USBDRequestID::setFeature:
					//USBD_SetFeature(pdev, req);
					break;

				case USBDRequestID::clearFeature:
					processClearFeatureRequest(request);
					break;

				default:
					//USBD_CtlError(pdev, req);
					break;
			}
			break;

		default:
			//USBD_CtlError(pdev, req);
			break;
	}

	return result;
}

/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'getDescriptor'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processGetDescriptorRequest(
	USBD_SetupReqTypedef *request) {

	unsigned length = 0;
	uint8_t *data = nullptr;

	// Provisional per proves
    auto pdev = getHandle();
    auto classe = pdev->pClass[0];

	bool result = true;

    switch (request->getValueDescriptorType()) {

        case USBDRequestValueDescriptorType::device:
            result = getDeviceDescriptor(data, length);
            break;

        case USBDRequestValueDescriptorType::configuration:
        	if (pdev->dev_speed == USBD_SPEED_HIGH) {
        		result = classe->classGetHSConfigurationDescriptor(data, length);
        		if (result)
        			data[1] = USB_DESC_TYPE_CONFIGURATION;
        	}
        	else {
        		result = classe->classGetFSConfigurationDescriptor(data, length);
        		if (result)
        			data[1] = USB_DESC_TYPE_CONFIGURATION;
        	}
        	break;


        case USBDRequestValueDescriptorType::string:
        	switch (request->getValueDescriptorIndex()) {

        		case USBD_IDX_LANGID_STR:
        			result = getLangIDStrDescriptor(data, length);
        			break;

        		case USBD_IDX_MFC_STR:
        			result = getManufacturerStrDescriptor(data, length);
        			break;

        		case USBD_IDX_PRODUCT_STR:
        			result = getProductStrDescriptor(data, length);
        			break;

        		case USBD_IDX_SERIAL_STR:
        			result = getSerialStrDescriptor(data, length);
        			break;

        		case USBD_IDX_CONFIG_STR:
        			result = getConfigurationStrDescriptor(data, length);
        			break;

        		case USBD_IDX_INTERFACE_STR:
        			result = getInterfaceStrDescriptor(data, length);
        			break;

        		default:
        			result = false;
          	  	    break;
        	}
        	break;

    	case USBDRequestValueDescriptorType::deviceQualifier:
  			result = classe->classGetDeviceQualifierDescriptor(data, length);
    		break;

    	case USBDRequestValueDescriptorType::otherSpeedConfiguration:
    		if (pdev->dev_speed == USBD_SPEED_HIGH) {
    			result = classe->classGetOtherSpeedConfigurationDescriptor(data, length);
    			if (result)
    				data[1] = USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION;
    		}
    		else
    			result = false;
    		break;

        default:
        	result = false;
        	break;
    }

    // Provisional per proves. es procesa el error en el cridador
    if (result == false)
    	return false;

    if (result) {
		if (request->length != 0) {
			if (length != 0) {
				length = MIN(length, request->length);
				USBD_CtlSendData(pdev, data, length);
			}
			else
				result = false;
		}
		else
			USBD_CtlSendStatus(pdev);
    }

    if (!result)
    	USBD_CtlError(pdev, request);

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'setAddress'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processSetAddressRequest(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();

    bool result = true;

	if ((request->index == 0) &&
		(request->length == 0) &&
		(request->value <= 0x007F)) {

		uint8_t addr = request->value;
	    if (pdev->dev_state == USBD_STATE_CONFIGURED)
	    	result = false;
	    else {
	    	pdev->dev_address = addr;
	    	USBD_LL_SetUSBAddress(pdev, addr);
	    	USBD_CtlSendStatus(pdev);
	    	if (addr != 0U)
	    		pdev->dev_state = USBD_STATE_ADDRESSED;
	    	else
	    		pdev->dev_state = USBD_STATE_DEFAULT;
	    }
	}
	else
		result = false;

	if (!result)
		USBD_CtlError(pdev, request);

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una solicitut 'clearFeature'
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceDriver::processClearFeatureRequest(
	USBD_SetupReqTypedef *request) {

	// Provisional per proves
    auto pdev = getHandle();

    bool result = true;

    switch (pdev->dev_state) {
		case USBD_STATE_DEFAULT:
		case USBD_STATE_ADDRESSED:
		case USBD_STATE_CONFIGURED:
			if (request->value == USB_FEATURE_REMOTE_WAKEUP) {
				pdev->dev_remote_wakeup = 0U;
				USBD_CtlSendStatus(pdev);
			}
			break;

		default:
			result = false;
			break;
	}

    if (!result)
		USBD_CtlError(pdev, request);

    return result;
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
		if (data != nullptr) {
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
		if (data != nullptr) {
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

	if (str == nullptr)
		return false;

    length = MIN(sizeof(buffer), (strlen(str) * 2) + 2);
    data = buffer;

    unsigned i = 0;
    buffer[i++] = length;
    buffer[i++] = USB_DESC_TYPE_STRING;
    while (*str != 0) {
		buffer[i++] = *str++;
		buffer[i++] = 0;
    }

	return true;
}
