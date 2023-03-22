#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"


#if !defined(EOS_PLATFORM_STM32G0)
	#error Solo es valido para la plataforma STM32G0
#endif


#define RCC_CFGR_SW_HSISYS        (0 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_HSE           (1 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_PLLRCLK       (2 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_LSI           (3 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_LSE           (4 << RCC_CFGR_SW_Pos)


using namespace htl;


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
		#ifdef CLOCK_HSE_FREQUENCY
			case SysClkSource::hse:
				if (!isHseEnabled())
					return false;
				tmp |= RCC_CFGR_SW_HSE;
				break;
		#endif

		case SysClkSource::lsi:
			if (!isLsiEnabled())
				return false;
			tmp |= RCC_CFGR_SW_LSI;
			break;

		#ifdef CLOCK_LSE_FREQUENCY
			case SysClkSource::lse:
				if (!isLseEnabled())
					return false;
				tmp |= RCC_CFGR_SW_LSE;
				break;
		#endif

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
	while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> 2) != (RCC->CFGR & RCC_CFGR_SW_Msk))
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
	tmp  |= ((uint32_t) value) << RCC_CR_HSIDIV_Pos;
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

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_PPRE_Msk;
	switch (value) {
        case PClkPrescaler::_1:
            tmp |= 0b000 << RCC_CFGR_PPRE_Pos;
            break;

        case PClkPrescaler::_2:
            tmp |= 0b100 << RCC_CFGR_PPRE_Pos;
            break;

        case PClkPrescaler::_4:
            tmp |= 0b101 << RCC_CFGR_PPRE_Pos;
            break;

        case PClkPrescaler::_8:
            tmp |= 0b110 << RCC_CFGR_PPRE_Pos;
            break;

        case PClkPrescaler::_16:
            tmp |= 0b111 << RCC_CFGR_PPRE_Pos;
            break;
	}

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
#ifdef CLOCK_HSE_FREQUENCY
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
#endif


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge HSE.
///
#ifdef CLOCK_HSE_FREQUENCY
void Clock::hseDisable() {
    
	RCC->CR &= ~RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) != 0)
		continue;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge HSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
#ifdef CLOCK_HSE_FREQUENCY
bool Clock::isHseEnabled() {
    
    return (RCC->CR & RCC_CR_HSERDY) != 0;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge LSE.
///
#ifdef CLOCK_LSE_FREQUENCY
void Clock::lseEnable() {

	RCC->BDCR |= RCC_BDCR_LSEON;
	while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0)
		continue;
}
#endif


