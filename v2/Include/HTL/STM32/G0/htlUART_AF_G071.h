#pragma once


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G071)


#define ALT_FUNCTION(id, fn, pin, af)                    \
	template <>                                          \
	struct PinFunctionInfo<DeviceID::_##id, fn, pin> { \
		static constexpr gpio::AlternateFunction alt = af;   \
	};


namespace htl {
	namespace uart {
		namespace internal {
			#ifdef HTL_UART1_EXIST
				ALT_FUNCTION(1, PinFunction::tx,  gpio::PinA9,  gpio::AlternateFunction::_1)
    			ALT_FUNCTION(1, PinFunction::tx,  gpio::PinB6,  gpio::AlternateFunction::_0)

				ALT_FUNCTION(1, PinFunction::rx,  gpio::PinA10, gpio::AlternateFunction::_1)
    			ALT_FUNCTION(1, PinFunction::rx,  gpio::PinB7,  gpio::AlternateFunction::_0)

				ALT_FUNCTION(1, PinFunction::cts, gpio::PinA11, gpio::AlternateFunction::_1)
    			ALT_FUNCTION(1, PinFunction::cts, gpio::PinB4,  gpio::AlternateFunction::_4)

				ALT_FUNCTION(1, PinFunction::rts, gpio::PinA12, gpio::AlternateFunction::_1)
				ALT_FUNCTION(1, PinFunction::rts, gpio::PinB3,  gpio::AlternateFunction::_4)
			#endif // HTL_UART1_EXIST

			#ifdef HTL_UART2_EXIST
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA2,  gpio::AlternateFunction::_1)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA14, gpio::AlternateFunction::_1)

				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinA3,  gpio::AlternateFunction::_1)
				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinA15, gpio::AlternateFunction::_1)

				ALT_FUNCTION(2, PinFunction::cts, gpio::PinA0,  gpio::AlternateFunction::_1)
				ALT_FUNCTION(2, PinFunction::cts, gpio::PinD3,  gpio::AlternateFunction::_0)

				ALT_FUNCTION(2, PinFunction::rts, gpio::PinA1,  gpio::AlternateFunction::_1)
			#endif // HTL_UART2_EXIST

			#ifdef HTL_UART3_EXIST
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA5,  gpio::AlternateFunction::_4)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinB2,  gpio::AlternateFunction::_4)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinB8,  gpio::AlternateFunction::_4)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinB10, gpio::AlternateFunction::_4)

				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinB0,  gpio::AlternateFunction::_4)
				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinB9,  gpio::AlternateFunction::_4)
				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinB11, gpio::AlternateFunction::_4)

				ALT_FUNCTION(2, PinFunction::cts, gpio::PinA6,  gpio::AlternateFunction::_4)
				ALT_FUNCTION(2, PinFunction::cts, gpio::PinB13, gpio::AlternateFunction::_4)

				ALT_FUNCTION(2, PinFunction::rts, gpio::PinA15, gpio::AlternateFunction::_5)
				ALT_FUNCTION(2, PinFunction::rts, gpio::PinB1,  gpio::AlternateFunction::_4)
				ALT_FUNCTION(2, PinFunction::rts, gpio::PinB14, gpio::AlternateFunction::_4)
			#endif // HTL_UART3_EXIST
            
            #ifdef HTL_UART4_EXISTS
            #endif // HTL_UART4_EXISTS
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G071

