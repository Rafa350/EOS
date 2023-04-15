#pragma once
#ifndef __STM32_htlI2C_AF_G031__
#define __STM32_htlI2C_AF_G031__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G031)


#define DECLARE_ALT_FUNCTION(id, fn, pin, af)  \
	template <>                                \
	struct I2CAltFunction<DeviceID::_##id, fn, pin> {       \
		static constexpr gpio::GPIOAlt alt = af;     \
	};

namespace htl {
	namespace i2c {
		namespace internal {

			#ifdef HTL_I2C1_EXIST
			DECLARE_ALT_FUNCTION(1, PinFunction::scl, gpio::PinA9,  gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(1, PinFunction::sda, gpio::PinA10, gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(1, PinFunction::scl, gpio::PinB6,  gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(1, PinFunction::sda, gpio::PinB7,  gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(1, PinFunction::scl, gpio::PinB8,  gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(1, PinFunction::sda, gpio::PinB9,  gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(1, PinFunction::scl, gpio::PinB10, gpio::GPIOAlt::_1)
			DECLARE_ALT_FUNCTION(1, PinFunction::sda, gpio::PinB11, gpio::GPIOAlt::_1)
			#endif // HTL_I2C1_EXIST

			#ifdef HTL_I2C2_EXIST
			DECLARE_ALT_FUNCTION(2, PinFunction::scl, gpio::PinA11, gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(2, PinFunction::sda, gpio::PinA12, gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(2, PinFunction::scl, gpio::PinB10, gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(2, PinFunction::sda, gpio::PinB11, gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(2, PinFunction::scl, gpio::PinB13, gpio::GPIOAlt::_6)
			DECLARE_ALT_FUNCTION(2, PinFunction::sda, gpio::PinB14, gpio::GPIOAlt::_6)
			#endif // HTL_I2C2_EXIST
		}
	}
}


#undef DECLARE_ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_htlI2C_AF_G031__
