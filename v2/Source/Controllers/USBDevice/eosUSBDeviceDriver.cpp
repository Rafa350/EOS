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


bool USBDeviceDriver::getDeviceDescriptor(
	uint8_t* &data,
	unsigned &length) {

	if (_descriptors != nullptr) {
		data = _descriptors->device;
		if (data != nullptr) {
			length = data[0];
			return true;
		}
	}

	return false;
}


bool USBDeviceDriver::getLangIDDescriptor(
	uint8_t* &data,
	unsigned &length) {

	if (_descriptors != nullptr) {
		data = _descriptors->langID;
		if (data != nullptr) {
			length = data[0];
			return true;
		}
	}

	return false;

}
