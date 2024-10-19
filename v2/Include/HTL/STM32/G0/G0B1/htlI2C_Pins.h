#pragma once
#ifndef __STM32G0B1_htlI2C_Pins__
#define __STM32G0B1_htlI2C_Pins__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G0B1)


#define ALT_FUNCTION(id, fn, pin, af)                 \
	template <>                                       \
	struct PinFunctionInfo<id, fn, pin> { \
		static constexpr gpio::AlternateFunction alt = af;      \
	};


namespace htl {
	namespace i2c {
		namespace internal {

			#ifdef HTL_I2C1_EXIST
			ALT_FUNCTION(DeviceID::_1, PinFunction::scl,   gpio::PinA9,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::scl,   gpio::PinB6,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::scl,   gpio::PinB8,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::sda,   gpio::PinA10, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::sda,   gpio::PinB7,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::sda,   gpio::PinB9,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::alert, gpio::PinA1,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::alert, gpio::PinB5,  gpio::AlternateFunction::_6)
			#endif // HTL_I2C1_EXIST

			#ifdef HTL_I2C2_EXIST
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl,   gpio::PinA7,  gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl,   gpio::PinA9,  gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl,   gpio::PinA11, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl,   gpio::PinB3,  gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl,   gpio::PinB10, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::scl,   gpio::PinB13, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda,   gpio::PinA8,  gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda,   gpio::PinA10, gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda,   gpio::PinA12, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda,   gpio::PinB4,  gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda,   gpio::PinB11, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_2, PinFunction::sda,   gpio::PinB14, gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_1, PinFunction::alert, gpio::PinA8,  gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_1, PinFunction::alert, gpio::PinA15, gpio::AlternateFunction::_8)
			ALT_FUNCTION(DeviceID::_1, PinFunction::alert, gpio::PinB12, gpio::AlternateFunction::_8)
			#endif // HTL_I2C2_EXIST

			#ifdef HTL_I2C3_EXIST
			ALT_FUNCTION(DeviceID::_3, PinFunction::scl,   gpio::PinA7,  gpio::AlternateFunction::_9)
			ALT_FUNCTION(DeviceID::_3, PinFunction::scl,   gpio::PinB3,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_3, PinFunction::scl,   gpio::PinC1,  gpio::AlternateFunction::_6)

			ALT_FUNCTION(DeviceID::_3, PinFunction::sda,   gpio::PinA6,  gpio::AlternateFunction::_9)
			ALT_FUNCTION(DeviceID::_3, PinFunction::sda,   gpio::PinB4,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(DeviceID::_3, PinFunction::sda,   gpio::PinC6,  gpio::AlternateFunction::_6)
			#endif // HTL_I2C3_EXIST
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G0B1


#endif // __STM32G0B1_htlI2C_Pins__
