#pragma once
#ifndef __STM32_F7_htlLTDC_AF_F7__
#define __STM32_F7_htlLTDC_AF_F7__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"
#include "HTL/STM32/htlLTDC.h"


#if defined(EOS_PLATFORM_STM32F7)


#define ALT_FUNCTION(fn, pin, af)        \
	template <>                                  \
	struct LTDCPinFunctionID<fn, pin> {            \
		static constexpr gpio::PinFunctionID alt = af; \
	};


namespace htl {
	namespace ltdc {
		namespace internal {

			ALT_FUNCTION(PinFunction::de,    gpio::PinF10, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::de,    gpio::PinE13, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::de,    gpio::PinK7,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::pc,    gpio::PinE14, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::pc,    gpio::PinG7,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::pc,    gpio::PinI14, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::hsync, gpio::PinC6,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::hsync, gpio::PinI10, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::hsync, gpio::PinI12, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::vsync, gpio::PinA4,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::vsync, gpio::PinI9,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::vsync, gpio::PinI13, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r0,    gpio::PinI15, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r0,    gpio::PinH2,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r1,    gpio::PinJ0,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r1,    gpio::PinA2,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r1,    gpio::PinH3,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r2,    gpio::PinA1,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r2,    gpio::PinC10, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r2,    gpio::PinH8,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r2,    gpio::PinJ1,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r3,    gpio::PinH9,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r3,    gpio::PinB0,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r3,    gpio::PinJ2,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r4,    gpio::PinA5,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r4,    gpio::PinA11, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r4,    gpio::PinH10, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r4,    gpio::PinJ3,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r5,    gpio::PinH11, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r5,    gpio::PinA12, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r5,    gpio::PinJ4,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r6,    gpio::PinA8,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r6,    gpio::PinB1,  gpio::PinFunctionID::_9)
			ALT_FUNCTION(PinFunction::r6,    gpio::PinH12, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r6,    gpio::PinJ5,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::r7,    gpio::PinE15, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r7,    gpio::PinG6,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::r7,    gpio::PinJ6,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b0,    gpio::PinE4,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b0,    gpio::PinJ12, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b1,    gpio::PinG12, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b1,    gpio::PinJ13, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b2,    gpio::PinD6,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b2,    gpio::PinG10, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b2,    gpio::PinJ14, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b3,    gpio::PinG11, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b3,    gpio::PinD10, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b3,    gpio::PinJ15, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b4,    gpio::PinE12, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b4,    gpio::PinG12, gpio::PinFunctionID::_9)
			ALT_FUNCTION(PinFunction::b4,    gpio::PinI4,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b4,    gpio::PinK3,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b5,    gpio::PinI5,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b5,    gpio::PinA3,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b5,    gpio::PinK4,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b6,    gpio::PinB8,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b6,    gpio::PinI6,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b6,    gpio::PinK5,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::b7,    gpio::PinI7,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b7,    gpio::PinB9,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::b7,    gpio::PinK6,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g0,    gpio::PinE5,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g0,    gpio::PinJ7,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g1,    gpio::PinE6,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g1,    gpio::PinJ8,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g2,    gpio::PinA6,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g2,    gpio::PinJ9,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g2,    gpio::PinH13, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g3,    gpio::PinH14, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g3,    gpio::PinE11, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g3,    gpio::PinG10, gpio::PinFunctionID::_9)
			ALT_FUNCTION(PinFunction::g3,    gpio::PinJ10, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g4,    gpio::PinB10, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g4,    gpio::PinH15, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g4,    gpio::PinJ11, gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g5,    gpio::PinI0,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g5,    gpio::PinB11, gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g5,    gpio::PinK0,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g6,    gpio::PinC7,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g6,    gpio::PinI1,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g6,    gpio::PinK1,  gpio::PinFunctionID::_14)

			ALT_FUNCTION(PinFunction::g7,    gpio::PinI2,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g7,    gpio::PinD3,  gpio::PinFunctionID::_14)
			ALT_FUNCTION(PinFunction::g7,    gpio::PinK2,  gpio::PinFunctionID::_14)
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32F7


#endif // __STM32_F7_htlLTDC_AF_F7


