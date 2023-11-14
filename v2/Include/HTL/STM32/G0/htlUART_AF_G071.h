#pragma once


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G071)


#define ALT_FUNCTION(id, fn, pin, af)                    \
	template <>                                          \
	struct PinFunctionInfo<DeviceID::_##id, fn, pin> { \
		static constexpr gpio::PinFunction alt = af;   \
	};


namespace htl {
	namespace uart {
		namespace internal {
			#ifdef HTL_UART1_EXIST
				ALT_FUNCTION(1, PinFunction::tx,  gpio::PinA9,  gpio::PinFunction::_1)
    			ALT_FUNCTION(1, PinFunction::tx,  gpio::PinB6,  gpio::PinFunction::_0)

				ALT_FUNCTION(1, PinFunction::rx,  gpio::PinA10, gpio::PinFunction::_1)
    			ALT_FUNCTION(1, PinFunction::rx,  gpio::PinB7,  gpio::PinFunction::_0)

				ALT_FUNCTION(1, PinFunction::cts, gpio::PinA11, gpio::PinFunction::_1)
    			ALT_FUNCTION(1, PinFunction::cts, gpio::PinB4,  gpio::PinFunction::_4)

				ALT_FUNCTION(1, PinFunction::rts, gpio::PinA12, gpio::PinFunction::_1)
				ALT_FUNCTION(1, PinFunction::rts, gpio::PinB3,  gpio::PinFunction::_4)
			#endif // HTL_UART1_EXIST

			#ifdef HTL_UART2_EXIST
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA2,  gpio::PinFunction::_1)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA14, gpio::PinFunction::_1)

				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinA3,  gpio::PinFunction::_1)
				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinA15, gpio::PinFunction::_1)

				ALT_FUNCTION(2, PinFunction::cts, gpio::PinA0,  gpio::PinFunction::_1)
				ALT_FUNCTION(2, PinFunction::cts, gpio::PinD3,  gpio::PinFunction::_0)

				ALT_FUNCTION(2, PinFunction::rts, gpio::PinA1,  gpio::PinFunction::_1)
			#endif // HTL_UART2_EXIST

			#ifdef HTL_UART3_EXIST
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinA5,  gpio::PinFunction::_4)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinB2,  gpio::PinFunction::_4)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinB8,  gpio::PinFunction::_4)
				ALT_FUNCTION(2, PinFunction::tx,  gpio::PinB10, gpio::PinFunction::_4)

				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinB0,  gpio::PinFunction::_4)
				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinB9,  gpio::PinFunction::_4)
				ALT_FUNCTION(2, PinFunction::rx,  gpio::PinB11, gpio::PinFunction::_4)

				ALT_FUNCTION(2, PinFunction::cts, gpio::PinA6,  gpio::PinFunction::_4)
				ALT_FUNCTION(2, PinFunction::cts, gpio::PinB13, gpio::PinFunction::_4)

				ALT_FUNCTION(2, PinFunction::rts, gpio::PinA15, gpio::PinFunction::_5)
				ALT_FUNCTION(2, PinFunction::rts, gpio::PinB1,  gpio::PinFunction::_4)
				ALT_FUNCTION(2, PinFunction::rts, gpio::PinB14, gpio::PinFunction::_4)
			#endif // HTL_UART3_EXIST
            
            #ifdef HTL_UART4_EXISTS
            #endif // HTL_UART4_EXISTS
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G071

