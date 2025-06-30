#include "eos.h"
#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"
#include "Controllers/USBDevice/CDC/ST/st_usbd_cdc.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
/// \param    devUSBD: El dispositiu USB
/// \param    interface: El interface de comunicacio
///
USBDeviceClassCDC::USBDeviceClassCDC(
	USBDeviceDriver *drvUSBD,
	CDCInterface *interface) :

	USBDeviceClass {drvUSBD},
	_interface {interface} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void USBDeviceClassCDC::initialize() {

	auto handle = _drvUSBD->getHandle();

	USBD_RegisterClass(handle, USBD_CDC_CLASS);
	handle->pUserData[handle->classId] = _interface;
}
