#include "eos.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_SSD.h"

#include "stm32746g_discovery_sd.h"


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
	'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer: 8 bytes  */
	'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product     : 16 Bytes */
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'0', '.', '0','1',                      /* Version     : 4 Bytes  */
};

static MSCStorage_SSD *__instance;
volatile uint32_t __writestatus, __readstatus = 0;

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
MSCStorage_SSD::MSCStorage_SSD() {

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


USBD_StorageTypeDef * MSCStorage_SSD::getDescriptor() const {

	return (USBD_StorageTypeDef*) &_callTable;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \return   0 si tot es correcte.
///
int8_t MSCStorage_SSD::init(
	uint8_t lun) {

	BSP_SD_Init();

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la capacitat.
/// \param    block_num: El nombre de blocs.
/// \param    block_size: El tamany de cada block.
/// \return   0 si tot es correcte.
///
int8_t MSCStorage_SSD::getCapacity(
	uint8_t lun,
	uint32_t *block_num,
	uint16_t *block_size) {

	HAL_SD_CardInfoTypeDef info;
	int8_t result = -1;

	if (isCardPresent()) {

	    BSP_SD_GetCardInfo(&info);

	    *block_num = info.LogBlockNbr;
	    *block_size = info.LogBlockSize;
	    result = 0;
	}

	return result;
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

		BSP_SD_WriteBlocks_DMA((uint32_t *)buffer, blkStart, blkCount);

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


extern "C" void BSP_SD_WriteCpltCallback(void) {

	__writestatus = 1;
}


extern "C" void BSP_SD_ReadCpltCallback(void) {

	__readstatus = 1;
}



