#include "eos.h"
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"


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

	USBD_RegisterClass(handle, this);
	handle->pUserData[handle->classId] = _storage;
}


int8_t USBDeviceClassMSC::classInit(
	uint8_t cfgidx) {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classDeinit(
	uint8_t cfgidx) {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classSetup(
	USBD_SetupReqTypedef *req) {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classEP0TxSent() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classEP0RxReady() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classDataIn(
	uint8_t epnum) {

	return USBD_FAIL;

}


int8_t USBDeviceClassMSC::classDataOut(
	uint8_t epnum) {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classSOF() {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classIsoINIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}


int8_t USBDeviceClassMSC::classIsoOUTIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}


uint8_t* USBDeviceClassMSC::classGetHSConfigurationDescriptor(
	uint16_t *length) {

	return 0;
}


uint8_t* USBDeviceClassMSC::classGetFSConfigurationDescriptor(
	uint16_t *length) {

	return 0;
}


uint8_t* USBDeviceClassMSC::classGetOtherSpeedConfigurationDescriptor(
	uint16_t *length) {

	return 0;
}


uint8_t* USBDeviceClassMSC::classGetDeviceQualifierDescriptor(
	uint16_t *length) {

	return 0;
}
