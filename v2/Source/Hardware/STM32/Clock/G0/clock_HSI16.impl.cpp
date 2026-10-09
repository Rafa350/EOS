module;


#include "hardware.h"


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
void Clock_HSI16<true>::enableHSI16(
	bool kernelMode) {

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
void Clock_HSI16<true>::disableHSI16() {

	Bits::clear(RCC->CR, RCC_CR_HSION);
	while (isHSI16Enabled())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el oscilador HSI16 esta actiu.
/// \return   True si esta actiu, false en cas contrari.
///
bool Clock_HSI16<true>::isHSI16Enabled() {

	return Bits::isSet(RCC->CR, RCC_CR_HSION);
}
