#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"


using namespace htl;
using namespace htl::clock;


/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge SysClk
/// \param    source: L'origen.
/// \return   True si tot es correcte, false en cas contrari.
///
bool Clock::setSysClkSource(
	SysClkSource source) {

	uint32_t tmp = RCC->CFGR;

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
void Clock::setHClkPrescaler(
	HClkPrescaler value) {

	uint32_t tmp = RCC->CFGR;

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
void Clock::hsiEnable() {

	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSION) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge HSI
///
void Clock::hsiDisable() {

	RCC->CR &= ~RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSION) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock::isHsiEnabled() {

    return (RCC->CR & RCC_CR_HSION) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSE.
/// \param    bypass: El modus del bypass
///
void Clock::hseEnable(
	HseBypassMode bypass) {

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
void Clock::hseDisable() {

	RCC->CR &= ~RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock::isHseEnabled() {

    return (RCC->CR & RCC_CR_HSERDY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el PLL
///
void Clock::pllEnable() {

	RCC->CR |= RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el PLL
///
void Clock::pllDisable() {

	RCC->CR &= ~RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el PLL esta activat.
/// \return   True si esta activat, false en cas contrari.
///
bool Clock::isPllEnabled() {

    return ((RCC->CR & RCC_CR_PLLON) != 0) && ((RCC->CR & RCC_CR_PLLRDY) != 0);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned Clock::getClockFrequency(
	ClockID clockID) {

	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
	static const uint8_t pllMultiplierTbl[16] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	static const uint8_t pllHseDividerTbl[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

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

				case RCC_CFGR_SWS_PLL:
#if defined(EOS_PLATFORM_STM32F0)
					if ((RCC->CFGR & RCC_CFGR_PLLSRC_Msk) == RCC_CFGR_PLLSRC_HSI_DIV2)
						fclk = CLOCK_HSI_FREQUENCY / 2;
					else
						fclk = CLOCK_HSE_FREQUENCY / pllHseDividerTbl[(RCC->CFGR2 & RCC_CFGR2_PREDIV_Msk) >> RCC_CFGR2_PREDIV_Pos];
					fclk *= pllMultiplierTbl[(RCC->CFGR & RCC_CFGR_PLLMUL_Msk) >> RCC_CFGR_PLLMUL_Pos];
#endif
					break;
			}
			break;

		case ClockID::hclk:
			fclk = getClockFrequency(ClockID::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
			break;

		case ClockID::hse:
			fclk = CLOCK_HSE_FREQUENCY;
			break;

		case ClockID::hsi:
			fclk = CLOCK_HSI_FREQUENCY;
			break;

#if defined(EOS_PLATFORM_STM32F0)
		case ClockID::hsi14:
			fclk = CLOCK_HSI14_FREQUENCY;
			break;
#endif

		case ClockID::lse:
			fclk = CLOCK_LSE_FREQUENCY;
			break;

		case ClockID::lsi:
			fclk = CLOCK_LSI_FREQUENCY;
			break;
	}

	return fclk;
}
