#include "eos.h"
#include "Controllers/USBDevice/eosMSCStorage_RAM.h"


using namespace eos;


static int8_t __inquiryData[] = {
	/* LUN 0 */
	0x00,
	(int8_t) 0x80,
	0x02,
	0x02,
	(STANDARD_INQUIRY_DATA_LEN - 5),
	0x00,
	0x00,
	0x00,
	'E', 'O', 'S', ' ', ' ', ' ', ' ', ' ',      // Manufacturer: 8 bytes
	'R', 'A', 'M', '-', 'D', 'i', 's', 'k',      // Product     : 16 Bytes
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'0', '.', '1','0',                           // Version     : 4 Bytes
};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MSCStorage_RAM::MSCStorage_RAM(
	uint8_t *storage,
	unsigned storageSize) :

	_storage {storage},
	_storageSize {storageSize} {

	_callTable.GetCapacity = getCapacity;
	_callTable.GetMaxLun = getMaxLun;
	_callTable.Init = init;
	_callTable.IsReady = isReady;
	_callTable.IsWriteProtected = isWriteProtected;
	_callTable.Read = read;
	_callTable.Write = write;
	_callTable.pInquiry = __inquiryData;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descriptor.
///
USBD_StorageTypeDef* MSCStorage_RAM::getDescriptor() const {

	return (USBD_StorageTypeDef*) &_callTable;
}


int8_t MSCStorage_RAM::init(
	uint8_t lun) {

	return 0;
}


int8_t MSCStorage_RAM::getCapacity(
	uint8_t lun,
	uint32_t *block_num,
	uint16_t *block_size) {

	*block_size = 1024;
	*block_num = 10;

	return 0;
}


int8_t MSCStorage_RAM::isReady(
	uint8_t lun) {

	return 0;
}


int8_t MSCStorage_RAM::isWriteProtected(
	uint8_t lun) {

	return 0;
}


int8_t MSCStorage_RAM::read(
	uint8_t lun,
	uint8_t *buf,
	uint32_t blk_addr,
	uint16_t blk_len) {

	return 0;
}


int8_t MSCStorage_RAM::write(
	uint8_t lun,
	uint8_t *buf,
	uint32_t blk_addr,
	uint16_t blk_len) {

	return 0;
}


int8_t MSCStorage_RAM::getMaxLun() {

	return 0;
}
