#include "eos.h"
#include "HAL/halSYS.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_flash_ex.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sd.h"
#include "stm32746g_discovery_sdram.h"


static void initializeCLK() {

	// Enable HSE Oscillator and activate PLL with HSE as source
	//
	RCC_OscInitTypeDef oscInit;
	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscInit.HSEState = RCC_HSE_ON;
	oscInit.HSIState = RCC_HSI_OFF;
	oscInit.PLL.PLLState = RCC_PLL_ON;
	oscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	oscInit.PLL.PLLM = 25;
	oscInit.PLL.PLLN = 432;
	oscInit.PLL.PLLP = RCC_PLLP_DIV2;
	oscInit.PLL.PLLQ = 9;
	HAL_RCC_OscConfig(&oscInit);

	HAL_PWREx_EnableOverDrive();

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	// clocks dividers
	//
	RCC_ClkInitTypeDef clkInit;
	clkInit.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_7);

	// Inicialitza el rellotge del periferic SDMCC
	//
	RCC_PeriphCLKInitTypeDef perClkInit;
	perClkInit.PeriphClockSelection = RCC_PERIPHCLK_SDMMC1 | RCC_PERIPHCLK_CLK48;
	perClkInit.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
	perClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
	HAL_RCCEx_PeriphCLKConfig(&perClkInit);
}


static void initializeSDRAM() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


static void initializeSD() {

	BSP_SD_Init();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void appInitialize() {

    SCB_EnableICache();
    SCB_EnableDCache();

    halSYSInitialize();
	initializeCLK();
	initializeSDRAM();
	initializeSD();
}
