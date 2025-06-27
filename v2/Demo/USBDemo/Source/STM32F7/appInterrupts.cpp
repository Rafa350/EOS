#include "eos.h"
#include "HTL/STM32/htlUART.h"

#include "main.h"


extern "C" void xPortSysTickHandler(void);

extern PCD_HandleTypeDef hpcd;
extern SD_HandleTypeDef uSdHandle;


extern "C" void SysTick_Handler(void) {

	HAL_IncTick();
	xPortSysTickHandler();
}


#ifdef USE_USB_FS
extern "C" void OTG_FS_IRQHandler(void)
#else
extern "C" void OTG_HS_IRQHandler(void)
#endif
{
	HAL_PCD_IRQHandler(&hpcd);
}


extern "C" void BSP_SDMMC_IRQHandler(void) {

	HAL_SD_IRQHandler(&uSdHandle);
}


extern "C" void BSP_SDMMC_DMA_Tx_IRQHandler(void) {

	HAL_DMA_IRQHandler(uSdHandle.hdmatx);
}


extern "C" void BSP_SDMMC_DMA_Rx_IRQHandler(void) {

	HAL_DMA_IRQHandler(uSdHandle.hdmarx);
}
