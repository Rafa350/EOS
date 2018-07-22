#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"
#include "Services/eosAppLoop.h"
#include "Controllers/Fat/eosFatFS.h"
#include "HAL/halSYS.h"
#include "HAL/halGPIO.h"

#include "sd_diskio.h"

#include <stdlib.h>
#include <stdio.h>


using namespace eos;


FATFS SDFatFs;  /* File system object for SD card logical drive */
FIL MyFile;     /* File object */
char SDPath[4]; /* SD card logical drive path */
uint8_t workBuffer[_MAX_SS];


static void Error_Handler() {

	while (true)
		continue;
}


static void SDTest() {

	FRESULT res;                                          /* FatFs function common result code */
	uint32_t byteswritten, bytesread;                     /* File write/read counts */
	uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
	uint8_t rtext[100];

	/*##-1- Link the micro SD disk I/O driver ##################################*/
	if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0) {

		/*##-2- Register the file system object to the FatFs module ##############*/
		if (f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)  {
			/* FatFs Initialization Error */
			Error_Handler();
		}
		else {
			/*##-3- Create a FAT file system (format) on the logical drive #########*/
			/* WARNING: Formatting the uSD card will delete all content on the device */
			if (f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, workBuffer, sizeof(workBuffer)) != FR_OK) {
				/* FatFs Format Error */
				Error_Handler();
			}
			else {
				/*##-4- Create and Open a new text file object with write access #####*/
				if (f_open(&MyFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
					/* 'STM32.TXT' file Open for write Error */
					Error_Handler();
				}
				else {
					/*##-5- Write data to the text file ################################*/
					res = f_write(&MyFile, wtext, sizeof(wtext), (UINT*)&byteswritten);

					if ((byteswritten == 0) || (res != FR_OK)) {
						/* 'STM32.TXT' file Write or EOF Error */
						Error_Handler();
					}
					else {
						/*##-6- Close the open text file #################################*/
						f_close(&MyFile);

						/*##-7- Open the text file object with read access ###############*/
						if (f_open(&MyFile, "STM32.TXT", FA_READ) != FR_OK) {
							/* 'STM32.TXT' file Open for read Error */
							Error_Handler();
						}
						else {
							/*##-8- Read data from the text file ###########################*/
							res = f_read(&MyFile, rtext, sizeof(rtext), (UINT*)&bytesread);

							if ((bytesread == 0) || (res != FR_OK)) {
								/* 'STM32.TXT' file Read or EOF Error */
								Error_Handler();
							}
							else {
								/*##-9- Close the open text file #############################*/
								f_close(&MyFile);

								/*##-10- Compare read data with the expected data ############*/
								if ((bytesread != byteswritten)) {
									/* Read data is different from the expected data */
									Error_Handler();
								}

								else {
								}
							}
						}
					}
				}
			}
		}
	}

	/*##-11- Unlink the micro SD disk I/O driver ###############################*/
	FATFS_UnLinkDriver(SDPath);
}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {

	SDTest();
}
