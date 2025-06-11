#include "eos.h"
#include "eosAssert.h"
#include "HTL/STM32/htlClock.h"

#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery_sdram.h"


using namespace htl::clock;


/// ----------------------------------------------------------------------
/// \brief Inicialitza el rellotge del sistema.
///
static void initializeCLK() {

    // Enable Power Control clock
	//
	__HAL_RCC_PWR_CLK_ENABLE();

	// The voltage scaling allows optimizing the power consumption when the device is
	// clocked below the maximum system frequency, to update the voltage scaling value
	// regarding system frequency refer to product datasheet.
	//
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	auto clk = ClockDevice::pInst;

	// Activa el oscilador extern
	//
	clk->enableHSE();

	// Configura el PLL
	//
	clk->disablePLL();
	clk->configurePLL(PLLsource::hse, 360, 8, PLLPdivider::div2, PLLQdivider::div7);
	clk->enablePLL();

	HAL_PWREx_EnableOverDrive();

	// Selecciona el rellotge del sistema
	//
	clk->selectSystemClock(SystemClockSource::pll, FlashLatency::fl5);

	// Configura els divisors AHB i APBx
	//
	clk->setAHBPrescaler(AHBPrescaler::div1);
	clk->setAPB1Prescaler(APBPrescaler::div4);
	clk->setAPB2Prescaler(APBPrescaler::div2);

	// Desabilita els osciladors no utilitzats.
	//
	clk->disableHSI();

    SystemCoreClockUpdate();
    eosAssert(SystemCoreClock == clk->getClockFrequency(htl::clock::ClockID::sysclk));
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
