module;


#include "HTL/htl.h"


module Eos.Hardware.Clock;


import Eos.Bits;


using namespace eos;
using namespace eos::hardware::clock;



/// ---------------------------------------------------------------------------
/// @brief    Activa el oscilador LSE
///
void Clock::enableLSE() const {

	Bits::set(RCC->BDCR, RCC_BDCR_LSEON);
	while (!isLSEEnabled())
		continue;
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el oscilador LSE
///
void Clock::disableLSE() const {

	Bits::clear(RCC->BDCR, RCC_BDCR_LSEON);
	while (isLSEEnabled())
		continue;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el oscilador LSE esta actiu.
/// @return   True si esta actiu, false en cas contrari.
///
bool Clock::isLSEEnabled() const {

	return Bits::isSet(RCC->BDCR, RCC_BDCR_LSERDY);
}
