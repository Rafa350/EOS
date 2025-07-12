#include "eos.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_SSD.h"

#include "stm32746g_discovery_sd.h"


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
MSCStorage_SSD::MSCStorage_SSD() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \return   0 si tot es correcte.
///
int8_t MSCStorage_SSD::initialize(
	uint8_t lun) {

	BSP_SD_Init();

	return 0;
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
	uint32_t *blkQuantity,
	uint16_t *blkSize) {

	if (isCardPresent()) {

		HAL_SD_CardInfoTypeDef info;
	    BSP_SD_GetCardInfo(&info);

	    *blkQuantity = info.LogBlockNbr;
	    *blkSize = info.LogBlockSize;
	    return 0;
	}

	else
		return -1;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si esta preparat.
/// \param    lun: Dispositiu logic.
/// \return   0 si esta preparat.
///
int8_t MSCStorage_SSD::isReady(
	uint8_t lun) {

	int8_t result = -1;

	if (isCardPresent()) {
		if (_prevStatus < 0) {
			BSP_SD_Init();
			_prevStatus = 0;

	    }
	    if (!isCardBusy())
	    	result = 0;
	}
	else if (_prevStatus == 0)
	    _prevStatus = -1;

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si esta protegit d'escriptura.
/// \param    lun: Dispositiu logic.
/// \return   0 si no ho esta.
///
int8_t MSCStorage_SSD::isWriteProtected(
	uint8_t lun) {

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Lectura de dades.
/// \param    lun: Dispositiu logic.
/// \param    buffer: Buffer de dades.
/// \param    blkStart: Block inicial.
/// \param    blkCount: Nombre de block a lleigir.
/// \return   0 si tot es correcte.
///
int8_t MSCStorage_SSD::read(
	uint8_t lun,
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	int8_t result = -1;
	uint32_t timeout = 100000;

	if (isCardPresent()) {

	    BSP_SD_ReadBlocks_DMA((uint32_t *)buffer, blkStart, blkCount);

	    // Wait for Rx Transfer completion
	    //
	    while (__readstatus == 0)
	    	continue;
	    __readstatus = 0;

	    // Wait until SD card is ready to use for new operation
	    //
	    while (isCardBusy()) {
	    	if (timeout-- == 0)
	    		return result;
	    }
	    result = 0;
	}

	return result;
}


int8_t MSCStorage_SSD::write(
	uint8_t lun,
	uint8_t *buffer,
	uint32_t blkStart,
	uint16_t blkCount) {

	int8_t result = -1;
	uint32_t timeout = 100000;

	if (isCardPresent()) {

		BSP_SD_WriteBlocks_DMA((uint32_t*) buffer, blkStart, blkCount);

		// Wait for Tx Transfer completion
		//
		while (__writestatus == 0)
			continue;
		__writestatus = 0;

		// Wait until SD card is ready to use for new operation
		//
		while (isCardBusy())	{
			if (timeout-- == 0)
				return result;
		}

		result = 0;
	}

	return result;
}


int8_t MSCStorage_SSD::getMaxLun() {

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



