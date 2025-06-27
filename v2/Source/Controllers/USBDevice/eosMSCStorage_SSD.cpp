#include "eos.h"
#include "Controllers/USBDevice/eosMSCStorage_SSD.h"

#include "usbd_storage.h"


using namespace eos;


USBD_StorageTypeDef * MSCStorage_SSD::getDescriptor() const {

	return &USBD_DISK_fops;
}
