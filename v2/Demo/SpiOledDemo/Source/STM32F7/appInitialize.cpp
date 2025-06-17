#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlGPIO.h"
#include "HTL/STM32/htlClock.h"

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"


using namespace htl;


static void initializeCLK() {

	auto clk = clock::ClockDevice::pInst;

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

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	// clocks dividers
	//
	RCC_ClkInitTypeDef clkInit;
	clkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_7);

	auto fhclk = clk->getClockFrequency(clock::ClockID::hclk);
	eosAssert(fhclk == 216000000);
	auto fpclk1 = clk->getClockFrequency(clock::ClockID::pclk1);
	eosAssert(fpclk1 == 54000000);
	auto fpclk2 = clk->getClockFrequency(clock::ClockID::pclk2);
	eosAssert(fpclk2 == 108000000);
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
	auto pinK3 = gpio::PinK3::pInst;
    pinK3->initOutput(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::medium, false);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void appInitialize() {

	enableCache();

	HAL_Init();

	initializeCLK();
	initializeSDRAM();
	initializeGPIO();

#ifdef EOS_DEBUG
	__HAL_FREEZE_TIM6_DBGMCU();
#endif

}
