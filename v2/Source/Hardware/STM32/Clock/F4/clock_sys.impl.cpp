module;

#include "hardware.h"


module Eos.Hardware.Clock;


import Eos.Bits;
import Eos.Types;


using namespace eos;
using namespace eos::hardware::clock;


static_assert(platformCheck("STM32F4xxxx"));


/// ----------------------------------------------------------------------
/// @brief    Selecciona el rellotge principal del sistema
/// @param    source: El rellotge a seleccionar.
/// @param    fl: Latencia de la memoria FLASH
/// @return   True si tot es correcte, false en cas contrari.
/// @remarks  El posen els prescalers AHB, APB1 i APB2 a la maxima divisio
///
bool Clock::selectSystemClock(
	SystemClockSource source,
	FlashLatency fl) {

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


UInt32 Clock::getClockFrequency(
	ClockID clockID) {

	static const uint8_t shiftAHB[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 5, 6, 7, 8};
	static const uint8_t shiftAPB[8] = { 0, 0, 0, 0, 1, 2, 3, 4};

	unsigned fclk = 0;

	switch (clockID) {
		case ClockID::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS_Msk) {
				case RCC_CFGR_SWS_HSE:
					fclk = CLOCK_HSE_FREQUENCY;
					break;

				case RCC_CFGR_SWS_HSI:
					fclk = CLOCK_HSI_FREQUENCY;
					break;

				case RCC_CFGR_SWS_PLL: {
					auto pllMul = (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
					auto pllDiv = (RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos;
				    auto pllP = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1 ) * 2;
					if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSI)
						fclk = CLOCK_HSI_FREQUENCY;
					else
						fclk = CLOCK_HSE_FREQUENCY;
					fclk /= pllDiv;
					fclk *= pllMul;
				    fclk /= pllP;
				    fclk >>= shiftAHB[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
					break;
				}
			}
			break;

		case ClockID::hclk:
			fclk = getClockFrequency(ClockID::sysclk);
			break;

		case ClockID::pclk1:
			fclk = getClockFrequency(ClockID::hclk) >> shiftAPB[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos];
			break;

		case ClockID::pclk2:
			fclk = getClockFrequency(ClockID::hclk) >> shiftAPB[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos];
			break;

		case ClockID::tim1clk:
			fclk = getClockFrequency(ClockID::pclk1) << (((RCC->CFGR & ~RCC_CFGR_PPRE1) == 0) ? 0 : 1);
			break;

		case ClockID::tim2clk:
			fclk = getClockFrequency(ClockID::pclk2) << (((RCC->CFGR & ~RCC_CFGR_PPRE1) == 0) ? 0 : 1);
			break;

		case ClockID::hse:
			fclk = CLOCK_HSE_FREQUENCY;
			break;

		case ClockID::hsi:
			fclk = CLOCK_HSI_FREQUENCY;
			break;

		case ClockID::lse:
			fclk = CLOCK_LSE_FREQUENCY;
			break;

		case ClockID::lsi:
			fclk = CLOCK_LSI_FREQUENCY;
			break;
	}

	return fclk;
}
