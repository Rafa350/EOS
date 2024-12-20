#pragma once
#ifndef __STM32G071_htlI2C_Pins__
#define __STM32G071_htlI2C_Pins__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32G071)
	#error "Valid for STM32G071 platform only"
#endif


#define ALT_FUNCTION(id, fn, pin, af)                 \
	template <>                                       \
	struct PinFunctionInfo<id, fn, pin> { \
		static constexpr gpio::AlternateFunction alt = af;      \
	};


namespace htl {
	namespace i2c {
		namespace internal {

			#ifdef HTL_I2C1_EXIST
			ALT_FUNCTION(DeviceID::_1, PinFunction::scl,  gpio::PinA9,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::scl,  gpio::PinB6,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::scl,  gpio::PinB8,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::scl,  gpio::PinB10, gpio::AlternateFunction::_1)
			ALT_FUNCTION(DeviceID::_1, PinFunction::sda,  gpio::PinA10, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::sda,  gpio::PinB7,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::sda,  gpio::PinB9,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::sda,  gpio::PinB11, gpio::AlternateFunction::_1)
			ALT_FUNCTION(DeviceID::_1, PinFunction::smba, gpio::PinA1,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::smba, gpio::PinB5,  gpio::AlternateFunction::_6)
			#endif // HTL_I2C1_EXIST

			#ifdef HTL_I2C2_EXIST
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl, gpio::PinA11, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl, gpio::PinB10, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl, gpio::PinB13, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda, gpio::PinA12, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda, gpio::PinB11, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda, gpio::PinB14, gpio::AlternateFunction::_6)
			#endif // HTL_I2C2_EXIST
		}
	}
}


#undef ALT_FUNCTION


#endif // __STM32G071_htlI2C_Pins__
