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

	static const uint32_t hclkPrescalerFactor[] = { 1, 2, 4, 8, 16, 64, 128, 256, 512 };
	static const uint32_t pclkPrescalerFactor[] = { 1, 2, 4, 8, 16 };
	static const uint32_t pllMultiplierFactor[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	static const uint32_t pllHseDividerFactor[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	unsigned fclk = 0;

	if (_updated)
		switch (clockId) {
			case ClockId::sysclk:
				switch (_sysClkSource) {
					case SysClkSource::hse:
						fclk = CLOCK_HSE_FREQUENCY;
						break;

					case SysClkSource::hsi:
						fclk = CLOCK_HSI_FREQUENCY;
						break;

					case SysClkSource::pll:
						fclk = (_pllSource == PllSource::hsi ?
							CLOCK_HSI_FREQUENCY / 2 :
							CLOCK_HSE_FREQUENCY / pllHseDividerFactor[(uint32_t) _pllHseDivider]) *
								pllMultiplierFactor[(uint32_t) _pllMultiplier];
						break;
				}
				break;

			case ClockId::pclk:
				fclk = getClockFrequency(ClockId::hclk) / pclkPrescalerFactor[(uint32_t) _pclkPrescaler];
				break;

			case ClockId::hclk:
				fclk = getClockFrequency(ClockId::sysclk) / hclkPrescalerFactor[(uint32_t) _hclkPrescaler];
				break;

			case ClockId::hse:
				fclk = CLOCK_HSE_FREQUENCY;
				break;

			case ClockId::hsi:
				fclk = CLOCK_HSI_FREQUENCY;
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
