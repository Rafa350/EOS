module;


#include "HTL/htl.h"


export module htl.clocks.stm32f7;

import htl.bits;


export namespace htl::clock {

	enum class ClockID {
		sysclk,
		pclk,
		pclk2,
		hclk,
		hse,
		hsi,
		lse,
		lsi
	};

	enum class HseBypassMode {
		on,
		off,
		unchanged
	};

	enum class PllSource {
		hsi,
		hse
	};

	enum class PllHseDivider {
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		_10,
		_11,
		_12,
		_13,
		_14,
		_15,
		_16
	};

	enum class PllMultiplier {
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		_10,
		_11,
		_12,
		_13,
		_14,
		_15,
		_16
	};

	enum class SysClkSource {
		hsi,
		hse,
		pll
	};

	enum class HClkPrescaler {
		_1,
		_2,
		_4,
		_8,
		_16,
		_64,
		_128,
		_256,
		_512
	};

	enum class PClkPrescaler {
		_1,
		_2,
		_4,
		_8,
		_16
	};

	void hsiEnable();
	void hsiDisable();
	bool isHsiEnabled();

	void hseEnable(HseBypassMode bypass = HseBypassMode::off);
	void hseDisable();
	bool isHseEnabled();

	void pllEnable();
	void pllDisable();
	bool isPllEnabled();
	bool setPllSource(PllSource value);
	void setPllMultiplier(PllMultiplier value);
	void setPllHseDivider(PllHseDivider value);

	bool setSysClkSource(SysClkSource source);
	void setHClkPrescaler(HClkPrescaler value);
	void setPClkPrescaler(PClkPrescaler value);

	unsigned getClockFrequency(ClockID clockId);
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge SysClk
/// \param    source: L'origen.
/// \return   True si tot es correcte, false en cas contrari.
///
bool htl::clock::setSysClkSource(
	htl::clock::SysClkSource source) {

	auto tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_SW_Msk;
	switch (source) {
		case SysClkSource::hse:
            if (!isHseEnabled())
                return false;
			tmp |= RCC_CFGR_SW_HSE;
			break;

		case SysClkSource::hsi:
            if (!isHsiEnabled())
                return false;
			tmp |= RCC_CFGR_SW_HSI;
			break;

		case SysClkSource::pll:
            if (!isPllEnabled())
                return false;
			tmp |= RCC_CFGR_SW_PLL;
			break;
	}

	RCC->CFGR = tmp;
	while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> 2) != (RCC->CFGR & RCC_CFGR_SW_Msk))
		continue;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el valor del divisor del rellotge HClk (AHB)
/// \param    value: El valor.
///
void htl::clock::setHClkPrescaler(
	htl::clock::HClkPrescaler value) {

	auto tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_HPRE_Msk;
	switch (value) {
        case HClkPrescaler::_1:
            tmp |= RCC_CFGR_HPRE_DIV1;
            break;

        case HClkPrescaler::_2:
            tmp |= RCC_CFGR_HPRE_DIV2;
            break;

        case HClkPrescaler::_4:
            tmp |= RCC_CFGR_HPRE_DIV4;
            break;

        case HClkPrescaler::_8:
            tmp |= RCC_CFGR_HPRE_DIV8;
            break;

        case HClkPrescaler::_16:
            tmp |= RCC_CFGR_HPRE_DIV16;
            break;

        case HClkPrescaler::_64:
            tmp |= RCC_CFGR_HPRE_DIV64;
            break;

        case HClkPrescaler::_128:
            tmp |= RCC_CFGR_HPRE_DIV128;
            break;

        case HClkPrescaler::_256:
            tmp |= RCC_CFGR_HPRE_DIV256;
            break;

        case HClkPrescaler::_512:
            tmp |= RCC_CFGR_HPRE_DIV512;
            break;
	}

	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSI
///
void htl::clock::hsiEnable() {

	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSION) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge HSI
///
void htl::clock::hsiDisable() {

	RCC->CR &= ~RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSION) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::isHsiEnabled() {

    return (RCC->CR & RCC_CR_HSION) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSE.
/// \param    bypass: El modus del bypass
///
void htl::clock::hseEnable(
	htl::clock::HseBypassMode bypass) {

	switch (bypass) {
		case HseBypassMode::on:
			RCC->CR |= RCC_CR_HSEBYP;
			break;

		case HseBypassMode::off:
			RCC->CR &= ~RCC_CR_HSEBYP;
			break;

		default:
			break;
	}
	RCC->CR |= RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge HSE.
///
void htl::clock::hseDisable() {

	RCC->CR &= ~RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::isHseEnabled() {

    return (RCC->CR & RCC_CR_HSERDY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el PLL
///
void htl::clock::pllEnable() {

	RCC->CR |= RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el PLL
///
void htl::clock::pllDisable() {

	RCC->CR &= ~RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el PLL esta activat.
/// \return   True si esta activat, false en cas contrari.
///
bool htl::clock::isPllEnabled() {

    return ((RCC->CR & RCC_CR_PLLON) != 0) && ((RCC->CR & RCC_CR_PLLRDY) != 0);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned htl::clock::getClockFrequency(
	htl::clock::ClockID clockId) {

	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

	unsigned fclk = 0;

	switch (clockId) {

		// System clock
		//
		case ClockID::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS_Msk) {
				case RCC_CFGR_SWS_HSE:
					fclk = CLOCK_HSE_FREQUENCY;
					break;

				case RCC_CFGR_SWS_HSI:
					fclk = CLOCK_HSI_FREQUENCY;
					break;

				case RCC_CFGR_SWS_PLL:  {
				    // PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
				    // SYSCLK = PLL_VCO / PLL_P
				    unsigned pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

				    unsigned pllvco;
				    if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) != 0)
				        pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
				    else
				        pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);

				    unsigned pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16) + 1) * 2;
				    fclk = pllvco / pllp;
				    break;
				}
			}
			break;

		case ClockID::pclk:
			fclk = getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos];
			break;

		case ClockID::pclk2:
			fclk = getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE2_Msk) >> RCC_CFGR_PPRE2_Pos];
			break;

		case ClockID::hclk:
			fclk = getClockFrequency(ClockID::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
			break;

		// High speed external clock
		//
		case ClockID::hse:
			fclk = CLOCK_HSE_FREQUENCY;
			break;

		// High speed internal clock
		//
		case ClockID::hsi:
			fclk = CLOCK_HSI_FREQUENCY;
			break;

		// Low speed external clock
		//
		case ClockID::lse:
			fclk = CLOCK_LSE_FREQUENCY;
			break;

		// Low speed internal clock
		//
		case ClockID::lsi:
			fclk = CLOCK_LSI_FREQUENCY;
			break;
	}

	return fclk;
}
