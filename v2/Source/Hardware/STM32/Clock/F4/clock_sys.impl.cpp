module;


#include "hardware.h"


module Eos.Hardware.Clock;


import Eos.Bits;
import Eos.Types;


using namespace eos;
using namespace eos::hardware::clock;


static_assert(Platform::is_STM32_F4);


/// ----------------------------------------------------------------------
/// @brief    Selecciona el rellotge principal del sistema
/// @param    source: El rellotge a seleccionar.
/// @param    fl: Latencia de la memoria FLASH
/// @return   True si tot es correcte, false en cas contrari.
/// @remarks  El posen els prescalers AHB, APB1 i APB2 a la maxima divisio
///
bool ClockDevice::selectSystemClock(
	SystemClockSource source,
	FlashLatency fl) const {

	auto ACR = FLASH->ACR;
	auto CFGR = RCC->CFGR;

	// Si la latencia actual es mes baixa que la indicada, la puja
	//
	if (((ACR & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos) < (UInt32) fl) {
		Bits::clear(ACR, FLASH_ACR_LATENCY);
		Bits::set(ACR, ((UInt32)fl << FLASH_ACR_LATENCY_Pos) & FLASH_ACR_LATENCY_Msk);
		FLASH->ACR = ACR;
	}

	Bits::set(CFGR, 15UL << RCC_CFGR_HPRE_Pos);
	Bits::set(CFGR, 7UL << RCC_CFGR_PPRE1_Pos);
	Bits::set(CFGR, 7UL << RCC_CFGR_PPRE2_Pos);

	Bits::clear(CFGR, RCC_CFGR_SW);
	switch (source) {
		case SystemClockSource::hsi:
			if (!isHSIEnabled())
				return false;
			Bits::set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_HSI);
			break;

		case SystemClockSource::hse:
			if (!isHSEEnabled())
				return false;
			Bits::set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_HSE);
			break;

		case SystemClockSource::pll:
            if (!isPLLEnabled())
                return false;
            Bits::set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_PLL);
			break;
	}

	RCC->CFGR = CFGR;

	while (((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW) >> RCC_CFGR_SW_Pos))
		continue;

	// Si la latencia actual es mes alta que la indicada, la baixa
	//
	if (((ACR & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos) > (UInt32) fl) {
		Bits::clear(ACR, FLASH_ACR_LATENCY);
		Bits::set(ACR, ((UInt32)fl << FLASH_ACR_LATENCY_Pos) & FLASH_ACR_LATENCY_Msk);
		FLASH->ACR = ACR;
	}

	return true;
}
