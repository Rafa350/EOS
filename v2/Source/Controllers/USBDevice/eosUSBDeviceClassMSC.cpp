#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceClassMSC.h"

#include "usbd_msc.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
///
USBDeviceClassMSC::USBDeviceClassMSC(
	USBDevice *devUSBD) :

	USBDeviceClass {devUSBD, USBD_MSC_CLASS} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void USBDeviceClassMSC::initialize(
	MSCStorage *storage) {

	auto handle = _devUSBD->getHandle();

	USBD_RegisterClass(handle, _usbdClass);
	USBD_MSC_RegisterStorage(handle, storage->getDescriptor());
}
