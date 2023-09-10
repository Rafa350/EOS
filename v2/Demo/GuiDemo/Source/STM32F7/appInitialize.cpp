#include "eos.h"
#include "eosAssert.h"
#include "hal/halSYS.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_rcc_ex.h"
#include "stm32f7xx_hal_flash_ex.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"
#include "HTL/STM32/htlLTDC.h"


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els rellotges del sistema i dels periferics.
///
static void initializeCLK() {

	RCC_ClkInitTypeDef clkInit;
	RCC_OscInitTypeDef oscInit;
    RCC_PeriphCLKInitTypeDef pclkInit;

	// Enable HSE Oscillator and activate PLL with HSE as source
	//
	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscInit.HSEState = RCC_HSE_ON;
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
	clkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_7);

	// Configura el rellotge pel periferic I2Cx
	//
    pclkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_I2C3 | RCC_PERIPHCLK_I2C4;
	pclkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	pclkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	pclkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
	pclkInit.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
	HAL_RCCEx_PeriphCLKConfig(&pclkInit);

	// Configura el rellotge pel periferic LTDC
	// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
	// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
	// LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz
	//
#if 1
	pclkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	pclkInit.PLLSAI.PLLSAIN = 192;
	pclkInit.PLLSAI.PLLSAIR = board::display::fdiv;
	pclkInit.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	HAL_RCCEx_PeriphCLKConfig(&pclkInit);
#else
	auto hLTDC = htl::ltdc::LTDDevice::getHandler();
	hLTDC->initClock(192, DISPLAY_CLK_FDIV, htl::LTDCClockDivider::_4);
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la SDRAM
///
static void initializeSDRAM() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita els caches
///
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
