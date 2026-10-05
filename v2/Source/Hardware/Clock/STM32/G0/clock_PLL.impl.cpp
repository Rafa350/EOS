module;


#include "HTL/htl.h"


module Eos.Hardware.Clock;


import Eos.Bits;


using namespace eos;
using namespace eos::hardware::clock;


static_assert(Platform::is_STM32_G0);


/// ---------------------------------------------------------------------------
/// @brief    Activa el PLL
///
void Clock::enablePLL() const {

	Bits::set(RCC->CR, RCC_CR_PLLON);
	while (!Bits::isSet(RCC->CR, RCC_CR_PLLRDY))
		continue;
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el PLL
///
void Clock::disablePLL() const {

	Bits::clear(RCC->CR, RCC_CR_PLLON);
	while (Bits::isSet(RCC->CR, RCC_CR_PLLRDY))
		continue;

	Bits::clear(RCC->PLLCFGR,
			RCC_PLLCFGR_PLLPEN | RCC_PLLCFGR_PLLQEN |
			RCC_PLLCFGR_PLLREN | RCC_PLLCFGR_PLLSRC);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el PLL esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock::isPLLEnabled() const {

    return (Bits::isSet(RCC->CR, RCC_CR_PLLON) &&
    		Bits::isSet(RCC->CR, RCC_CR_PLLRDY));
}


/// ---------------------------------------------------------------------------
/// \brief    Configura el PLL
/// \param    sorce: El rellotge.
/// \param    multiplier: Factor de multiplicacio (N)
/// \param    divider: Factor de divisio (M)
/// \param    divP: Factor de divisio de la sortida P
/// \param    divQ: Factor de divisio de la sortida Q
/// \param    divR: Factor de divisio de la sortida R
/// \return   True si tot es correcte, false en cas contrari.
///
bool Clock::configurePLL(
		PLLsource source,
		UInt32 multiplier,
		UInt32 divider,
		PLLPdivider divP,
		PLLQdivider divQ,
		PLLRdivider divR) const {

	if (divider < 1 || divider > 8 || multiplier < 8 || multiplier > 86)
		return false;

	if (isPLLEnabled())
		return false;

    auto PLLCFGR = RCC->PLLCFGR;

    Bits::clear(PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN);
	switch (source) {
		case PLLsource::hsi16:
            if (!isHSI16Enabled())
                return false;
            Bits::set(PLLCFGR, RCC_PLLCFGR_PLLSRC_HSI);
			break;

		case PLLsource::hse:
			if (!isHSEEnabled())
				return false;
			Bits::set(PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);
			break;
	}
	Bits::set(PLLCFGR, ((divider - 1) << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk);
	Bits::set(PLLCFGR,  (multiplier << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk);

	// Configura el divisor P
	//
	if (divP == PLLPdivider::disabled)
		Bits::clear(PLLCFGR, RCC_PLLCFGR_PLLPEN);
	else {
		Bits::clear(PLLCFGR, RCC_PLLCFGR_PLLP);
		Bits::set(PLLCFGR, ((1 + (uint32_t) divP) << RCC_PLLCFGR_PLLP_Pos) & RCC_PLLCFGR_PLLP);
		Bits::set(PLLCFGR, RCC_PLLCFGR_PLLPEN);
	}

	// Configura el divisor Q
	//
	if (divQ == PLLQdivider::disabled)
		Bits::clear(PLLCFGR, RCC_PLLCFGR_PLLQEN);
	else {
		Bits::clear(PLLCFGR, RCC_PLLCFGR_PLLQ);
		Bits::set(PLLCFGR, ((1 + (uint32_t) divQ) << RCC_PLLCFGR_PLLQ_Pos) & RCC_PLLCFGR_PLLQ);
		Bits::set(PLLCFGR, RCC_PLLCFGR_PLLQEN);
	}

	// Configura el divisor R
	//
	if (divR == PLLRdivider::disabled)
		Bits::clear(PLLCFGR, RCC_PLLCFGR_PLLREN);
	else {
		Bits::clear(PLLCFGR, RCC_PLLCFGR_PLLR);
		Bits::set(PLLCFGR, ((1 + (uint32_t) divR) << RCC_PLLCFGR_PLLR_Pos) & RCC_PLLCFGR_PLLR);
		Bits::set(PLLCFGR, RCC_PLLCFGR_PLLREN);
	}

	RCC->PLLCFGR = PLLCFGR;

	return true;
}
