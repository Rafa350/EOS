#include "eos.h"
#include "hal/halSYS.h"
#include "HTL/htlGPIO.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"


static void initializeCLK() {

	RCC_OscInitTypeDef oscInit;
	RCC_ClkInitTypeDef clkInit;

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
}


static void initializeSDRAM() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


static void enableCache() {

    SCB_EnableICache();
    SCB_EnableDCache();
}


static void initializeGPIO() {

#if defined(HARDWARE_STM32F746G_DISCO) && !defined(USE_DISPLAY)
	auto pinBKE = htl::gpio::PinK3::getHandler();
    pinBKE->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::low, htl::gpio::PinState::clear);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void appInitialize() {

	enableCache();

    halSYSInitialize();

	initializeCLK();
	initializeSDRAM();
	initializeGPIO();

#ifdef EOS_DEBUG
	__HAL_FREEZE_TIM6_DBGMCU();
#endif

}
