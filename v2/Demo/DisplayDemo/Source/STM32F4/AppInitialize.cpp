#include "eos.h"
#include "hal/halSYS.h"
#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery_sdram.h"


/// ----------------------------------------------------------------------
/// \brief Inicialitza el rellotge del sistema.
///
static void CLKInitialize() {

	RCC_ClkInitTypeDef clkInit;
	RCC_OscInitTypeDef oscInit;

	// Enable Power Control clock
	//
	__HAL_RCC_PWR_CLK_ENABLE();

	// The voltage scaling allows optimizing the power consumption when the device is
	// clocked below the maximum system frequency, to update the voltage scaling value
	// regarding system frequency refer to product datasheet.
	//
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	// Enable HSE Oscillator and activate PLL with HSE as source
	//
	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscInit.HSEState = RCC_HSE_ON;
	oscInit.PLL.PLLState = RCC_PLL_ON;
	oscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	oscInit.PLL.PLLM = 8;
	oscInit.PLL.PLLN = 360;
	oscInit.PLL.PLLP = RCC_PLLP_DIV2;
	oscInit.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&oscInit);

	// Activate the Over-Drive mode
	//
	HAL_PWREx_EnableOverDrive();

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	// clocks dividers
	//
	clkInit.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_5);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la SDRAM
///
static void SDRAMInitialize() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void AppInitialize() {

	halSYSInitialize();
	CLKInitialize();
	SDRAMInitialize();
}
