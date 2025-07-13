#include "eos.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_SSD.h"

#include "stm32746g_discovery_sd.h"


#define xUSE_SSD_DMA

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
	'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', // Manufacturer
	'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', // Product
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'0', '.', '0','1',                      // Version
};


volatile uint32_t __writestatus = 0;
volatile uint32_t __readstatus = 0;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MSCStorage_SSD::MSCStorage_SSD():

	_prevStatus {0} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \return   0 si tot es correcte.
///
Result MSCStorage_SSD::initialize() {

	BSP_SD_Init();

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Obte les dades SCSI
/// \return   El punter a les dades.
//
int8_t const * MSCStorage_SSD::getInquiryData() {

	return __inquiryData;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la capacitat.
/// \param    blkQuantity: El nombre de blocs.
/// \param    blkSize: El tamany de cada block.
/// \return   0 si tot es correcte.
///
int8_t MSCStorage_SSD::getCapacity(
	uint8_t lun,
	unsigned &blkQuantity,
	unsigned &blkSize) {

	if (isCardPresent()) {

		HAL_SD_CardInfoTypeDef info;
	    BSP_SD_GetCardInfo(&info);

	    blkQuantity = info.LogBlockNbr;
	    blkSize = info.LogBlockSize;
	    return 0;
	}

	else
		return -1;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si esta preparat.
/// \param    lun: Dispositiu logic.
/// \return   True si esta preparat.
///
bool MSCStorage_SSD::isReady(
	uint8_t lun) {

	bool result = false;

	if (isCardPresent()) {
		if (_prevStatus < 0) {
			BSP_SD_Init();
			_prevStatus = 0;

	    }
	    if (!isCardBusy())
	    	result = true;
	}
	else if (_prevStatus == 0)
	    _prevStatus = -1;

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si esta protegit d'escriptura.
/// \param    lun: Dispositiu logic.
/// \return   True si ho esta.
///
bool MSCStorage_SSD::isWriteProtected(
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
Result MSCStorage_SSD::read(
	uint8_t lun,
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	uint32_t timeout = 100000;

	if (isCardPresent()) {

#ifdef USE_SSD_DMA
	    if (BSP_SD_ReadBlocks_DMA((uint32_t*) buffer, blkStart, blkCount) != MSD_OK)
	    	return -1;

	    // Wait for Rx Transfer completion
	    //
	    while (__readstatus == 0)
	    	__readstatus = 0;
#else
	    if (BSP_SD_ReadBlocks((uint32_t*) buffer, blkStart, blkCount, timeout) != MSD_OK)
	    	return Results::timeout;
#endif
	    // Wait until SD card is ready to use for new operation
	    //
	    while (isCardBusy()) {
	    	if (timeout-- == 0)
	    		return Results::timeout;
	    }

	    return Results::success;
	}
	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Escriptura de dades.
/// \param    lun: Dispositiu logic.
/// \param    buffer: Buffer de dades.
/// \param    blkStart: Block inicial.
/// \param    blkCount: Nombre de block a escriure.
/// \return   El resultat de l'operacio
///
Result MSCStorage_SSD::write(
	uint8_t lun,
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	uint32_t timeout = 100000;

	if (isCardPresent()) {

#ifdef USE_SDD_DMA
		BSP_SD_WriteBlocks_DMA((uint32_t*) buffer, blkStart, blkCount);

		// Wait for Tx Transfer completion
		//
		while (__writestatus == 0)
			continue;
		__writestatus = 0;
#else
		if (BSP_SD_WriteBlocks((uint32_t*) buffer, blkStart, blkCount, timeout) != MSD_OK)
			return Results::timeout;
#endif

		// Wait until SD card is ready to use for new operation
		//
		while (isCardBusy())	{
			if (timeout-- == 0)
				return Results::timeout;
		}

		return Results::success;
	}

	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor lun mes gran suportat.
/// \return   El resultat.
///
unsigned MSCStorage_SSD::getMaxLun() {

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Indica si la SSD esta present.
/// \return   True si esta present, false en cas contrari.
///
bool MSCStorage_SSD::isCardPresent() const {

	return BSP_SD_IsDetected() != SD_NOT_PRESENT;
}


/// ----------------------------------------------------------------------
/// \brief    Indica si la SSD esta ocupada.
/// \return   True si esta ocupada, false en cas contrari.
///
bool MSCStorage_SSD::isCardBusy() const {

	return BSP_SD_GetCardState() != SD_TRANSFER_OK;
}


extern "C" void BSP_SD_WriteCpltCallback(void) {

	__writestatus = 1;
}


extern "C" void BSP_SD_ReadCpltCallback(void) {

	__readstatus = 1;
}



