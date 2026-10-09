module;


#include "hardware.h"


module Eos.Hardware.Clock;


import Eos.Bits;
import Eos.Types;


namespace f = eos::hardware::flash;

using namespace eos;
using namespace eos::hardware::clock;
using namespace eos::hardware::flash;


static_assert(Platform::is_STM32_G0);


/// ---------------------------------------------------------------------------
/// @brief    Selecciona el rellotge principal del sistema
/// @param    source: El rellotge a seleccionar.
/// @param    fl: Latencia de la memoria FLASH
/// @return   True si tot es correcte, false en cas contrari.
///
bool Clock::selectSystemClock(
	SystemClockSource source,
	FlashLatency fl) {

	// Si la latencia actual es mes baixa que la indicada, la puja
	//
	if (Flash::getLatency() < fl)
		Flash::setLatency(fl);

	auto CFGR = RCC->CFGR;

	// Inicialitza els divisor al valor mes alt
	//
	Bits::set(CFGR, 15UL << RCC_CFGR_HPRE_Pos);
	Bits::set(CFGR, 7UL << RCC_CFGR_PPRE_Pos);

	Bits::clear(CFGR, RCC_CFGR_SW_Msk);
	switch (source) {
		case SystemClockSource::hse:
			if (!isHSEEnabled())
				return false;
			Bits::set(CFGR, RCC_CFGR_SW_HSE);
			break;

		case SystemClockSource::lsi:
			if (!isLSIEnabled())
				return false;
			Bits::set(CFGR, RCC_CFGR_SW_LSI);
			break;

		case SystemClockSource::lse:
			if (!isLSEEnabled())
				return false;
			Bits::set(CFGR, RCC_CFGR_SW_LSE);
			break;

		case SystemClockSource::pllrclk:
            if (!isPLLEnabled() || ((RCC->PLLCFGR & RCC_PLLCFGR_PLLREN) == 0))
                return false;
            Bits::set(CFGR, RCC_CFGR_SW_PLLRCLK);
			break;

		case SystemClockSource::hsisys:
			Bits::set(CFGR, RCC_CFGR_SW_HSISYS);
			break;
	}

	RCC->CFGR = CFGR;

	while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW_Msk) >> RCC_CFGR_SW_Pos))
		continue;

    // Si la latencia actual es mes alta que la indicada, la baixa
	//
	if (Flash::getLatency() > fl)
		Flash::setLatency(fl);

	return true;
}


/// ---------------------------------------------------------------------------
/// @brief    Selecciona el divisor AHB
/// @param 	  prescaler: El valor a asignar.
///
void Clock::setAHBPrescaler(
	AHBPrescaler prescaler) {

	auto CFGR = RCC->CFGR;
	Bits::clear(CFGR, RCC_CFGR_HPRE_Msk);
	if (prescaler != AHBPrescaler::div1)
		Bits::set(CFGR, ((7 + (UInt32) prescaler) << RCC_CFGR_HPRE_Pos) & RCC_CFGR_HPRE_Msk);
	RCC->CFGR = CFGR;
}


/// ---------------------------------------------------------------------------
/// @brief    Selecciona el divisor APB
/// @param 	  prescaler: El valor a asignar.
///
void Clock::setAPBPrescaler(
	APBPrescaler prescaler) {

	auto CFGR = RCC->CFGR;
	Bits::clear(CFGR, RCC_CFGR_PPRE);
	if (prescaler != APBPrescaler::div1)
		Bits::set(CFGR, ((3 + (UInt32) prescaler) << RCC_CFGR_PPRE_Pos) & RCC_CFGR_PPRE_Msk);
	RCC->CFGR = CFGR;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte la frequencia d'un rellotge.
/// @param    clockID: Idenfificador del rellotge.
/// @return   El valor en hertz. Zero en cas d'error.
///
UInt32 Clock::getClockFrequency(
	ClockID clockID) {

	static const UInt8 shiftAHB[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
	static const UInt8 shiftAPB[8] = { 0, 0, 0, 0, 1, 2, 3, 4};

	UInt32 fclk = 0;

	switch (clockID) {
		case ClockID::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS) {
				case RCC_CFGR_SWS_HSISYS:
					fclk = getClockFrequency(ClockID::hsisys);
					break;

				case RCC_CFGR_SWS_HSE:
					fclk = clockHSEfrequency;
					break;

				case RCC_CFGR_SWS_PLLRCLK:
					fclk = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_Msk) == (0b10 << RCC_PLLCFGR_PLLSRC_Pos) ?
						 clockHSI16frequency: clockHSEfrequency;
					fclk /= ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM_Msk) >> RCC_PLLCFGR_PLLM_Pos) + 1;
					fclk *= (RCC->PLLCFGR & RCC_PLLCFGR_PLLN_Msk) >> RCC_PLLCFGR_PLLN_Pos;
					fclk /= ((RCC->PLLCFGR & RCC_PLLCFGR_PLLR_Msk) >> RCC_PLLCFGR_PLLR_Pos) + 1;
					break;

				case RCC_CFGR_SWS_LSI:
					fclk = clockLSIfrequency;
					break;

				case RCC_CFGR_SWS_LSE:
					fclk = clockLSEfrequency;
					break;
			}
			break;

		case ClockID::pclk:
			fclk = getClockFrequency(ClockID::hclk) >> shiftAPB[(RCC->CFGR & RCC_CFGR_PPRE_Msk) >> RCC_CFGR_PPRE_Pos];
			break;

		case ClockID::timpclk:
			fclk = getClockFrequency(ClockID::pclk) << (((RCC->CFGR & ~RCC_CFGR_PPRE_Msk) == 0) ? 0 : 1);
			break;

		case ClockID::hclk:
			fclk = getClockFrequency(ClockID::sysclk) >> shiftAHB[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
			break;

		case ClockID::hclk8:
			fclk = getClockFrequency(ClockID::hclk) / 8;
			break;

		case ClockID::hsisys:
			fclk = clockHSI16frequency >> ((RCC->CR & RCC_CR_HSIDIV_Msk) >> RCC_CR_HSIDIV_Pos);
			break;

		case ClockID::hse:
			fclk = clockHSEfrequency;
			break;

		case ClockID::hsi16:
			fclk = clockHSI16frequency;
			break;

#if defined(RCC_CR_HSI48ON)
		case ClockID::hsi48:
			fclk = clockHSI48frequency;
			break;
#endif

		case ClockID::lse:
			fclk = clockLSEfrequency;
			break;

		case ClockID::lsi:
			fclk = clockLSIfrequency;
			break;

		default:
			break;
	}

	return fclk;
}
