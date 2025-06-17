#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlGPIO.h"
#include "HTL/STM32/htlClock.h"


using namespace htl;
using namespace htl::clock;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la flash.
//
static void initializeFlash() {

	// Activa prefetch
	//
	auto tmp = FLASH->ACR;
	tmp &= ~FLASH_ACR_PRFTEN;
	tmp |= FLASH_ACR_PRFTEN;
	FLASH->ACR = tmp;
}


static void initializeClock() {

	auto clk = ClockDevice::pInst;

	// Activa el oscilador HSE (8Mhz, obtingut del debugger integrat ST-LINK)
	//
	clk->enableHSE(HSEBypass::enabled);

	// Configura el PLL
	// 		PLL = (HSE / 1) * 16 = 128MHz
	// 		R = PLL / 2 = 64Mhz
	// 		Q = PLL / 2 = 64Mhz
	// 		P = PLL / 2 = 64Mhz
	//
	clk->disablePLL();
	clk->configurePLL(PLLsource::hse, 16, 1, PLLPdivider::div2, PLLQdivider::div2, PLLRdivider::div2);
	clk->enablePLL();

	// Selecciona el PLL com a clock del sistema
	//
	clk->selectSystemClock(SystemClockSource::pllrclk, FlashLatency::fl2);

    // Configura el clock dels bus AHB i APB
    //      HCLK = PLLRCLK / 1 = 64MHz
    //      PCLK = PLLRCLK / 4 = 16MHz
    //
	clk->setAHBPrescaler(AHBPrescaler::div1);
	clk->setAPBPrescaler(APBPrescaler::div4);

	// Desactiva els oscilador no utilitzats
	//
	clk->disableHSI16();

    SystemCoreClock = clk->getClockFrequency(ClockID::hclk);
    eosAssert(SystemCoreClock != 0);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void appInitialize() {

	initializeFlash();
	initializeClock();
}
