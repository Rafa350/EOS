#pragma once
#ifndef __STM32F4_htlSPI_Pins__
#define __STM32F4_htlSPI_Pins__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlSPI.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F4)


#define ALT_FUNCTION(id, fn, pin, af)  \
	template <>                                \
	struct PinFunctionInfo<DeviceID::_##id, fn, pin> {       \
		static constexpr gpio::AlternateFunction alt = af;     \
	};


namespace htl {
	namespace spi {
		namespace internal {

			#ifdef HTL_SPI1_EXIST
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinA5,  gpio::AlternateFunction::_5)
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinB3,  gpio::AlternateFunction::_5)

			ALT_FUNCTION(1, PinFunction::miso, gpio::PinA6,  gpio::AlternateFunction::_5)
			ALT_FUNCTION(1, PinFunction::miso, gpio::PinB4,  gpio::AlternateFunction::_5)

			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinA7,  gpio::AlternateFunction::_5)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinB5,  gpio::AlternateFunction::_5)
			#endif

			#ifdef HTL_SPI2_EXIST
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB10, gpio::AlternateFunction::_5)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB13, gpio::AlternateFunction::_5)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinD3,  gpio::AlternateFunction::_5)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinI1,  gpio::AlternateFunction::_5)

			ALT_FUNCTION(2, PinFunction::miso, gpio::PinB14, gpio::AlternateFunction::_5)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinI2,  gpio::AlternateFunction::_5)

			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinB15, gpio::AlternateFunction::_5)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinC2,  gpio::AlternateFunction::_5)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinC3,  gpio::AlternateFunction::_5)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinI3,  gpio::AlternateFunction::_5)
			#endif

			#ifdef HTL_SPI3_EXIST
			ALT_FUNCTION(3, PinFunction::sck,  gpio::PinB3,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(3, PinFunction::sck,  gpio::PinC10, gpio::AlternateFunction::_6)
			ALT_FUNCTION(3, PinFunction::miso, gpio::PinB4,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(3, PinFunction::miso, gpio::PinC11, gpio::AlternateFunction::_6)
			ALT_FUNCTION(3, PinFunction::mosi, gpio::PinB5,  gpio::AlternateFunction::_6)
			ALT_FUNCTION(3, PinFunction::mosi, gpio::PinC12, gpio::AlternateFunction::_6)
			ALT_FUNCTION(3, PinFunction::mosi, gpio::PinD6,  gpio::AlternateFunction::_5)
			#endif

			#ifdef HTL_SPI4_EXIST
			#endif

			#ifdef HTL_SPI5_EXIST
			ALT_FUNCTION(5, PinFunction::sck,  gpio::PinF7, gpio::AlternateFunction::_5)
			ALT_FUNCTION(5, PinFunction::mosi, gpio::PinF9, gpio::AlternateFunction::_5)
			#endif

		}
	}
}

#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32F4


#endif // __STM32F4_htlSPI_Pins__
