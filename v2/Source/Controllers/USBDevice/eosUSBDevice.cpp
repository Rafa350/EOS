#include "eos.h"
#include "Controllers/USBDevice/eosUSBDevice.h"
#include "Controllers/USBDevice/eosUSBDeviceClass.h"

#include "usbd_core.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
USBDevice::USBDevice() :
	_state {State::reset} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void USBDevice::initialize(
	USBD_DescriptorsTypeDef *descriptors) {

	if (_state == State::reset) {

		if (USBD_Init(&_usbd, descriptors, 0) != USBD_StatusTypeDef::USBD_OK)
			return;

		_state = State::ready;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicia les transaccions. Es controla tot per interrupcions.
///
void USBDevice::start() {

	if (_state == State::ready) {

		if (USBD_Start(&_usbd) != USBD_StatusTypeDef::USBD_OK)
			return;

		_state = State::running;
	}
}
