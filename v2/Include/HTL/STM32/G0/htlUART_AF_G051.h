#pragma once
#ifndef __STM32_G0_htlUART_AF_G051__
#define __STM32_G0_htlUART_AF_GO51__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G051) 


#define ALT_FUNCTION(id, fn, pin, af)                    \
	template <>                                          \
	struct UARTPinFunctionID<DeviceID::_##id, fn, pin> { \
		static constexpr gpio::PinFunctionID alt = af;   \
	};


namespace htl {
	namespace uart {
		namespace internal {
			#ifdef HTL_UART1_EXIST
				ALT_FUNCTION(1, PinFunction::tx,  gpio::PinA9,  gpio::PinFunctionID::_1)
    			ALT_FUNCTION(1, PinFunction::tx,  gpio::PinB6,  gpio::PinFunctionID::_0)

				ALT_FUNCTION(1, PinFunction::rx,  gpio::PinA10, gpio::PinFunctionID::_1)
    			ALT_FUNCTION(1, PinFunction::rx,  gpio::PinB7,  gpio::PinFunctionID::_0)

				ALT_FUNCTION(1, PinFunction::cts, gpio::PinA11, gpio::PinFunctionID::_1)
    			ALT_FUNCTION(1, PinFunction::cts, gpio::PinB4,  gpio::PinFunctionID::_4)

				ALT_FUNCTION(1, PinFunction::rts, gpio::PinA12, gpio::PinFunctionID::_1)
				ALT_FUNCTION(1, PinFunction::rts, gpio::PinB3,  gpio::PinFunctionID::_4)
			#endif

			#ifdef HTL_UART2_EXIST
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA2,  gpio::PinFunctionID::_1)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA14, gpio::PinFunctionID::_1)

				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinA3,  gpio::PinFunctionID::_1)
				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinA15, gpio::PinFunctionID::_1)

				ALT_FUNCTION(2, PinFunction::cts,  gpio::PinA0, gpio::PinFunctionID::_1)
				ALT_FUNCTION(2, PinFunction::cts,  gpio::PinD3, gpio::PinFunctionID::_0)

				ALT_FUNCTION(2, PinFunction::rts,  gpio::PinA1, gpio::PinFunctionID::_1)
			#endif
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G051


#endif // __STM32_G0_htlUART_AF_G051__