/// ----------------------------------------------------------------------
/// \brief   Desactiva el rellotge LSE.
///
#ifdef CLOCK_LSE_FREQUENCY
void Clock::lseDisable() {
    
	RCC->BDCR &= ~RCC_BDCR_LSEON;
	while ((RCC->BDCR & RCC_BDCR_LSERDY) != 0)
		continue;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Comprova si el rellotge LSE es actiu.
/// \return   True si esta actiu, false en cas contrari.
///
#ifdef CLOCK_LSE_FREQUENCY
bool Clock::isLseEnabled() {
    
    return (RCC->BDCR & RCC_BDCR_LSERDY) != 0;
}
#endif


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
/// \param    multiplier: Factor de multiplicacio.
/// \param    divider: Factor de divisio.
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool Clock::configurePll(
	PllSource source,
	int multiplier,
	int divider) {

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

		#ifdef CLOCK_HSE_FREQUENCY
			case PllSource::hse:
				if (!isHseEnabled())
					return false;
				tmp |= 0b11 << RCC_PLLCFGR_PLLSRC_Pos;
				break;
		#endif
	}

	tmp &= ~RCC_PLLCFGR_PLLM_Msk;
	tmp &= ~RCC_PLLCFGR_PLLN_Msk;
	tmp |= (divider - 1) << RCC_PLLCFGR_PLLM_Pos;
	tmp |= multiplier << RCC_PLLCFGR_PLLN_Pos;

	RCC->PLLCFGR = tmp;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Configura la sortida P del PLL.
/// \param    divider: El valor del divisor.
/// \return   True si s'ha realitzat l'operacio correctament.
///
bool Clock::configurePllP(
	int divider) {

	if (divider < 2 || divider > 32)
		return false;

	if (isPllEnabled())
		return false;

	uint32_t tmp = RCC->PLLCFGR;
	tmp &= ~RCC_PLLCFGR_PLLP_Msk;
	tmp |= (divider - 1) << RCC_PLLCFGR_PLLP_Pos;
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
	int divider) {

	if (divider < 2 || divider > 8)
		return false;

	if (isPllEnabled())
		return false;

	uint32_t tmp = RCC->PLLCFGR;
	tmp &= ~RCC_PLLCFGR_PLLQ_Msk;
	tmp |= (divider - 1) << RCC_PLLCFGR_PLLQ_Pos;
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
	int divider) {

	if (divider < 2 || divider > 8)
		return false;

	if (isPllEnabled())
		return false;

	uint32_t tmp = RCC->PLLCFGR;
	tmp &= ~RCC_PLLCFGR_PLLR_Msk;
	tmp |= (divider - 1) << RCC_PLLCFGR_PLLR_Pos;
	tmp |= RCC_PLLCFGR_PLLREN;
	RCC->PLLCFGR = tmp;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned Clock::getClockFrequency(
	ClockId clockId) {

	static const uint8_t hsiDividerTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7};
	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

	unsigned fclk = 0;

	switch (clockId) {
		case ClockId::sysclk:
			switch (RCC->CFGR & RCC_CFGR_SWS_Msk) {
				case RCC_CFGR_SW_HSISYS:
					fclk = getClockFrequency(ClockId::hsisys);
					break;

				#ifdef CLOCK_HSE_FREQUENCY
					case RCC_CFGR_SW_HSE:
						fclk = CLOCK_HSE_FREQUENCY;
						break;
				#endif

				case RCC_CFGR_SW_PLLRCLK:
					fclk = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == (0b10 << RCC_PLLCFGR_PLLSRC_Pos) ?
						 CLOCK_HSI16_FREQUENCY : CLOCK_HSE_FREQUENCY;
					fclk *= (RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos;
					fclk /= (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
					fclk /=
					break;

				case RCC_CFGR_SW_LSI:
					fclk = CLOCK_LSI_FREQUENCY;
					break;

				#ifdef CLOCK_LSE_FREQUENCY
					case RCC_CFGR_SW_LSE:
						fclk = CLOCK_LSE_FREQUENCY;
						break;
				#endif
			}
			break;

		case ClockId::pclk:
			fclk = getClockFrequency(ClockId::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE_Msk) >> RCC_CFGR_PPRE_Pos];
			break;

		case ClockId::hclk:
			fclk = getClockFrequency(ClockId::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
			break;

		case ClockId::hclk8:
			fclk = getClockFrequency(ClockId::hclk) / 8;
			break;

		case ClockId::hsisys:
			fclk = CLOCK_HSI16_FREQUENCY >> hsiDividerTbl[(RCC->CR & RCC_CR_HSIDIV_Msk) >> RCC_CR_HSIDIV_Pos];
			break;

		#ifdef CLOCK_HSE_FREQUENCY
			case ClockId::hse:
				fclk = CLOCK_HSE_FREQUENCY;
				break;
		#endif

		case ClockId::hsi16:
			fclk = CLOCK_HSI16_FREQUENCY;
			break;

		case ClockId::hsi48:
			fclk = CLOCK_HSI48_FREQUENCY;
			break;

		#ifdef CLOCK_LSE_FREQUENCY
			case ClockId::lse:
				fclk = CLOCK_LSE_FREQUENCY;
				break;
		#endif

		case ClockId::lsi:
			fclk = CLOCK_LSI_FREQUENCY;
			break;

		default:
			break;
	}

	return fclk;
}
