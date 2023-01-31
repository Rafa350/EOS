#include "HTL/htl.h"
#include "HTL/STM32/htlClock.h"


using namespace htl;


bool Clock::_updated = false;
SysClkSource Clock::_sysClkSource;
PClkPrescaler Clock::_pclkPrescaler;
HClkPrescaler Clock::_hclkPrescaler;
PllSource Clock::_pllSource;
PllMultiplier Clock::_pllMultiplier;
PllHseDivider Clock::_pllHseDivider;


/// ----------------------------------------------------------------------
/// \brief    Asigna l'origen del rellotge del sistema.
/// \param    value: El valor.
///
void Clock::setSysClkSource(
	SysClkSource value) {

	if (_sysClkSource != value) {
		_sysClkSource = value;
		_updated = false;
	}
}


void Clock::setHClkPrescaler(
	HClkPrescaler value) {

	if (_hclkPrescaler != value) {
		_hclkPrescaler = value;
		_updated = false;
	}
}


void Clock::setPClkPrescaler(
	PClkPrescaler value) {

	if (_pclkPrescaler != value) {
		_pclkPrescaler = value;
		_updated = false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el rellotge SysClk
/// \param    source: L'origen.
/// \return   True si tot es correcte, false en cas contrari.
///
bool Clock::sysClkSource(
	SysClkSource source) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_SW_Msk;
	switch (source) {
		case SysClkSource::hse:
			tmp |= RCC_CFGR_SW_HSE;
			break;

		case SysClkSource::hsi:
			tmp |= RCC_CFGR_SW_HSI;
			break;

		case SysClkSource::pll:
			tmp |= RCC_CFGR_SW_PLL;
			break;
	}

	RCC->CFGR = tmp;
	while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> 2) != (RCC->CFGR & RCC_CFGR_SW_Msk))
		continue;

	return true;
}


void Clock::HClkPrescaler(
	HClkPrescaler value) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_HPRE_Msk;
	switch (value) {

	}

	RCC->CFGR = tmp;
}


