// -----------------------------------------------------------------------
// Basat en els treballs de:
// 		HALL libraries de STMicroelectonics
//      FatFS de ChaN
//		STM32 Libraries de Tilen Majerle
// -----------------------------------------------------------------------

#include "Controllers/Fat/Drivers/SDIO/sd_diskio.h"
#include "stm32746g_discovery_sd.h"
#include <stdbool.h>


extern void *fsGetInstance(void);
extern bool fsInitialize(void *instance);
extern bool fsIsBusy(void *instance);


static volatile DSTATUS status = STA_NOINIT;
static void *fsDriver;

DSTATUS SD_initialize (BYTE);
DSTATUS SD_status (BYTE);
DRESULT SD_read (BYTE, BYTE*, DWORD, UINT);
#if _USE_WRITE == 1
  DRESULT SD_write (BYTE, const BYTE*, DWORD, UINT);
#endif
#if _USE_IOCTL == 1
  DRESULT SD_ioctl (BYTE, BYTE, void*);
#endif

const Diskio_drvTypeDef SD_Driver = {
	SD_initialize,
	SD_status,
	SD_read,
#if _USE_WRITE == 1
	SD_write,
#endif
#if _USE_IOCTL == 1
	SD_ioctl,
#endif
};


/// ----------------------------------------------------------------------
/// /brief Inicialitza un disc
/// /param lun: not used
/// /retval DSTATUS: Operation status
///
DSTATUS SD_initialize(
	BYTE lun) {

	status = STA_NOINIT;

	/*
	fsDriver = fsGetInstance();
	if (fsInitialize(fsDriver))
		status &= ~STA_NOINIT;
	*/

	if (BSP_SD_Init() == MSD_OK)
		status &= ~STA_NOINIT;

	return status;
}


/// ----------------------------------------------------------------------
/// brief Obte l'estat del disc.
/// /param lun: not used
/// /return DSTATUS: Resultat de l'operacio.
///
DSTATUS SD_status(
	BYTE lun) {

	status = STA_NOINIT;

	/*
	if (!fsIsBusy(fsDriver))
		status &= ~STA_NOINIT;
    */

	if (BSP_SD_GetCardState() == MSD_OK)
		status &= ~STA_NOINIT;

	return status;
}


/// ----------------------------------------------------------------------
/// /brief Lectura de sectors del disc.
/// /param lun: not used
/// /param buff: Data buffer to store read data
/// /param sector: Sector address (LBA)
/// /param count: Number of sectors to read (1..128)
/// /return DRESULT: Resultat de l'operacio.
///
DRESULT SD_read(
	BYTE lun,
	BYTE *buff,
	DWORD sector,
	UINT count) {

	DRESULT res = RES_ERROR;

	if (BSP_SD_ReadBlocks((uint32_t*) buff, (uint32_t) sector,
			count, SDMMC_DATATIMEOUT) == MSD_OK) {

		// Wait until the read operation is finished
		//
		while (BSP_SD_GetCardState() != MSD_OK)
			continue;

		res = RES_OK;
	}

	return res;
}


/// ----------------------------------------------------------------------
/// /brief  Writes Sector(s)
/// /param  lun: not used
/// /param  *buff: Data to be written
/// /param  sector: Sector address (LBA)
/// /param  count: Number of sectors to write (1..128)
/// /return DRESULT: Operation result
///
#if _USE_WRITE == 1
DRESULT SD_write(
	BYTE lun,
	const BYTE *buff,
	DWORD sector,
	UINT count) {

	DRESULT res = RES_ERROR;

	if (BSP_SD_WriteBlocks((uint32_t*) buff, (uint32_t) sector,
			count, SDMMC_DATATIMEOUT) == MSD_OK) {

		// Wait until the Write operation is finished
		//
		while (BSP_SD_GetCardState() != MSD_OK)
			continue;

		res = RES_OK;
	}

	return res;
}
#endif


/// ----------------------------------------------------------------------
/// /brief  I/O control operation
/// /param  lun: not used
/// /param  cmd: Control code
/// /param  *buff: Buffer to send/receive control data
/// /return DRESULT: Operation result
///
#if _USE_IOCTL == 1
DRESULT SD_ioctl(
	BYTE lun,
	BYTE cmd,
	void *buff) {

	DRESULT res = RES_ERROR;
	BSP_SD_CardInfo CardInfo;

	if (status & STA_NOINIT)
		return RES_NOTRDY;

	switch (cmd) {

		// Make sure that no pending write process
	    //
		case CTRL_SYNC :
			res = RES_OK;
			break;

		// Get number of sectors on the disk (DWORD)
		//
		case GET_SECTOR_COUNT :
			BSP_SD_GetCardInfo(&CardInfo);
			*(DWORD*)buff = CardInfo.LogBlockNbr;
			res = RES_OK;
			break;

		// Get R/W sector size (WORD)
		//
		case GET_SECTOR_SIZE :
			BSP_SD_GetCardInfo(&CardInfo);
			*(WORD*)buff = CardInfo.LogBlockSize;
			res = RES_OK;
			break;

		// Get erase block size in unit of sector (DWORD)
		//
		case GET_BLOCK_SIZE :
			BSP_SD_GetCardInfo(&CardInfo);
			*(DWORD*)buff = CardInfo.LogBlockSize;
			res = RES_OK;
			break;

		default:
			res = RES_PARERR;
			break;
	}

	return res;
}
#endif

