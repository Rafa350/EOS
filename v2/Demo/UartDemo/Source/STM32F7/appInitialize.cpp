#include "eos.h"
#include "eosAssert.h"
#include "HTL/STM32/htlClock.h"

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"


using namespace htl::clock;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el rellotge del sistems i dels periferics
///
static void initializeClock() {

	auto clk = ClockDevice::pInst;

	clk->enableHSE();

	clk->disablePLL();
	clk->configurePLL(PLLsource::hse, 432, 25, PLLPdivider::div2, PLLQdivider::div9);
	clk->enablePLL();

	clk->selectSystemClock(SystemClockSource::pll, FlashLatency::fl7);

	clk->setAHBPrescaler(AHBPrescaler::div1);
	clk->setAPB1Prescaler(APBPrescaler::div4);
	clk->setAPB2Prescaler(APBPrescaler::div2);

	clk->disableHSI();

	SystemCoreClockUpdate();
	eosAssert(SystemCoreClock == clk->getClockFrequency(ClockID::sysclk));
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la SDRAM
///
static void initializeSDRam() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


/// ----------------------------------------------------------------------
/// \brief    Activa els caches.
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

    HAL_Init();

	initializeClock();
	initializeSDRam();

	__HAL_FREEZE_TIM2_DBGMCU();
	__HAL_FREEZE_TIM3_DBGMCU();
	__HAL_FREEZE_TIM6_DBGMCU();
}
