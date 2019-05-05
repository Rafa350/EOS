#include "eos.h"
#include "Controllers/Usb/eosUSBDevice.h"
#include "Controllers/Usb/STM32/usbd.h"


using namespace eos;


#ifdef USE_USB_DEVICE0
static USBD_HandleTypeDef hUsbDeviceFS;
#endif
#ifdef USE_USB_DEVICE1
static USBD_HandleTypeDef hUsbDeviceHS;
#endif

USBD_HandleTypeDef *hUsbDevices[2] = {
#ifdef USE_USB_DEVICE0
	&hUsbDeviceFS,
#else
	nullptr,
#endif
#ifdef USE_USB_DEVICE1
	&hUsbDeviceHS
#else
	nullptr
#endif
};


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param port: Port USB a inicialitzar.
///
UsbDevice::UsbDevice(
	USBPort port):

	UsbBase(port) {
}


/// ----------------------------------------------------------------------
/// \brief Comprova si esta preparat.
/// \return True si esta preparat, false en cas conmtrari.

bool UsbDevice::isReady() const {

	USBD_HandleTypeDef *handle = hUsbDevices[getPort()];
	return handle->dev_state == USBD_STATE_CONFIGURED;
}


/// ----------------------------------------------------------------------
/// \brief Activa el port USB
///
void UsbDevice::start() {

	onStart();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el port USB
///
void UsbDevice::stop() {

	onStop();
}


/// ----------------------------------------------------------------------
/// \brief procesa les accions del port USB
///
void UsbDevice::process() {

	onProcess();
}


/// ----------------------------------------------------------------------
/// \bried Activa el port USB.
///
void UsbDevice::onStart() {

	USBD_HandleTypeDef *handle = hUsbDevices[getPort()];
	USBD_Start(handle);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el port USB.

void UsbDevice::onStop() {

	USBD_HandleTypeDef *handle = hUsbDevices[getPort()];
	USBD_Stop(handle);
}


/// ----------------------------------------------------------------------
/// \brief Procesa les accions del port USB.
///
void UsbDevice::onProcess() {

}