void Clock::PClkPrescaler(
	PClkPrescaler value) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_PPRE_Msk;
	switch (value) {

	}

	RCC->CFGR = tmp;
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
/// \brief    Selecciona el rellotge d'entrada del PLL.
/// \param    value: El valor.
///
void Clock::pllSource(
	PllSource value) {

	uint32_t tmp = RCC->CFGR;

	tmp &= ~RCC_CFGR_PLLSRC_Msk;
	switch (value) {
		case PllSource::hsi:
			tmp |= RCC_CFGR_PLLSRC_HSI_DIV2;
			break;

		case PllSource::hse:
			tmp |= RCC_CFGR_PLLSRC_HSE_PREDIV;
			break;
	}

	RCC->CFGR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor del divisor de la entrada HSE del PLL.
/// \param    value: El valor.
///
void Clock::pllHseDivider(
	PllHseDivider value) {

	uint_32_t tmp = RCC->CFGR2;

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
void Clock::pllMultiplier(
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
/// \brief    Asigna l'origen del rellotge del PLL.
/// \param    vaslue: El vaslor.
///
void Clock::setPllSource(
	PllSource value) {

	if (_pllSource != value) {
		_pllSource = value;
		_updated = false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el divisor per rellotge HSE d'entrada al PLL.
/// \param    value: El valor.
///
void Clock::setPllHseDivider(
	PllHseDivider value) {

	if (_pllHseDivider != value) {
		_pllHseDivider = value;
		_updated = false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Assigna el multiplicador del PLL.
/// \param    value: El valor.
///
void Clock::setPllMultiplier(
	PllMultiplier value) {

	if (_pllMultiplier != value) {
		_pllMultiplier = value;
		_updated = false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Reseteja el rellotge als valor basics de funcionament.
///
void Clock::reset() {

}


/// ----------------------------------------------------------------------
/// \brief    Actualitza el rellotge amb els nous parametres.
/// \return   True si tot es correcte, false en cas contrari.
///
bool Clock::update() {

	static const uint32_t pllSource[] = {
		RCC_CFGR_PLLSRC_HSI_DIV2,
		RCC_CFGR_PLLSRC_HSE_PREDIV
	};

	static const uint32_t pllMultiplier[] = {
		RCC_CFGR_PLLMUL2,
		RCC_CFGR_PLLMUL3,
		RCC_CFGR_PLLMUL4,
		RCC_CFGR_PLLMUL5,
		RCC_CFGR_PLLMUL6,
		RCC_CFGR_PLLMUL7,
		RCC_CFGR_PLLMUL8,
		RCC_CFGR_PLLMUL9,
		RCC_CFGR_PLLMUL10,
		RCC_CFGR_PLLMUL11,
		RCC_CFGR_PLLMUL12,
		RCC_CFGR_PLLMUL13,
		RCC_CFGR_PLLMUL14,
		RCC_CFGR_PLLMUL15,
		RCC_CFGR_PLLMUL16
	};

	static const uint32_t pllHseDivider[] = {
		RCC_CFGR2_PREDIV_DIV1,
		RCC_CFGR2_PREDIV_DIV2,
		RCC_CFGR2_PREDIV_DIV3,
		RCC_CFGR2_PREDIV_DIV4,
		RCC_CFGR2_PREDIV_DIV5,
		RCC_CFGR2_PREDIV_DIV6,
		RCC_CFGR2_PREDIV_DIV7,
		RCC_CFGR2_PREDIV_DIV8,
		RCC_CFGR2_PREDIV_DIV9,
		RCC_CFGR2_PREDIV_DIV10,
		RCC_CFGR2_PREDIV_DIV11,
		RCC_CFGR2_PREDIV_DIV12,
		RCC_CFGR2_PREDIV_DIV13,
		RCC_CFGR2_PREDIV_DIV14,
		RCC_CFGR2_PREDIV_DIV15,
		RCC_CFGR2_PREDIV_DIV16
	};

	static const uint32_t hclkPrescaler[] = {
		RCC_CFGR_HPRE_DIV1,
		RCC_CFGR_HPRE_DIV2,
		RCC_CFGR_HPRE_DIV4,
		RCC_CFGR_HPRE_DIV8,
		RCC_CFGR_HPRE_DIV16,
		RCC_CFGR_HPRE_DIV64,
		RCC_CFGR_HPRE_DIV128,
		RCC_CFGR_HPRE_DIV256,
		RCC_CFGR_HPRE_DIV512
	};

	static const uint32_t pclkPrescaler[] = {
		RCC_CFGR_PPRE_DIV1,
		RCC_CFGR_PPRE_DIV2,
		RCC_CFGR_PPRE_DIV4,
		RCC_CFGR_PPRE_DIV8,
		RCC_CFGR_PPRE_DIV16
	};

	if (!_updated) {

		uint32_t tmp;

		// Desactiva el PLL
		//
		RCC->CR &= ~RCC_CR_PLLON;
		while ((RCC->CR & RCC_CR_PLLRDY) != 0)
			continue;

		// Configura el PLL si cal
		//
		if (_sysClkSource == SysClkSource::pll) {

			// Configura el PLL
			//
			tmp = RCC->CFGR;
			tmp &= ~RCC_CFGR_PLLMUL_Msk;
			tmp |= pllMultiplier[(uint8_t)_pllMultiplier];
			tmp &= ~RCC_CFGR_PLLSRC_Msk;
			tmp |= pllSource[(uint8_t) _pllSource];
			RCC->CFGR = tmp;

			// Selecciona el divisor HSE del PLL
			//
			if (_pllSource == PllSource::hse) {
				tmp = RCC->CFGR2;
				tmp &= ~RCC_CFGR2_PREDIV_Msk;
				tmp |= pllHseDivider[(uint32_t) _pllHseDivider];
				RCC->CFGR2 = tmp;
			}

			// Activa el PLL
			//
			RCC->CR |= RCC_CR_PLLON;
			while ((RCC->CR & RCC_CR_PLLRDY) == 0)
				continue;
		}

		// Selecciona el rellotge del sistema
		//
		tmp = RCC->CFGR;
		tmp &= ~RCC_CFGR_SW_Msk;
		switch (_sysClkSource) {
			case SysClkSource::hse:
				tmp |= RCC_CFGR_SW_HSE;
				break;

			case SysClkSource::hsi:
				tmp |= RCC_CFGR_SW_HSI;
				break;

			case SysClkSource::pll:
				tmp |= RCC_CFGR_SW_PLL;
				break;
		}
		RCC->CFGR = tmp;

		// Espera que es realitzi el canvi
		//
		while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> 2) != (RCC->CFGR & RCC_CFGR_SW_Msk))
			continue;

		// Selecciona el divisor del rellotge PCLK i del HCLK
		//
		tmp = RCC->CFGR;
		tmp &= ~RCC_CFGR_HPRE_Msk;
		tmp |= hclkPrescaler[(uint32_t) _hclkPrescaler];
		tmp &= ~RCC_CFGR_PPRE_Msk;
		tmp |= pclkPrescaler[(uint32_t) _pclkPrescaler];
		RCC->CFGR = tmp;

		_updated = true;

		SystemCoreClockUpdate();
	}

	return _updated;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia d'un rellotge.
/// \param    clockId: Identificador del rellotge.
/// \return   La frequencia en hz, o zero en cas d'error.
///
unsigned Clock::getClockFrequency(
	ClockId clockId) {

	static const uint8_t pclkPrescalerTbl[8] = { 0, 0, 0, 0, 1, 2, 3, 4};
	static const uint8_t hclkPrescalerTbl[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
	static const uint8_t pllMultiplierTbl[16] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	static const uint8_t pllHseDividerTbl[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	unsigned fclk = 0;

	switch (clockId) {
		case ClockId::sysclk:
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

		case ClockId::pclk:
			fclk = getClockFrequency(ClockId::hclk) >> pclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_PPRE_Msk) >> RCC_CFGR_PPRE_Pos];
			break;

		case ClockId::hclk:
			fclk = getClockFrequency(ClockId::sysclk) >> hclkPrescalerTbl[(RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos];
			break;

		case ClockId::hse:
			fclk = CLOCK_HSE_FREQUENCY;
			break;

		case ClockId::hsi:
			fclk = CLOCK_HSI_FREQUENCY;
			break;

		case ClockId::hsi14:
			fclk = CLOCK_HSI14_FREQUENCY;
			break;

		case ClockId::lse:
			fclk = CLOCK_LSE_FREQUENCY;
			break;

		case ClockId::lsi:
			fclk = CLOCK_LSI_FREQUENCY;
			break;
	}

	return fclk;
}
