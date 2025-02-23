#pragma once
#ifndef __STM32_G0_htlI2C_AF_G051__
#define __STM32_G0_htlI2C_AF_G051__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G051)


#define ALT_FUNCTION(id, fn, pin, af)                 \
	template <>                                       \
	struct I2CPinFunctionID<DeviceID::_##id, fn, pin> { \
		static constexpr gpio::PinFunctionID alt = af;      \
	};


namespace htl {
	namespace i2c {
		namespace internal {

			#ifdef HTL_I2C1_EXIST
			ALT_FUNCTION(1, PinFunction::scl, gpio::PinA9,  gpio::PinFunctionID::_6)
			ALT_FUNCTION(1, PinFunction::scl, gpio::PinB6,  gpio::PinFunctionID::_6)
			ALT_FUNCTION(1, PinFunction::scl, gpio::PinB8,  gpio::PinFunctionID::_6)
			ALT_FUNCTION(1, PinFunction::scl, gpio::PinB10, gpio::PinFunctionID::_1)

			ALT_FUNCTION(1, PinFunction::sda, gpio::PinA10, gpio::PinFunctionID::_6)
			ALT_FUNCTION(1, PinFunction::sda, gpio::PinB7,  gpio::PinFunctionID::_6)
			ALT_FUNCTION(1, PinFunction::sda, gpio::PinB9,  gpio::PinFunctionID::_6)
			ALT_FUNCTION(1, PinFunction::sda, gpio::PinB11, gpio::PinFunctionID::_1)

			ALT_FUNCTION(1, PinFunction::alert, gpio::PinA1,  gpio::PinFunctionID::_6)
			ALT_FUNCTION(1, PinFunction::alert, gpio::PinB5,  gpio::PinFunctionID::_6)
			#endif // HTL_I2C1_EXIST

			#ifdef HTL_I2C2_EXIST
			ALT_FUNCTION(2, PinFunction::scl, gpio::PinA11, gpio::PinFunctionID::_6)
			ALT_FUNCTION(2, PinFunction::scl, gpio::PinB10, gpio::PinFunctionID::_6)
			ALT_FUNCTION(2, PinFunction::scl, gpio::PinB13, gpio::PinFunctionID::_6)

			ALT_FUNCTION(2, PinFunction::sda, gpio::PinA12, gpio::PinFunctionID::_6)
			ALT_FUNCTION(2, PinFunction::sda, gpio::PinB11, gpio::PinFunctionID::_6)
			ALT_FUNCTION(2, PinFunction::sda, gpio::PinB14, gpio::PinFunctionID::_6)
			#endif // HTL_I2C2_EXIST
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G051


#endif // __STM32_G0_htlI2C_AF_G051__
