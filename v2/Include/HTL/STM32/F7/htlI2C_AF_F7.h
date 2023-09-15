#pragma once
#ifndef __STM32_F7_htlI2C_AF_F7__
#define __STM32_F7_htlI2C_AF_F7__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F7)


#define ALT_FUNCTION(id, fn, pin, af)                 \
	template <>                                       \
	struct I2CPinFunctionID<DeviceID::_##id, fn, pin> { \
		static constexpr gpio::PinFunctionID alt = af;      \
	};


namespace htl {
    namespace i2c {
        namespace internal {

            #ifdef HTL_I2C1_EXIST
            #endif // HTL_I2C1_EXIST

            #ifdef HTL_I2C2_EXIST
            #endif // HTL_I2C2_EXIST

            #ifdef HTL_I2C3_EXIST
            ALT_FUNCTION(3, PinFunction::scl, gpio::PinH7, gpio::PinFunctionID::_4)
            ALT_FUNCTION(3, PinFunction::sda, gpio::PinH8, gpio::PinFunctionID::_4)
            #endif // HTL_I2C3_EXIST
        }
    }
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_F7_htlI2C_AF_F7__
