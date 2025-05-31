#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlClock.h"


using namespace htl::bits;
using namespace htl::clock;

/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge SYSCLK
/// \param    source: L'origen.
/// \return   True si tot es correcte, false en cas contrari.
///
bool sysclkSetSource(
	SysClkSource source) {

	auto CFGR = RCC->CFGR;

	clear(CFGR, RCC_CFGR_SW);
	switch (source) {
		case SysClkSource::hse:
            if (!hseIsEnabled())
                return false;
			set(CFGR, (typeof(CFGR))  RCC_CFGR_SW_HSE);
			break;

		case SysClkSource::hsi:
            if (!hsiIsEnabled())
                return false;
			set(CFGR, (typeof(CFGR))  RCC_CFGR_SW_HSI);
			break;

		case SysClkSource::pll:
            if (!pllIsEnabled())
                return false;
			set(CFGR, (typeof(CFGR))  RCC_CFGR_SW_PLL);
			break;
	}

	RCC->CFGR = CFGR;

	while (((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW) >> RCC_CFGR_SW_Pos))
		continue;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el valor del divisor del rellotge HCLK (AHB)
/// \param    value: El valor.
///
void hclkSetPrescaler(
	HClkPrescaler value) {

	auto CFGR = RCC->CFGR;

	clear(CFGR, RCC_CFGR_HPRE);
	switch (value) {
        case HClkPrescaler::div1:
            set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV1);
            break;

        case HClkPrescaler::div2:
            set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV2);
            break;

        case HClkPrescaler::div4:
            set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV4);
            break;

        case HClkPrescaler::div8:
        	set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV8);
            break;

        case HClkPrescaler::div16:
        	set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV16);
            break;

        case HClkPrescaler::div64:
        	set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV64);
            break;

        case HClkPrescaler::div128:
        	set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV128);
            break;

        case HClkPrescaler::div256:
        	set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV256);
            break;

        case HClkPrescaler::div512:
        	set(CFGR, (typeof(CFGR)) RCC_CFGR_HPRE_DIV512);
            break;
	}

	RCC->CFGR = CFGR;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSI
///
void hsiEnable() {

	set(RCC->CR, RCC_CR_HSION);
	while ((RCC->CR & RCC_CR_HSION) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge HSI
///
void hsiDisable() {

	clear(RCC->CR, RCC_CR_HSION);
	while ((RCC->CR & RCC_CR_HSION) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool hsiIsEnabled() {

    return (RCC->CR & RCC_CR_HSION) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSE.
/// \param    bypass: El modus del bypass
///
void hseEnable(
	HseBypassMode bypass) {

	switch (bypass) {
		case HseBypassMode::on:
			set(RCC->CR, RCC_CR_HSEBYP);
			break;

		case HseBypassMode::off:
			clear(RCC->CR, RCC_CR_HSEBYP);
			break;

		default:
			break;
	}
	set(RCC->CR, RCC_CR_HSEON);
	while ((RCC->CR & RCC_CR_HSERDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge HSE.
///
void hseDisable() {

	clear(RCC->CR, RCC_CR_HSEON);
	while ((RCC->CR & RCC_CR_HSERDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool hseIsEnabled() {

    return (RCC->CR & RCC_CR_HSERDY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el PLL
///
void pllEnable() {

	set(RCC->CR, RCC_CR_PLLON);
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el PLL
///
void pllDisable() {

	clear(RCC->CR, RCC_CR_PLLON);
	while ((RCC->CR & RCC_CR_PLLRDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el PLL esta activat.
/// \return   True si esta activat, false en cas contrari.
///
bool pllIsEnabled() {

    return ((RCC->CR & RCC_CR_PLLON) != 0) && ((RCC->CR & RCC_CR_PLLRDY) != 0);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned htl::clock::getClockFrequency(
	ClockID clockId) {

	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

	unsigned fclk = 0;

	switch (clockId) {
		case ClockID::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS_Msk) {
				case RCC_CFGR_SWS_HSE:
					fclk = CLOCK_HSE_FREQUENCY;
					break;

				case RCC_CFGR_SWS_HSI:
					fclk = CLOCK_HSI_FREQUENCY;
					break;

				case RCC_CFGR_SWS_PLL: {
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

		case ClockID::pclk1:
			fclk = htl::clock::getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos];
			break;

		case ClockID::pclk2:
			fclk = htl::clock::getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE2_Msk) >> RCC_CFGR_PPRE2_Pos];
			break;

		case ClockID::hclk:
			fclk = htl::clock::getClockFrequency(ClockID::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
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
