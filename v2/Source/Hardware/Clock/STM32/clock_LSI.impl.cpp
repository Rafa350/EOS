module;


#include "hardware.h"


module Eos.Hardware.Clock;


import Eos.Bits;


using namespace eos;
using namespace eos::hardware::clock;


/// ---------------------------------------------------------------------------
/// @brief    Activa el oscilador LSI
///
void Clock::enableLSI() const {

	Bits::set(RCC->CR, RCC_CSR_LSION);
	while (!isLSIEnabled())
		continue;
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el oscilador LSI
///
void Clock::disableLSI() const {

	Bits::clear(RCC->CR, RCC_CSR_LSION);
	while (isLSIEnabled())
		continue;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el oscilador LSI esta actiu.
/// @return   True si esta actiu, false en cas contrari.
///
bool Clock::isLSIEnabled() const {

	return Bits::isSet(RCC->CSR, RCC_CSR_LSION);
}
