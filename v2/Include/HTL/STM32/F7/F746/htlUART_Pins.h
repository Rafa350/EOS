#pragma once
#ifndef __STM32_F7_htlUART_AF_F7__
#define __STM32_F7_htlUART_AF_F7__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F7)


#define ALT_FUNCTION(id, fn, pin, af)                    \
    template <>                                          \
    struct PinFunctionInfo<DeviceID::_##id, fn, pin> { \
        static constexpr gpio::AlternateFunction alt = af;   \
    };


namespace htl {

    namespace uart {

        namespace internal {

            #ifdef HTL_UART1_EXIST
            ALT_FUNCTION(1, PinFunction::tx,  gpio::PinA9,  gpio::AlternateFunction::_8)

            ALT_FUNCTION(1, PinFunction::rx,  gpio::PinB7,  gpio::AlternateFunction::_8)
            #endif

            #ifdef HTL_UART2_EXIST
            ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA9,  gpio::AlternateFunction::_8)

            ALT_FUNCTION(2, PinFunction::rx,  gpio::PinB7,  gpio::AlternateFunction::_8)
            #endif

            #ifdef HTL_UART3_EXIST
            #endif

            #ifdef HTL_UART4_EXIST
            #endif

            #ifdef HTL_UART5_EXIST
            #endif

            #ifdef HTL_UART6_EXIST
            ALT_FUNCTION(6, PinFunction::tx,  gpio::PinC6,  gpio::AlternateFunction::_8)

            ALT_FUNCTION(2, PinFunction::rx,  gpio::PinC7,  gpio::AlternateFunction::_8)
            #endif

            #ifdef HTL_UART7_EXIST
            #endif

            #ifdef HTL_UART8_EXIST
            #endif
        }
    }
}


#endif // EOS_PLATFORM_STM32F7


#endif // __STM32_F7_htlUART_AF_F7__

