#include "eos.h"
#include "Controllers/Usb/eosUSBDevice.h"
#include "usbd_def.h"
#include "usbd_core.h"


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

	port(port) {

	initializePort(port);
}


/// ----------------------------------------------------------------------
/// \brief Activa el port USB
///
void UsbDevice::start() {

	USBD_Start(hUsbDevices[port]);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el port USB
///
void UsbDevice::stop() {

	USBD_Stop(hUsbDevices[port]);
}


/// ----------------------------------------------------------------------
/// \brief procesa les accions del port USB
///
void UsbDevice::process() {

}
