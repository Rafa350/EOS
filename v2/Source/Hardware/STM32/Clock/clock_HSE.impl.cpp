module;


#include "hardware.h"


module Eos.Hardware.Clock;


import Eos.Bits;


using namespace eos;
using namespace eos::hardware::clock;


/// ---------------------------------------------------------------------------
/// @brief    Activa el oscilador HSE
/// @param    bypass: Indica si utilitza un rellotge extern
///
void Clock::enableHSE(
	HSEBypass bypass) {

	if (bypass == HSEBypass::enabled)
		Bits::set(RCC->CR, RCC_CR_HSEBYP);
	else
		Bits::clear(RCC->CR, RCC_CR_HSEBYP);

	Bits::set(RCC->CR, RCC_CR_HSEON);
	while (!isHSEEnabled())
		continue;
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el oscilador HSE
///
void Clock::disableHSE() {

	Bits::clear(RCC->CR, RCC_CR_HSEON);
	while (isHSEEnabled())
		continue;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el oscilador HSE esta actiu.
/// @return   True si esta actiu, false en cas contrari.
///
bool Clock::isHSEEnabled() {

    return (RCC->CR & RCC_CR_HSERDY) != 0;
}
