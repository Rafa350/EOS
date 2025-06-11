#include "eos.h"
#include "eosAssert.h"
#include "htl/STM32/htlClock.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f429i_discovery_sdram.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief Inicialitza el rellotge del sistema.
///
static void initializeCLK() {

	auto clk = clock::ClockDevice::pInst;

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
	RCC_OscInitTypeDef oscInit;
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
	RCC_ClkInitTypeDef clkInit;
	clkInit.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_5);

	// Inicialitza rellotge del modul LTDC
	// -Configure PLLSAI prescalers for LCD
	// -Enable Pixel Clock
	// -PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// -PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAI_N = 192 Mhz
	// -PLLLCDCLK = PLLSAI_VCO Output/PLLSAI_R = 192/4 = 96 Mhz
	// -LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDivR = 96/4 = 24 Mhz
	//
    RCC_PeriphCLKInitTypeDef pclkInit;
    pclkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    pclkInit.PLLSAI.PLLSAIN = 192;
    pclkInit.PLLSAI.PLLSAIR = 4;
    pclkInit.PLLSAIDivR = RCC_PLLSAIDIVR_8;
    HAL_RCCEx_PeriphCLKConfig(&pclkInit);


    auto fpclk1 = clk->getClockFrequency(clock::ClockID::pclk1);
    eosAssert(fpclk1 <= 108000000);

    auto fpclk2 = clk->getClockFrequency(clock::ClockID::pclk2);
    eosAssert(fpclk2 <= 108000000);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la SDRAM
///
static void initializeSDRAM() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void appInitialize() {

	HAL_Init();

	initializeCLK();
	initializeSDRAM();

#ifdef EOS_DEBUG
	__HAL_FREEZE_TIM6_DBGMCU();
#endif
}
