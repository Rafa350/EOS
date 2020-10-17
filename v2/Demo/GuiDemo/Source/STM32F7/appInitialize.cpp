#include "eos.h"
#include "eosAssert.h"
#include "hal/halSYS.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_rcc_ex.h"
#include "stm32f7xx_hal_flash_ex.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"


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

	// Configura el rellotge pel I2C-3 del TouchPad
	//
    pclkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_I2C3 | RCC_PERIPHCLK_I2C4;
	pclkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	pclkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	pclkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
	pclkInit.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
	HAL_RCCEx_PeriphCLKConfig(&pclkInit);
}


static void initializeSDRAM() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
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

	__HAL_FREEZE_TIM6_DBGMCU();
}
