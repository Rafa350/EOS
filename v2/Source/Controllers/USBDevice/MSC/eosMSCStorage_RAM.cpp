#include "eos.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_RAM.h"


using namespace eos;


static const int8_t __inquiryData[STANDARD_INQUIRY_DATA_LEN] = {
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


Result MSCStorage_RAM::initialize() {

	memset(_storage, 0, _storageSize);

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Obte les dades SCSI
/// \return   El punter a les dades.
//
int8_t const * MSCStorage_RAM::getInquiryData() {

	return __inquiryData;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor lun mes gran suportat.
/// \return   El resultat.
///
unsigned MSCStorage_RAM::getMaxLun() {

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la capacitat.
/// \param    blkQuantity: El nombre de blocs.
/// \param    blkSize: El tamany de cada block.
/// \return   0 si tot es correcte.
///
int8_t MSCStorage_RAM::getCapacity(
	uint8_t lun,
	unsigned &blkQuantity,
	unsigned &blkSize) {

	blkSize = __blockSize;
	blkQuantity = _storageSize / __blockSize;

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si esta preparat.
/// \param    lun: Dispositiu logic.
/// \return   True si esta preparat.
///
bool MSCStorage_RAM::isReady(
	uint8_t lun) {

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si esta protegit d'escriptura.
/// \param    lun: Dispositiu logic.
/// \return   True si ho esta.
///
bool MSCStorage_RAM::isWriteProtected(
	uint8_t lun) {

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Lectura de dades.
/// \param    lun: Dispositiu logic.
/// \param    buffer: Buffer de dades.
/// \param    blkStart: Block inicial.
/// \param    blkCount: Nombre de block a lleigir.
/// \return   El resultat de l'operacio
///
Result MSCStorage_RAM::read(
	uint8_t lun,
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	unsigned len = blkCount * __blockSize;
	uint8_t *ptr = _storage + (blkStart * __blockSize);

	// TODO: Implementar-ho amb DMA
	memcpy(buffer, ptr, len);

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Escriptura de dades.
/// \param    lun: Dispositiu logic.
/// \param    buffer: Buffer de dades.
/// \param    blkStart: Block inicial.
/// \param    blkCount: Nombre de block a escriure.
/// \return   El resultat de l'operacio
///
Result MSCStorage_RAM::write(
	uint8_t lun,
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	unsigned len = blkCount * __blockSize;
	uint8_t *ptr = _storage + (blkStart * __blockSize);

	// TODO: Implementar-ho amb DMA
	memcpy(ptr, buffer, len);

	return Results::success;
}
