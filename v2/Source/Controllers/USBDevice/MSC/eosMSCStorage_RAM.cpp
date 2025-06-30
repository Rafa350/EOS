#include "eos.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_RAM.h"


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


static MSCStorage_RAM *__instance;
static constexpr unsigned __blockSize = 512;

static int8_t __init(uint8_t lun);
static int8_t __getCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t __isReady(uint8_t lun);
static int8_t __isWriteProtected(uint8_t lun);
static int8_t __read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t __write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t __getMaxLun(void);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MSCStorage_RAM::MSCStorage_RAM(
	uint8_t *storage,
	unsigned storageSize) :

	_storage {storage},
	_storageSize {storageSize} {

	_callTable.GetCapacity = __getCapacity;
	_callTable.GetMaxLun = __getMaxLun;
	_callTable.Init = __init;
	_callTable.IsReady = __isReady;
	_callTable.IsWriteProtected = __isWriteProtected;
	_callTable.Read = __read;
	_callTable.Write = __write;
	_callTable.pInquiry = __inquiryData;

	__instance = this;
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

	*block_size = __blockSize;
	*block_num = _storageSize / __blockSize;
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
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	unsigned len = blkCount * __blockSize;
	uint8_t *ptr = _storage + (blkStart * __blockSize);

	memcpy(buffer, ptr, len);

	return 0;
}


int8_t MSCStorage_RAM::write(
	uint8_t lun,
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	unsigned len = blkCount * __blockSize;
	uint8_t *ptr = _storage + (blkStart * __blockSize);

	memcpy(ptr, buffer, len);

	return 0;
}


int8_t MSCStorage_RAM::getMaxLun() {

	return 0;
}


int8_t __init(
	uint8_t lun) {

	return __instance->init(lun);
}


int8_t __getCapacity(
	uint8_t lun,
	uint32_t *block_num,
	uint16_t *block_size) {

	return __instance->getCapacity(lun, block_num, block_size);
}


int8_t __isReady(
	uint8_t lun) {

	return __instance->isReady(lun);
}


int8_t __isWriteProtected(
	uint8_t lun) {

	return __instance->isWriteProtected(lun);
}


int8_t __read(
	uint8_t lun,
	uint8_t *buf,
	uint32_t blk_addr,
	uint16_t blk_len) {

	return __instance->read(lun, buf, blk_addr, blk_len);
}


int8_t __write(
	uint8_t lun,
	uint8_t *buf,
	uint32_t blk_addr,
	uint16_t blk_len) {

	return __instance->write(lun, buf, blk_addr, blk_len);
}


int8_t __getMaxLun() {

	return __instance->getMaxLun();
}
