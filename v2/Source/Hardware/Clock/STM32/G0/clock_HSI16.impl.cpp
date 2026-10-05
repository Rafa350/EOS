module;


#include "HTL/htl.h"


module Eos.Hardware.Clock;


import Eos.Bits;
import Eos.Configuration.Platform;


using namespace eos;
using namespace eos::hardware::clock::internal;


static_assert(Platform::is_STM32_G0);



/// ---------------------------------------------------------------------------
/// \brief    Activa el oscilador HSI16
/// \param    kernelMode: Selecciona el modus kernel.
///
void HSI16Interface<true>::enableHSI16(
	bool kernelMode) const {

	Bits::set(RCC->CR, RCC_CR_HSION);
	while (!isHSI16Enabled())
		continue;

	if (kernelMode)
		Bits::set(RCC->CR, RCC_CR_HSIKERON);
	else
		Bits::clear(RCC->CR, RCC_CR_HSIKERON);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el oscilador HSI16
///
void HSI16Interface<true>::disableHSI16() const {

	Bits::clear(RCC->CR, RCC_CR_HSION);
	while (isHSI16Enabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el oscilador HSI16 esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool HSI16Interface<true>::isHSI16Enabled() const {

	return Bits::isSet(RCC->CR, RCC_CR_HSION);
}
