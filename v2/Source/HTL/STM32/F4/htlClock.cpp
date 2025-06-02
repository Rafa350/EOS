#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlClock.h"


using namespace htl::bits;


/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge SysClk
/// \param    source: L'origen.
/// \return   True si tot es correcte, false en cas contrari.
///
bool htl::clock::sysclkSetSource(
	SysClkSource source) {

	auto CFGR = RCC->CFGR;
	clear(CFGR, RCC_CFGR_SW);
	switch (source) {
		case SysClkSource::hse:
            if (!hseIsEnabled())
                return false;
			set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_HSE);
			break;

		case SysClkSource::hsi:
            if (!hsiIsEnabled())
                return false;
			set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_HSI);
			break;

		case SysClkSource::pll:
            if (!pllIsEnabled())
                return false;
			set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_PLL);
			break;
	}
	RCC->CFGR = CFGR;

	while (((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW) >> RCC_CFGR_SW_Pos))
		continue;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el valor del divisor del rellotge HClk (AHB)
/// \param    value: El valor.
///
void htl::clock::hclkSetPrescaler(
	HClkPrescaler value) {

	auto CFGR = RCC->CFGR;
	clear(CFGR, RCC_CFGR_HPRE);
	switch (value) {
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
void htl::clock::hsiEnable() {

	set(RCC->CR, RCC_CR_HSION);

	while ((RCC->CR & RCC_CR_HSION) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge HSI
///
void htl::clock::hsiDisable() {

	clear(RCC->CR, RCC_CR_HSION);

	while ((RCC->CR & RCC_CR_HSION) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::hsiIsEnabled() {

    return (RCC->CR & RCC_CR_HSION) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSE.
/// \param    bypass: El modus del bypass
///
void htl::clock::hseEnable(
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
void htl::clock::hseDisable() {

	clear(RCC->CR, RCC_CR_HSEON);

	while ((RCC->CR & RCC_CR_HSERDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::hseIsEnabled() {

    return (RCC->CR & RCC_CR_HSERDY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el PLL
///
void htl::clock::pllEnable() {

	set(RCC->CR, RCC_CR_PLLON);

	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el PLL
///
void htl::clock::pllDisable() {

	clear(RCC->CR, RCC_CR_PLLON);

	while ((RCC->CR & RCC_CR_PLLRDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el PLL esta activat.
/// \return   True si esta activat, false en cas contrari.
///
bool htl::clock::pllIsEnabled() {

    return ((RCC->CR & RCC_CR_PLLON) != 0) && ((RCC->CR & RCC_CR_PLLRDY) != 0);
}


/// ----------------------------------------------------------------------
/// \brief    Configura el PLL.
/// \param    source: Rellotge font.
/// \param    multiplier: Factor principal de multiplicacio (N).
/// \param    divider: Factor principal de divisio (M).
/// \param    divP: Factor secundari de divisio (P).
/// \param    divQ: Factor secundari de divisio (Q).
/// \return   True si s'ha realitzat l'operacio correctament.
///

bool htl::clock::pllConfigure(
	PllSource source,
	unsigned multiplier,
	unsigned divider,
	PllPDivider divP,
	PllQDivider divQ) {

	if (divider < 2 || divider > 63 || multiplier < 50 || multiplier > 432)
		return false;

	if (clock::pllIsEnabled())
		return false;

    auto PLLCFGR = RCC->PLLCFGR;

	clear(PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN);
	switch (source) {
		case PllSource::hsi:
            if (!hsiIsEnabled())
                return false;
			set(PLLCFGR, (typeof(PLLCFGR)) (0b10 << RCC_PLLCFGR_PLLSRC_Pos));
			break;

		case PllSource::hse:
			if (!hseIsEnabled())
				return false;
			set(PLLCFGR, (typeof(PLLCFGR)) (0b11 <<  RCC_PLLCFGR_PLLSRC_Pos));
			break;
	}
	set(PLLCFGR, (divider << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM);
	set(PLLCFGR, (multiplier << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN);
	set(PLLCFGR, (typeof(PLLCFGR)) ((uint32_t) divP << RCC_PLLCFGR_PLLP_Pos));
	set(PLLCFGR, (typeof(PLLCFGR)) (2 + ((uint32_t) divQ << RCC_PLLCFGR_PLLQ_Pos)));

	RCC->PLLCFGR = PLLCFGR;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned htl::clock::getClockFrequency(
	ClockID clockID) {

	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 5, 6, 7, 8};
	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};

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
					break;
				}
			}
			break;

		case ClockID::hclk:
			fclk = getClockFrequency(ClockID::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos];
			break;

		case ClockID::pclk1:
			fclk = getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos];
			break;

		case ClockID::pclk2:
			fclk = getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos];
			break;

		case ClockID::timpclk:
			fclk = getClockFrequency(ClockID::pclk1) << (((RCC->CFGR & ~RCC_CFGR_PPRE1) == 0) ? 0 : 1);
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
