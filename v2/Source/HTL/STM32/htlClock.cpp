#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlClock.h"


#if defined(EOS_PLATFORM_STM32G0)
#define RCC_CFGR_SW_HSISYS        (0UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_HSE           (1UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_PLLRCLK       (2UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_LSI           (3UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_LSE           (4UL << RCC_CFGR_SW_Pos)
#define RCC_PLLCFGR_PLLSRC_HSI16  (2UL << RCC_PLLCFGR_PLLSRC_Pos)
#endif


htl::clock::ClockDevice htl::clock::ClockDevice::_instance;


using namespace htl::bits;


/// ----------------------------------------------------------------------
/// \brief    Constructor per defecte del dispositiu.
///
htl::clock::ClockDevice::ClockDevice() {

}


/// ----------------------------------------------------------------------
/// \brief    Activa el clock LSE
///
void htl::clock::ClockDevice::enableLSE() const {

	set(RCC->BDCR, RCC_BDCR_LSEON);
	while (!isLSEEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el clock LSE
///
void htl::clock::ClockDevice::disableLSE() const {

	clear(RCC->BDCR, RCC_BDCR_LSEON);
	while (isLSEEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el clock LSE esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::ClockDevice::isLSEEnabled() const {

	return isSet(RCC->BDCR, RCC_BDCR_LSERDY);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el clock HSE
/// \param    hseBaypassMode: Indica si utilitza un rellotge extern
///
void htl::clock::ClockDevice::enableHSE(
	HseBypassMode bypass) const {

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
	while (!isHSEEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el clock HSE
///
void htl::clock::ClockDevice::disableHSE() const {
	hseDisable();

	clear(RCC->CR, RCC_CR_HSEON);
	while (isHSEEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el clock HSE esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::ClockDevice::isHSEEnabled() const {

    return (RCC->CR & RCC_CR_HSERDY) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el clock LSI
///
void htl::clock::ClockDevice::enableLSI() const {

	set(RCC->CR, RCC_CSR_LSION);
	while (!isLSIEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el clock LSI
///
void htl::clock::ClockDevice::disableLSI() const {

	clear(RCC->CR, RCC_CSR_LSION);
	while (isLSIEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el clock LSI esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::ClockDevice::isLSIEnabled() const {

	return isSet(RCC->CSR, RCC_CSR_LSION);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el clock HSI
///
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void htl::clock::ClockDevice::enableHSI() const {

	set(RCC->CR, RCC_CR_HSION);
	while (!isHSIEnabled())
		continue;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Desactiva el clock HSI
///
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
void htl::clock::ClockDevice::disableHSI() const {

	clear(RCC->CR, RCC_CR_HSION);
	while (isHSIEnabled())
		continue;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Comprova si el clock HSI esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
bool htl::clock::ClockDevice::isHSIEnabled() const {

	return isSet(RCC->CR, RCC_CR_HSION);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Activa el clock HSI16
/// \param    kernelMode: Selecciona el modus kernel.
///
#if defined(EOS_PLATFORM_STM32G0)
void htl::clock::ClockDevice::enableHSI16(
	bool kernelMode) const {

	set(RCC->CR, RCC_CR_HSION);
	while (!isHSI16Enabled())
		continue;

	if (kernelMode)
		set(RCC->CR, RCC_CR_HSIKERON);
	else
		clear(RCC->CR, RCC_CR_HSIKERON);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Desactiva el clock HSI16
///
#if defined(EOS_PLATFORM_STM32G0)
void htl::clock::ClockDevice::disableHSI16() const {

	clear(RCC->CR, RCC_CR_HSION);
	while (isHSI16Enabled())
		continue;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Comprova si el clock HSI16 esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
#if defined(EOS_PLATFORM_STM32G0)
bool htl::clock::ClockDevice::isHSI16Enabled() const {

	return isSet(RCC->CR, RCC_CR_HSION);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Activa el PLL
///
void htl::clock::ClockDevice::enablePLL() const {

	set(RCC->CR, RCC_CR_PLLON);
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el PLL
///
void htl::clock::ClockDevice::disablePLL() const {

	clear(RCC->CR, RCC_CR_PLLON);
	while ((RCC->CR & RCC_CR_PLLRDY) != 0)
		continue;

#if defined(EOS_PLATFORM_STM32G0)
	clear(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN | RCC_PLLCFGR_PLLQEN | RCC_PLLCFGR_PLLREN);
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el PLL esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::ClockDevice::isPLLEnabled() const {

    return (isSet(RCC->CR, RCC_CR_PLLON) && isSet(RCC->CR, RCC_CR_PLLRDY));
}


/// ----------------------------------------------------------------------
/// \brief    Configura el PLL
/// \param    sorce: El rellotge.
/// \param    multiplier: Factor de multiplicacio (N)
/// \param    divider: Factor de divisio (M)
/// \param    divP: Factor de divisio de la sortida P
/// \param    divQ: Factor de divisio de la sortida Q
/// \param    divR: Factor de divisio de la sortida R
/// \return   True si tot es correcte, false en cas contrari.
///
#if defined(EOS_PLATFORM_STM32G0)
bool htl::clock::ClockDevice::configurePLL(
		PLLsource source,
		unsigned multiplier,
		unsigned divider,
		PLLPdivider divP,
		PLLQdivider divQ,
		PLLRdivider divR) const {

	if (divider < 1 || divider > 8 || multiplier < 8 || multiplier > 86)
		return false;

	if (isPLLEnabled())
		return false;

    auto PLLCFGR = RCC->PLLCFGR;

	clear(PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN);
	switch (source) {
		case PLLsource::hsi16:
            if (!isHSI16Enabled())
                return false;
			set(PLLCFGR, RCC_PLLCFGR_PLLSRC_HSI16);
			break;

		case PLLsource::hse:
			if (!isHSEEnabled())
				return false;
			set(PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);
			break;
	}
	set(PLLCFGR, ((divider - 1) << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk);
	set(PLLCFGR,  (multiplier << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk);

	// Configura el divisor P
	//
	if (divP == PLLPdivider::disabled)
		clear(PLLCFGR, RCC_PLLCFGR_PLLPEN);
	else {
		clear(PLLCFGR, RCC_PLLCFGR_PLLP);
		set(PLLCFGR, ((uint32_t) divP << RCC_PLLCFGR_PLLP_Pos) & RCC_PLLCFGR_PLLP);
		set(PLLCFGR, RCC_PLLCFGR_PLLPEN);
	}

	// Configura el divisor Q
	//
	if (divQ == PLLQdivider::disabled)
		clear(PLLCFGR, RCC_PLLCFGR_PLLQEN);
	else {
		clear(PLLCFGR, RCC_PLLCFGR_PLLQ);
		set(PLLCFGR, ((uint32_t) divQ << RCC_PLLCFGR_PLLQ_Pos) & RCC_PLLCFGR_PLLQ);
		set(PLLCFGR, RCC_PLLCFGR_PLLQEN);
	}

	// Configura el divisor R
	//
	if (divR == PLLRdivider::disabled)
		clear(PLLCFGR, RCC_PLLCFGR_PLLREN);
	else {
		clear(PLLCFGR, RCC_PLLCFGR_PLLR);
		set(PLLCFGR, ((uint32_t) divR << RCC_PLLCFGR_PLLR_Pos) & RCC_PLLCFGR_PLLR);
		set(PLLCFGR, RCC_PLLCFGR_PLLREN);
	}

	RCC->PLLCFGR = PLLCFGR;

	return true;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge principal del sistema
/// \param    source: El rellotge a seleccionar.
/// \return   True si tot es correcte, false en cas contrari.
///
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
bool htl::clock::ClockDevice::selectSystemClock(
	SystemClockSource source) const {

	auto CFGR = RCC->CFGR;

	clear(CFGR, RCC_CFGR_SW);
	switch (source) {
		case SystemClockSource::hsi:
			if (!isHSIEnabled())
				return false;
			set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_HSI);
			break;

		case SystemClockSource::hse:
			if (!isHSEEnabled())
				return false;
			set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_HSE);
			break;

		case SystemClockSource::pll:
            if (!isPLLEnabled())
                return false;
			set(CFGR, (typeof(CFGR)) RCC_CFGR_SW_PLL);
			break;
	}

	RCC->CFGR = CFGR;

	while (((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW) >> RCC_CFGR_SW_Pos))
		continue;

	return true;
}

#elif defined(EOS_PLATFORM_STM32G0)
bool htl::clock::ClockDevice::selectSystemClock(
	SystemClockSource source) const {

	auto CFGR = RCC->CFGR;

	clear(CFGR, RCC_CFGR_SW);
	switch (source) {
		case SystemClockSource::hse:
			if (!isHSEEnabled())
				return false;
			set(CFGR, RCC_CFGR_SW_HSE);
			break;

		case SystemClockSource::lsi:
			if (!isLSIEnabled())
				return false;
			set(CFGR, RCC_CFGR_SW_LSI);
			break;

		case SystemClockSource::lse:
			if (!isLSEEnabled())
				return false;
			set(CFGR, RCC_CFGR_SW_LSE);
			break;

		case SystemClockSource::pllrclk:
#if defined(EOS_PLATFORM_STM32G0)
            if (!isPLLEnabled() || ((RCC->PLLCFGR & RCC_PLLCFGR_PLLREN) == 0))
#else
            if (!isPLLEnabled())
#endif
                return false;
			set(CFGR, RCC_CFGR_SW_PLLRCLK);
			break;

		case SystemClockSource::hsisys:
			set(CFGR, RCC_CFGR_SW_HSISYS);
			break;
	}

	RCC->CFGR = CFGR;

	while (((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW) >> RCC_CFGR_SW_Pos))
		continue;

	return true;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia del rellotge especificat.
/// \param    clockID: El identificador del rellotge.
/// \return   La frequencia en hertz. 0 en cas d'error.
///
#if defined(EOS_PLATFORM_STM32F4)
unsigned htl::clock::ClockDevice::getClockFrequency(
	ClockID clockID) const {

	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 5, 6, 7, 8};
	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};

	unsigned fclk = 0;

	switch (clockID) {
		case ClockID::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS_Msk) {
				case RCC_CFGR_SWS_HSE:
					fclk = clockHSEfrequency;
					break;

				case RCC_CFGR_SWS_HSI:
					fclk = clockHSIfrequency;
					break;

				case RCC_CFGR_SWS_PLL: {
					auto pllMul = (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
					auto pllDiv = (RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos;
				    auto pllP = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1 ) * 2;
					if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSI)
						fclk = clockHSIfrequency;
					else
						fclk = clockHSEfrequency;
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
			fclk = clockHSEfrequency;
			break;

		case ClockID::hsi:
			fclk = clockHSIfrequency;
			break;

		case ClockID::lse:
			fclk = clockLSEfrequency;
			break;

		case ClockID::lsi:
			fclk = clockLSIfrequency;
			break;
	}

	return fclk;
}

#elif defined(EOS_PLATFORM_STM32F7)
unsigned htl::clock::ClockDevice::getClockFrequency(
	ClockID clockID) const {

	return 0;
}

#elif defined(EOS_PLATFORM_STM32G0)
unsigned htl::clock::ClockDevice::getClockFrequency(
	ClockID clockID) const {

	static const uint8_t hsiDividerTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7};
	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

	unsigned fclk = 0;

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
					fclk = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == (0b10 << RCC_PLLCFGR_PLLSRC_Pos) ?
						 clockHSI16frequency: clockHSEfrequency;
					fclk /= ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1;
					fclk *= (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
					fclk /= ((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos) + 1;
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
			fclk = getClockFrequency(ClockID::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE_Msk) >> RCC_CFGR_PPRE_Pos];
			break;

		case ClockID::timpclk:
			fclk = getClockFrequency(ClockID::pclk) << (((RCC->CFGR & ~RCC_CFGR_PPRE_Msk) == 0) ? 0 : 1);
			break;

		case ClockID::hclk:
			fclk = getClockFrequency(ClockID::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
			break;

		case ClockID::hclk8:
			fclk = getClockFrequency(ClockID::hclk) / 8;
			break;

		case ClockID::hsisys:
			fclk = CLOCK_HSI16_FREQUENCY >> hsiDividerTbl[(RCC->CR & RCC_CR_HSIDIV_Msk) >> RCC_CR_HSIDIV_Pos];
			break;

		case ClockID::hse:
			fclk = clockHSEfrequency;
			break;

		case ClockID::hsi16:
			fclk = clockHSI16frequency;
			break;

#if defined(EOS_PLATFORM_SRTM32G0B1)
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
#endif
