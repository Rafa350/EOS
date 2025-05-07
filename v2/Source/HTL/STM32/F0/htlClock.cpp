#include "HTL/htl.h"
#include "HTL/STM32/F0/htlClock.h"


#if !defined(EOS_PLATFORM_STM32F0)
	#error Solo es valido para la plataforma STM32F0
#endif


namespace htl::clock {


/// ----------------------------------------------------------------------
/// \brief    Selecciona la font de SysClk
/// \param    source: L'origen.
/// \return   True si tot es correcte, false en cas contrari.
///
bool setSysClkSource(
	SysClkSource source) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_SW_Msk;
	switch (source) {
		case SysClkSource::hse:
            if (!hseIsEnabled())
                return false;
			tmp |= RCC_CFGR_SW_HSE;
			break;

		case SysClkSource::hsi:
            if (!hsiIsEnabled())
                return false;
			tmp |= RCC_CFGR_SW_HSI;
			break;

		case SysClkSource::pll:
            if (!pllIsEnabled())
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
/// \brief    Selecciona la font del rellotge I2CClk
/// \param    source: La font.
///
void setI2CClkSource(
	I2CClkSource source) {

	switch (source) {
		case I2CClkSource::hsi:
			RCC->CFGR3 &= ~RCC_CFGR3_I2C1SW;
			break;

		case I2CClkSource::sysclk:
			RCC->CFGR3 |= RCC_CFGR3_I2C1SW;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el valor del divisor del rellotge HClk (AHB)
/// \param    value: El valor.
///
void setHClkPrescaler(
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
/// \brief    Selecciona el valor del divisor del rellotge PClk (APB)
/// \param    value: El valor.
///
void setPClkPrescaler(
	PClkPrescaler value) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_PPRE_Msk;
	switch (value) {
        case PClkPrescaler::_1:
            tmp |= RCC_CFGR_PPRE_DIV1;
            break;

        case PClkPrescaler::_2:
            tmp |= RCC_CFGR_PPRE_DIV2;
            break;

        case PClkPrescaler::_4:
            tmp |= RCC_CFGR_PPRE_DIV4;
            break;

        case PClkPrescaler::_8:
            tmp |= RCC_CFGR_PPRE_DIV8;
            break;

        case PClkPrescaler::_16:
            tmp |= RCC_CFGR_PPRE_DIV16;
            break;
	}

	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSI
///
void hsiEnable() {

	RCC->CR |= RCC_CR_HSION;
	while (!hsiIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge HSI
///
void hsiDisable() {

	RCC->CR &= ~RCC_CR_HSION;
	while (hsiIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool hsiIsEnabled() {

    return (RCC->CR & RCC_CR_HSIRDY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSE.
/// \param    bypass: El modus del bypass
///
void hseEnable(
	HseBypassMode bypass) {

	if (!hseIsEnabled()) {
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
		while (!hseIsEnabled())
			continue;
	}
}


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge HSE.
///
void hseDisable() {

	RCC->CR &= ~RCC_CR_HSEON;
	while (hseIsEnabled())
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

	RCC->CR |= RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el PLL
///
void pllDisable() {

	RCC->CR &= ~RCC_CR_PLLON;
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
/// \brief    Selecciona el rellotge d'entrada del PLL.
/// \param    value: El valor.
/// \return   True si tot es correce, false en cas contrari.
///
bool pllSetSource(
	PllSource value) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_PLLSRC_Msk;
	switch (value) {
		case PllSource::hsi:
            if (!hsiIsEnabled())
                return false;
			tmp |= RCC_CFGR_PLLSRC_HSI_DIV2;
			break;

		case PllSource::hse:
            if (!hseIsEnabled())
                return false;
			tmp |= RCC_CFGR_PLLSRC_HSE_PREDIV;
			break;
	}

	RCC->CFGR = tmp;

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor del divisor de la entrada HSE del PLL.
/// \param    value: El valor.
///
void pllSetHseDivider(
	PllHseDivider value) {

	uint32_t tmp = RCC->CFGR2;

	tmp &= ~RCC_CFGR2_PREDIV_Msk;
	switch (value) {
		case PllHseDivider::_1:
			tmp |= RCC_CFGR2_PREDIV_DIV1;
			break;

		case PllHseDivider::_2:
			tmp |= RCC_CFGR2_PREDIV_DIV2;
			break;

		case PllHseDivider::_3:
			tmp |= RCC_CFGR2_PREDIV_DIV3;
			break;

		case PllHseDivider::_4:
			tmp |= RCC_CFGR2_PREDIV_DIV4;
			break;

		case PllHseDivider::_5:
			tmp |= RCC_CFGR2_PREDIV_DIV5;
			break;

		case PllHseDivider::_6:
			tmp |= RCC_CFGR2_PREDIV_DIV6;
			break;

		case PllHseDivider::_7:
			tmp |= RCC_CFGR2_PREDIV_DIV7;
			break;

		case PllHseDivider::_8:
			tmp |= RCC_CFGR2_PREDIV_DIV8;
			break;

		case PllHseDivider::_9:
			tmp |= RCC_CFGR2_PREDIV_DIV9;
			break;

		case PllHseDivider::_10:
			tmp |= RCC_CFGR2_PREDIV_DIV10;
			break;

		case PllHseDivider::_11:
			tmp |= RCC_CFGR2_PREDIV_DIV11;
			break;

		case PllHseDivider::_12:
			tmp |= RCC_CFGR2_PREDIV_DIV12;
			break;

		case PllHseDivider::_13:
			tmp |= RCC_CFGR2_PREDIV_DIV13;
			break;

		case PllHseDivider::_14:
			tmp |= RCC_CFGR2_PREDIV_DIV14;
			break;

		case PllHseDivider::_15:
			tmp |= RCC_CFGR2_PREDIV_DIV15;
			break;

		case PllHseDivider::_16:
			tmp |= RCC_CFGR2_PREDIV_DIV16;
			break;

	}

	RCC->CFGR2 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor del multiplicador del PLL.
/// \param    value: El valor.
///
void pllSetMultiplier(
	PllMultiplier value) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_PLLMUL_Msk;
	switch (value) {
		case PllMultiplier::_2:
			tmp |= RCC_CFGR_PLLMUL2;
			break;

		case PllMultiplier::_3:
			tmp |= RCC_CFGR_PLLMUL3;
			break;

		case PllMultiplier::_4:
			tmp |= RCC_CFGR_PLLMUL4;
			break;

		case PllMultiplier::_5:
			tmp |= RCC_CFGR_PLLMUL5;
			break;

		case PllMultiplier::_6:
			tmp |= RCC_CFGR_PLLMUL6;
			break;

		case PllMultiplier::_7:
			tmp |= RCC_CFGR_PLLMUL7;
			break;

		case PllMultiplier::_8:
			tmp |= RCC_CFGR_PLLMUL8;
			break;

		case PllMultiplier::_9:
			tmp |= RCC_CFGR_PLLMUL9;
			break;

		case PllMultiplier::_10:
			tmp |= RCC_CFGR_PLLMUL10;
			break;

		case PllMultiplier::_11:
			tmp |= RCC_CFGR_PLLMUL11;
			break;

		case PllMultiplier::_12:
			tmp |= RCC_CFGR_PLLMUL12;
			break;

		case PllMultiplier::_13:
			tmp |= RCC_CFGR_PLLMUL13;
			break;

		case PllMultiplier::_14:
			tmp |= RCC_CFGR_PLLMUL14;
			break;

		case PllMultiplier::_15:
			tmp |= RCC_CFGR_PLLMUL15;
			break;

		case PllMultiplier::_16:
			tmp |= RCC_CFGR_PLLMUL16;
			break;
	}

	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned getClockFrequency(
	ClockID clockId) {

	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
	static const uint8_t pllMultiplierTbl[16] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	static const uint8_t pllHseDividerTbl[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

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

				case RCC_CFGR_SWS_PLL:
					if ((RCC->CFGR & RCC_CFGR_PLLSRC_Msk) == RCC_CFGR_PLLSRC_HSI_DIV2)
						fclk = CLOCK_HSI_FREQUENCY / 2;
					else
						fclk = CLOCK_HSE_FREQUENCY / pllHseDividerTbl[(RCC->CFGR2 & RCC_CFGR2_PREDIV_Msk) >> RCC_CFGR2_PREDIV_Pos];
					fclk *= pllMultiplierTbl[(RCC->CFGR & RCC_CFGR_PLLMUL_Msk) >> RCC_CFGR_PLLMUL_Pos];
					break;
			}
			break;

		case ClockID::pclk:
			fclk = getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE_Msk) >> RCC_CFGR_PPRE_Pos];
			break;

		case ClockID::hclk:
			fclk = getClockFrequency(ClockID::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
			break;

		case ClockID::i2cclk:
			if ((RCC->CFGR3 & RCC_CFGR3_I2C1SW) == 0)
				fclk = CLOCK_HSI_FREQUENCY;
			else
				fclk = getClockFrequency(ClockID::sysclk);
			break;

		case ClockID::hse:
			fclk = CLOCK_HSE_FREQUENCY;
			break;

		case ClockID::hsi:
			fclk = CLOCK_HSI_FREQUENCY;
			break;

		case ClockID::hsi14:
			fclk = CLOCK_HSI14_FREQUENCY;
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

}
