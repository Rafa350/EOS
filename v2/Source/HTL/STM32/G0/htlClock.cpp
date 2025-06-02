#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlClock.h"


#if !defined(EOS_PLATFORM_STM32G0)
	#error "Valid for STM32G0 platform only"
#endif


struct CFGR_SW {
	static constexpr uint32_t Mask    = RCC_CFGR_SW_Msk;
	static constexpr uint32_t HSISYS  = 0 << RCC_CFGR_SW_Pos;
	static constexpr uint32_t HSE     = 1 << RCC_CFGR_SW_Pos;
	static constexpr uint32_t PLLRCLK = 2 << RCC_CFGR_SW_Pos;
	static constexpr uint32_t LSI     = 3 << RCC_CFGR_SW_Pos;
	static constexpr uint32_t LSE     = 4 << RCC_CFGR_SW_Pos;
};

struct CFGR_HPRE {
	static constexpr uint32_t Mask    = RCC_CFGR_HPRE_Msk;
};


/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge SysClk
/// \param    source: L'origen.
/// \return   True si tot es correcte, false en cas contrari.
///
bool htl::clock::sysclkSetSource(
	SysClkSource source) {

	auto CFGR = RCC->CFGR;

	bits::clear(CFGR, CFGR_SW::Mask);
	switch (source) {
		case SysClkSource::hse:
			if (!hseIsEnabled())
				return false;
			bits::set(CFGR, CFGR_SW::HSE);
			break;

		case SysClkSource::lsi:
			if (!lsiIsEnabled())
				return false;
			bits::set(CFGR, CFGR_SW::LSI);
			break;

		case SysClkSource::lse:
			if (!lseIsEnabled())
				return false;
			bits::set(CFGR, CFGR_SW::LSE);
			break;

		case SysClkSource::pllrclk:
            if (!pllIsEnabled() || ((RCC->PLLCFGR & RCC_PLLCFGR_PLLREN_Msk) == 0))
                return false;
			bits::set(CFGR, CFGR_SW::PLLRCLK);
			break;

		case SysClkSource::hsisys:
			bits::set(CFGR, CFGR_SW::HSISYS);
			break;
	}

	RCC->CFGR = CFGR;

	while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW_Msk) >> RCC_CFGR_SW_Pos))
		continue;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el divisor del rellotge HSISYS
