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


#define DEF(deviceID, pf, portID, pinID, af)               \
    template <>                                            \
    struct PinFunctionInfo2<deviceID, pf, portID, pinID> { \
        static constexpr gpio::AlternateFunction alt = af; \
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


            #ifdef HTL_UART1_EXIST
                DEF(DeviceID::_1, PinFunction::tx,  gpio::PortID::A, gpio::PinID::_9,  gpio::AlternateFunction::_1)
                DEF(DeviceID::_1, PinFunction::tx,  gpio::PortID::B, gpio::PinID::_6,  gpio::AlternateFunction::_0)

                DEF(DeviceID::_1, PinFunction::rx,  gpio::PortID::A, gpio::PinID::_10, gpio::AlternateFunction::_1)
                DEF(DeviceID::_1, PinFunction::rx,  gpio::PortID::B, gpio::PinID::_7,  gpio::AlternateFunction::_0)

                DEF(DeviceID::_1, PinFunction::cts, gpio::PortID::A, gpio::PinID::_11, gpio::AlternateFunction::_1)
                DEF(DeviceID::_1, PinFunction::cts, gpio::PortID::B, gpio::PinID::_4,  gpio::AlternateFunction::_4)

                DEF(DeviceID::_1, PinFunction::rts, gpio::PortID::A, gpio::PinID::_12, gpio::AlternateFunction::_1)
                DEF(DeviceID::_1, PinFunction::rts, gpio::PortID::B, gpio::PinID::_3,  gpio::AlternateFunction::_4)
            #endif // HTL_UART1_EXIST

            #ifdef HTL_UART2_EXIST
                DEF(DeviceID::_2, PinFunction::tx,  gpio::PortID::A, gpio::PinID::_2,  gpio::AlternateFunction::_1)
                DEF(DeviceID::_2, PinFunction::tx,  gpio::PortID::A, gpio::PinID::_14, gpio::AlternateFunction::_1)

                DEF(DeviceID::_2, PinFunction::rx,  gpio::PortID::A, gpio::PinID::_3,  gpio::AlternateFunction::_1)
                DEF(DeviceID::_2, PinFunction::rx,  gpio::PortID::A, gpio::PinID::_15, gpio::AlternateFunction::_1)

                DEF(DeviceID::_2, PinFunction::cts, gpio::PortID::A, gpio::PinID::_0,  gpio::AlternateFunction::_1)
                DEF(DeviceID::_2, PinFunction::cts, gpio::PortID::D, gpio::PinID::_3,  gpio::AlternateFunction::_0)

                DEF(DeviceID::_2, PinFunction::rts, gpio::PortID::A, gpio::PinID::_1,  gpio::AlternateFunction::_1)
            #endif // HTL_UART2_EXIST

            #ifdef HTL_UART3_EXIST
                DEF(DeviceID::_2, PinFunction::tx,  gpio::PortID::A, gpio::PinID::_5,  gpio::AlternateFunction::_4)
                DEF(DeviceID::_2, PinFunction::tx,  gpio::PortID::B, gpio::PinID::_2,  gpio::AlternateFunction::_4)
                DEF(DeviceID::_2, PinFunction::tx,  gpio::PortID::B, gpio::PinID::_8,  gpio::AlternateFunction::_4)
                DEF(DeviceID::_2, PinFunction::tx,  gpio::PortID::B, gpio::PinID::_10, gpio::AlternateFunction::_4)

                DEF(DeviceID::_2, PinFunction::rx,  gpio::PortID::B, gpio::PinID::_0,  gpio::AlternateFunction::_4)
                DEF(DeviceID::_2, PinFunction::rx,  gpio::PortID::B, gpio::PinID::_9,  gpio::AlternateFunction::_4)
                DEF(DeviceID::_2, PinFunction::rx,  gpio::PortID::B, gpio::PinID::_11, gpio::AlternateFunction::_4)

                DEF(DeviceID::_2, PinFunction::cts, gpio::PortID::A, gpio::PinID::_6,  gpio::AlternateFunction::_4)
                DEF(DeviceID::_2, PinFunction::cts, gpio::PortID::B, gpio::PinID::_13, gpio::AlternateFunction::_4)

                DEF(DeviceID::_2, PinFunction::rts, gpio::PortID::A, gpio::PinID::_15, gpio::AlternateFunction::_5)
                DEF(DeviceID::_2, PinFunction::rts, gpio::PortID::B, gpio::PinID::_1,  gpio::AlternateFunction::_4)
                DEF(DeviceID::_2, PinFunction::rts, gpio::PortID::B, gpio::PinID::_14, gpio::AlternateFunction::_4)
            #endif // HTL_UART3_EXIST

            #ifdef HTL_UART4_EXISTS
            #endif // HTL_UART4_EXISTS
            
		}
	}
}


#undef DEF
#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G071

