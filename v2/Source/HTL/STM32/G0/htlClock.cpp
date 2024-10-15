#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"


#if !defined(EOS_PLATFORM_STM32G0)
	#error "Valid for STM32G0 platform only"
#endif


#define RCC_CFGR_SW_HSISYS        (0 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_HSE           (1 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_PLLRCLK       (2 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_LSI           (3 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_LSE           (4 << RCC_CFGR_SW_Pos)


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

		case SysClkSource::lsi:
			if (!isLsiEnabled())
				return false;
			tmp |= RCC_CFGR_SW_LSI;
			break;

		case SysClkSource::lse:
			if (!isLseEnabled())
				return false;
			tmp |= RCC_CFGR_SW_LSE;
			break;

		case SysClkSource::pllrclk:
            if (!isPllEnabled() || ((RCC->PLLCFGR & RCC_PLLCFGR_PLLREN_Msk) == 0))
                return false;
			tmp |= RCC_CFGR_SW_PLLRCLK;
			break;

		case SysClkSource::hsisys:
			tmp |= RCC_CFGR_SW_HSISYS;
			break;
	}

	RCC->CFGR = tmp;
	while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos) != ((RCC->CFGR & RCC_CFGR_SW_Msk) >> RCC_CFGR_SW_Pos))
		continue;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el divisor del rellotge HSISYS
/// \param    value: El valor del divisor.
///
void Clock::setHsisysPrescaler(
	HsisysPrescaler value) {

	uint32_t tmp = RCC->CR;
	tmp &= ~RCC_CR_HSIDIV;
	tmp |= ((uint32_t) value) << RCC_CR_HSIDIV_Pos;
	RCC->CR = tmp;
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
            tmp |= 0b0000 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_2:
            tmp |= 0b1000 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_4:
            tmp |= 0b1001 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_8:
            tmp |= 0b1010 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_16:
            tmp |= 0b1011 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_64:
            tmp |= 0b1100 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_128:
            tmp |= 0b1101 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_256:
            tmp |= 0b1110 << RCC_CFGR_HPRE_Pos;
            break;

        case HClkPrescaler::_512:
            tmp |= 0b1111 << RCC_CFGR_HPRE_Pos;
            break;
	}

	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el valor del divisor del rellotge PClk (APB)
/// \param    value: El valor.
///
void Clock::setPClkPrescaler(
	PClkPrescaler value) {

	static const uint32_t tbl[] = { 0b000, 0b100, 0b101, 0b110, 0b111 };

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_PPRE_Msk;
	tmp |= tbl[uint32_t(value)] << RCC_CFGR_PPRE_Pos;
	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge HSI
///
void Clock::hsi16Enable() {

	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSION) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge HSI
///
void Clock::hsi16Disable() {

	RCC->CR &= ~RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSION) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock::isHsi16Enabled() {

    return (RCC->CR & RCC_CR_HSION) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge LSI
///
void Clock::lsiEnable() {

	RCC->CR |= RCC_CSR_LSION;
	while ((RCC->CR & RCC_CSR_LSION) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge LSI
///
void Clock::lsiDisable() {

	RCC->CR &= ~RCC_CSR_LSION;
	while ((RCC->CR & RCC_CSR_LSION) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge LSI es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock::isLsiEnabled() {

    return (RCC->CSR & RCC_CSR_LSION) != 0;
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
/// \brief    Activa el rellotge LSE.
///
void Clock::lseEnable() {

	RCC->BDCR |= RCC_BDCR_LSEON;
	while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge LSE.
///
void Clock::lseDisable() {

	RCC->BDCR &= ~RCC_BDCR_LSEON;
	while ((RCC->BDCR & RCC_BDCR_LSERDY) != 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge LSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock::isLseEnabled() {

    return (RCC->BDCR & RCC_BDCR_LSERDY) != 0;
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

	uint32_t tmp = RCC->PLLCFGR;
	tmp &= ~RCC_PLLCFGR_PLLPEN;
	tmp &= ~RCC_PLLCFGR_PLLQEN;
	tmp &= ~RCC_PLLCFGR_PLLREN;
	RCC->PLLCFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el PLL esta activat.
/// \return   True si esta activat, false en cas contrari.
///
bool Clock::isPllEnabled() {

    return ((RCC->CR & RCC_CR_PLLON) != 0) && ((RCC->CR & RCC_CR_PLLRDY) != 0);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el PLL.
/// \param    source: Rellotge font.
/// \param    multiplier: Factor de multiplicacio (N).
/// \param    divider: Factor de divisio (M).
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool Clock::configurePll(
	PllSource source,
	unsigned multiplier,
	unsigned divider) {

	if (divider < 1 || divider > 8 || multiplier < 8 || multiplier > 86)
		return false;

	if (isPllEnabled())
		return false;

    uint32_t tmp = RCC->PLLCFGR;

	tmp &= ~RCC_PLLCFGR_PLLSRC_Msk;
	switch (source) {
		case PllSource::hsi16:
            if (!isHsi16Enabled())
                return false;
			tmp |= 0b10 << RCC_PLLCFGR_PLLSRC_Pos;
			break;

		case PllSource::hse:
			if (!isHseEnabled())
				return false;
			tmp |= 0b11 << RCC_PLLCFGR_PLLSRC_Pos;
			break;
	}

	tmp &= ~RCC_PLLCFGR_PLLM_Msk;
	tmp &= ~RCC_PLLCFGR_PLLN_Msk;
	tmp |= ((divider - 1) << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk;
	tmp |= (multiplier << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk;

	RCC->PLLCFGR = tmp;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Configura la sortida P del PLL.
/// \param    divider: El valor del divisor.
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool Clock::configurePllP(
	unsigned divider) {

	if (divider < 2 || divider > 32)
		return false;

	if (isPllEnabled())
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
bool Clock::configurePllQ(
	unsigned divider) {

	if (divider < 2 || divider > 8)
		return false;

	if (isPllEnabled())
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
bool Clock::configurePllR(
	unsigned divider) {

	if (divider < 2 || divider > 8)
		return false;

	if (isPllEnabled())
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
void Clock::configureMCO(
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
		case MCOOutput::_1:
			tmp &= ~RCC_CFGR_MCOSEL_Msk;
			tmp |= (src << RCC_CFGR_MCOSEL_Pos) & RCC_CFGR_MCOSEL_Msk;
			tmp |= (div << RCC_CFGR_MCOPRE_Pos) & RCC_CFGR_MCOPRE_Msk;
			break;

		#ifdef EOS_PLATFORM_STM32G0B0
			case MCOOutput::_2:
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
unsigned Clock::getClockFrequency(
	ClockID clockId) {

	static const uint8_t hsiDividerTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7};
	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

	unsigned fclk = 0;

	switch (clockId) {
		case ClockID::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS_Msk) {
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