/// \param    value: El valor del divisor.
///
void htl::clock::hsisysSetPrescaler(
	HsisysPrescaler value) {

	auto CR = RCC->CR;
	bits::clear(CR, RCC_CR_HSIDIV);
	bits::set(CR, ((uint32_t) value) << RCC_CR_HSIDIV_Pos);
	RCC->CR = CR;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el valor del divisor del rellotge HClk (AHB)
/// \param    value: El valor.
///
void htl::clock::hclkSetPrescaler(
	HClkPrescaler value) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_HPRE_Msk;
	switch (value) {
        case HClkPrescaler::div1:
            tmp |= 0b0000 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div2:
            tmp |= 0b1000 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div4:
            tmp |= 0b1001 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div8:
            tmp |= 0b1010 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div16:
            tmp |= 0b1011 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div64:
            tmp |= 0b1100 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div128:
            tmp |= 0b1101 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div256:
            tmp |= 0b1110 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::div512:
            tmp |= 0b1111 << RCC_CFGR_HPRE_Pos;
            break;
	}

	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el valor del divisor del rellotge PClk (APB)
/// \param    value: El valor.
///
void htl::clock::pclkSetPrescaler(
	PClkPrescaler value) {

	static const uint32_t tbl[] = { 0b000, 0b100, 0b101, 0b110, 0b111 };

	uint32_t CFGR = RCC->CFGR;
	bits::clear(CFGR, RCC_CFGR_PPRE_Msk);
	bits::set(CFGR, tbl[(uint32_t) value] << RCC_CFGR_PPRE_Pos);
	RCC->CFGR = CFGR;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSI
///
void htl::clock::hsi16Enable() {

	bits::set(RCC->CR, RCC_CR_HSION);
	while (!hsi16IsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge HSI
///
void htl::clock::hsi16Disable() {

	bits::clear(RCC->CR, RCC_CR_HSION);
	while (hsi16IsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::hsi16IsEnabled() {

    return bits::isSet(RCC->CR, RCC_CR_HSION);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge LSI
///
void htl::clock::lsiEnable() {

	bits::set(RCC->CR, RCC_CSR_LSION);
	while (!lsiIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge LSI
///
void htl::clock::lsiDisable() {

	bits::clear(RCC->CR, RCC_CSR_LSION);
	while (lsiIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge LSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::lsiIsEnabled() {

    return bits::isSet(RCC->CSR, RCC_CSR_LSION);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSE.
/// \param    bypass: El modus del bypass
///
void htl::clock::hseEnable(
	HseBypassMode bypass) {

	switch (bypass) {
		case HseBypassMode::on:
			bits::set(RCC->CR, RCC_CR_HSEBYP);
			break;

		case HseBypassMode::off:
			bits::clear(RCC->CR, RCC_CR_HSEBYP);
			break;

		default:
			break;
	}
	bits::set(RCC->CR, RCC_CR_HSEON);
	while (!hseIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge HSE.
///
void htl::clock::hseDisable() {

	bits::clear(RCC->CR, RCC_CR_HSEON);
	while (hseIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::hseIsEnabled() {

    return bits::isSet(RCC->CR, RCC_CR_HSERDY);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge LSE.
///
void htl::clock::lseEnable() {

	bits::set(RCC->BDCR, RCC_BDCR_LSEON);
	while (!lseIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge LSE.
///
void htl::clock::lseDisable() {

	bits::clear(RCC->BDCR, RCC_BDCR_LSEON);
	while (lseIsEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge LSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool htl::clock::lseIsEnabled() {

    return bits::isSet(RCC->BDCR, RCC_BDCR_LSERDY);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el PLL
///
void htl::clock::pllEnable() {

	bits::set(RCC->CR, RCC_CR_PLLON);
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el PLL
///
void htl::clock::pllDisable() {

	bits::clear(RCC->CR, RCC_CR_PLLON);
	while ((RCC->CR & RCC_CR_PLLRDY) != 0)
		continue;

	bits::clear(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN | RCC_PLLCFGR_PLLQEN | RCC_PLLCFGR_PLLREN);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el PLL esta activat.
/// \return   True si esta activat, false en cas contrari.
///
bool htl::clock::pllIsEnabled() {

    return (bits::isSet(RCC->CR, RCC_CR_PLLON) && bits::isSet(RCC->CR, RCC_CR_PLLRDY));
}


/// ----------------------------------------------------------------------
/// \brief    Configura el PLL.
/// \param    source: Rellotge font.
/// \param    multiplier: Factor de multiplicacio (N).
/// \param    divider: Factor de divisio (M).
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool htl::clock::pllConfigure(
	PllSource source,
	unsigned multiplier,
	unsigned divider) {

	if (divider < 1 || divider > 8 || multiplier < 8 || multiplier > 86)
		return false;

	if (clock::pllIsEnabled())
		return false;

    auto PLLCFGR = RCC->PLLCFGR;

	bits::clear(PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN);
	switch (source) {
		case PllSource::hsi16:
            if (!hsi16IsEnabled())
                return false;
			bits::set(PLLCFGR, (typeof(PLLCFGR)) (0b10 << RCC_PLLCFGR_PLLSRC_Pos));
			break;

		case PllSource::hse:
			if (!hseIsEnabled())
				return false;
			bits::set(PLLCFGR, (typeof(PLLCFGR)) (0b11 <<  RCC_PLLCFGR_PLLSRC_Pos));
			break;
	}
	bits::set(PLLCFGR, ((divider - 1) << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk);
	bits::set(PLLCFGR,  (multiplier << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk);

	RCC->PLLCFGR = PLLCFGR;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Configura la sortida P del PLL.
/// \param    divider: El valor del divisor.
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool htl::clock::pllSetPDivider(
	unsigned divider) {

	if (divider < 2 || divider > 32)
		return false;

	if (clock::pllIsEnabled())
		return false;

	uint32_t div = divider - 1;

	uint32_t tmp = RCC->PLLCFGR;
	tmp &= ~RCC_PLLCFGR_PLLP_Msk;
	tmp |= (div << RCC_PLLCFGR_PLLP_Pos) & RCC_PLLCFGR_PLLP_Msk;
	tmp |= RCC_PLLCFGR_PLLPEN;
	RCC->PLLCFGR = tmp;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Configura la sortida Q del PLL
/// \param    divider: El valor del divisor.
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool htl::clock::pllSetQDivider(
	unsigned divider) {

	if (divider < 2 || divider > 8)
		return false;

	if (clock::pllIsEnabled())
		return false;

	uint32_t div = divider - 1;

	uint32_t tmp = RCC->PLLCFGR;
	tmp &= ~RCC_PLLCFGR_PLLQ_Msk;
	tmp |= (div << RCC_PLLCFGR_PLLQ_Pos) & RCC_PLLCFGR_PLLQ_Msk;
	tmp |= RCC_PLLCFGR_PLLQEN;
	RCC->PLLCFGR = tmp;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Configura la sortida R del PLL
/// \param    divider: El valor del divisor.
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool htl::clock::pllSetRDivider(
	unsigned divider) {

	if (divider < 2 || divider > 8)
		return false;

	if (clock::pllIsEnabled())
		return false;

	uint32_t div = divider - 1;

	uint32_t tmp = RCC->PLLCFGR;
	tmp &= ~RCC_PLLCFGR_PLLR_Msk;
	tmp |= (div << RCC_PLLCFGR_PLLR_Pos) & RCC_PLLCFGR_PLLR_Msk;
	tmp |= RCC_PLLCFGR_PLLREN;
	RCC->PLLCFGR = tmp;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Configura les sortides MCO
/// \param    output: La sortida.
/// \param    source: El clock origen.
/// \param    divider: El divisor.
///
void htl::clock::mcoConfigure(
	clock::MCOOutput output,
	clock::MCOSource source,
	clock::MCODivider divider) {

	uint32_t src = 0b0000;
	switch (source) {
		case MCOSource::hse:
			src = 0b0100;
			break;

		case MCOSource::hsi16:
			src = 0b0011;
			break;

		case MCOSource::lsi:
			src = 0b0110;
			break;

		case MCOSource::lse:
			src = 0b0111;
			break;

		case MCOSource::sysclk:
			src = 0b0001;
			break;

		case MCOSource::pllrclk:
			src = 0b0101;
			break;

		default:
			break;
	}

	uint32_t div = uint32_t(divider);

	uint32_t tmp = RCC->CFGR;
	switch (output) {
		case MCOOutput::out1:
			tmp &= ~RCC_CFGR_MCOSEL_Msk;
			tmp |= (src << RCC_CFGR_MCOSEL_Pos) & RCC_CFGR_MCOSEL_Msk;
			tmp |= (div << RCC_CFGR_MCOPRE_Pos) & RCC_CFGR_MCOPRE_Msk;
			break;

		#ifdef EOS_PLATFORM_STM32G0B0
			case MCOOutput::out2:
				tmp &= ~RCC_CFGR_MCO2SEL_Msk;
				tmp |= (src << RCC_CFGR_MCO2SEL_Pos) & RCC_CFGR__MCO2PRE_Msk;
				tmp |= (div << RCC_CFGR_MCO2PRE_Pos) & RCC_CFGR_MCO2PRE_Msk;
				break;
		#endif

		default:
			break;
	}

	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned htl::clock::getClockFrequency(
	ClockID clockId) {

	static const uint8_t hsiDividerTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7};
	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

	unsigned fclk = 0;

	switch (clockId) {
		case ClockID::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS) {
				case RCC_CFGR_SWS_HSISYS:
					fclk = getClockFrequency(ClockID::hsisys);
					break;

				case RCC_CFGR_SWS_HSE:
					fclk = CLOCK_HSE_FREQUENCY;
					break;

				case RCC_CFGR_SWS_PLLRCLK:
					fclk = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == (0b10 << RCC_PLLCFGR_PLLSRC_Pos) ?
						 CLOCK_HSI16_FREQUENCY : CLOCK_HSE_FREQUENCY;
					fclk /= ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1;
					fclk *= (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
					fclk /= ((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos) + 1;
					break;

				case RCC_CFGR_SWS_LSI:
					fclk = CLOCK_LSI_FREQUENCY;
					break;

				case RCC_CFGR_SWS_LSE:
					fclk = CLOCK_LSE_FREQUENCY;
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
			fclk = CLOCK_HSE_FREQUENCY;
			break;

		case ClockID::hsi16:
			fclk = CLOCK_HSI16_FREQUENCY;
			break;

		case ClockID::hsi48:
			fclk = CLOCK_HSI48_FREQUENCY;
			break;

		case ClockID::lse:
			fclk = CLOCK_LSE_FREQUENCY;
			break;

		case ClockID::lsi:
			fclk = CLOCK_LSI_FREQUENCY;
			break;

		default:
			break;
	}

	return fclk;
}

