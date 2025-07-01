#include "eos.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_RAM.h"


using namespace eos;


static const int8_t __inquiryData[] = {
	/* LUN 0 */
	0x00,                              // Qualifier / Device type
	(int8_t) 0x80,                     // RMB
	0x02,                              // Version
	0x02,                              // NORMACA / HISUP / FORMAT
	(STANDARD_INQUIRY_DATA_LEN - 5),   // Additional length
	0x00,
	0x00,
	0x00,
	'E', 'O', 'S', ' ', ' ', ' ', ' ', ' ',      // Manufacturer
	'R', 'A', 'M', '-', 'D', 'i', 's', 'k',      // Product
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'0', '.', '1','0',                           // Version
};


static constexpr unsigned __blockSize = 512;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MSCStorage_RAM::MSCStorage_RAM(
	uint8_t *storage,
	unsigned storageSize) :

	_storage {storage},
	_storageSize {storageSize} {

}


int8_t MSCStorage_RAM::initialize(
	uint8_t lun) {

	memset(_storage, 0, _storageSize);
	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Obte les dades SCSI
/// \return   El punter a les dades.
//
int8_t const * MSCStorage_RAM::getInquiryData() {

	return __inquiryData;
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
