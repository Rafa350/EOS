module;

#include "hardware.h"


module Eos.Hardware.Clock;


import Eos.Bits;
import Eos.Platform;


using namespace eos;
using namespace eos::hardware::clock::internal;


static_assert(platformCheck("STM32F4xxxx"));



/// ---------------------------------------------------------------------------
/// \brief    Activa el oscilador HSI
/// \param    kernelMode: Selecciona el modus kernel.
///
void Clock_HSI<true>::enableHSI() {

	Bits::set(RCC->CR, RCC_CR_HSION);
	while (!isHSIEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el oscilador HSI
///
void Clock_HSI<true>::disableHSI() {

	Bits::clear(RCC->CR, RCC_CR_HSION);
	while (isHSIEnabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el oscilador HSI esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock_HSI<true>::isHSIEnabled() {

	return Bits::isSet(RCC->CR, RCC_CR_HSION);
}
