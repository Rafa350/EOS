#include "eos.h"
#include "hal/halSYS.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"


static void initializeCLK() {

	RCC_OscInitTypeDef oscInit;
	RCC_ClkInitTypeDef clkInit;
    RCC_PeriphCLKInitTypeDef pclkInit;

	// Enable HSE Oscillator and activate PLL with HSE as source
    //
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

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	// clocks dividers
	//
	clkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_7);

	// Configura el rellotge pel periferic LTDC
	// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
	// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
	// LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz
	//
	pclkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	pclkInit.PLLSAI.PLLSAIN = 192;
	pclkInit.PLLSAI.PLLSAIR = DISPLAY_CLK_FDIV;
	pclkInit.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	HAL_RCCEx_PeriphCLKConfig(&pclkInit);}


static void initializeSDRAM() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


static void enableCache() {

    SCB_EnableICache();
    SCB_EnableDCache();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void appInitialize() {

	enableCache();

    halSYSInitialize();

	initializeCLK();
	initializeSDRAM();

#ifdef EOS_DEBUG
	__HAL_FREEZE_TIM6_DBGMCU();
#endif

}
