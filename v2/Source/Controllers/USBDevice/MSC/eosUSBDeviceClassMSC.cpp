#include "eos.h"
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"

#include "usbd_msc.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
///
USBDeviceClassMSC::USBDeviceClassMSC(
	USBDeviceDriver *drvUSBD,
	MSCStorage *storage) :

	USBDeviceClass {drvUSBD},
	_storage {storage} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void USBDeviceClassMSC::initialize() {

	auto handle = _drvUSBD->getHandle();

	USBD_RegisterClass(handle, USBD_MSC_CLASS);
	USBD_MSC_RegisterStorage(handle, _storage->getDescriptor());

	// TODO:
	//handle->pUserData[handle->classId] = storage;
}
