#pragma once
#ifndef __STM32F030_htlTMR_Pins__
#define __STM32F030_htlTMR_Pins__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32F030)
	#error "Valid for STM32F030 platform only"
#endif


#define ALT_FUNCTION(id, fn, pin, af)                 \
	template <>                                       \
	struct PinFunctionInfo<id, fn, pin> { \
		static constexpr gpio::AlternateFunction alt = af;      \
	};


namespace htl {
	namespace tmr {
		namespace internal {

			#ifdef HTL_TMR3_EXIST
			ALT_FUNCTION(DeviceID::_3, PinFunction::ch1, gpio::PinA6, gpio::AlternateFunction::_1)
			ALT_FUNCTION(DeviceID::_3, PinFunction::ch1, gpio::PinB4, gpio::AlternateFunction::_1)
			ALT_FUNCTION(DeviceID::_3, PinFunction::ch2, gpio::PinA7, gpio::AlternateFunction::_1)
			ALT_FUNCTION(DeviceID::_3, PinFunction::ch2, gpio::PinB5, gpio::AlternateFunction::_1)
			ALT_FUNCTION(DeviceID::_3, PinFunction::ch3, gpio::PinB0, gpio::AlternateFunction::_1)
			ALT_FUNCTION(DeviceID::_3, PinFunction::ch4, gpio::PinB1, gpio::AlternateFunction::_1)
			#endif // HTL_TMR_EXIST
		}
	}
}


#undef ALT_FUNCTION


#endif // __STM32F030_htlTMR_Pins__
