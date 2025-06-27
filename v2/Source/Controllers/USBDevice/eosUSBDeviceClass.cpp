#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceClass.h"

#include "usbd_core.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUSBD: El dispositiu USB
/// \param    usbdClass: El descriptor de la clase de dispositiu.
///
USBDeviceClass::USBDeviceClass(
	USBDevice *devUSBD,
	USBD_ClassTypeDef *usbdClass):

	_devUSBD {devUSBD},
	_usbdClass {usbdClass} {
}
