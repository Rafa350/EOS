#pragma once
#ifndef __STM32_G0_htlSPI_AF_G071__
#define __STM32_G0_htlSPI_AF_G071__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G071)


#define ALT_FUNCTION(id, fn, pin, af)                 \
	template <>                                       \
	struct PinFunctionInfo<DeviceID::_##id, fn, pin> { \
		static constexpr gpio::PinFunction alt = af;      \
	};


namespace htl {
	namespace spi {
		namespace internal {

			#ifdef HTL_SPI1_EXIST
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinA1,  gpio::PinFunction::_0)
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinA5,  gpio::PinFunction::_0)
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinB3,  gpio::PinFunction::_0)

			ALT_FUNCTION(1, PinFunction::miso, gpio::PinA6,  gpio::PinFunction::_0)
			ALT_FUNCTION(1, PinFunction::miso, gpio::PinA11, gpio::PinFunction::_0)
			ALT_FUNCTION(1, PinFunction::miso, gpio::PinB4,  gpio::PinFunction::_0)

			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinA2,  gpio::PinFunction::_0)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinA7,  gpio::PinFunction::_0)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinA12, gpio::PinFunction::_0)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinB5,  gpio::PinFunction::_0)
			#endif // HTL_SPI1_EXIST

			#ifdef HTL_SPI2_EXIST
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinA0,  gpio::PinFunction::_0)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB8,  gpio::PinFunction::_1)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB10, gpio::PinFunction::_5)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB13, gpio::PinFunction::_0)

			ALT_FUNCTION(2, PinFunction::miso, gpio::PinA3,  gpio::PinFunction::_0)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinA9,  gpio::PinFunction::_4)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinB1,  gpio::PinFunction::_1)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinB6,  gpio::PinFunction::_4)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinB14, gpio::PinFunction::_0)

			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinA4,  gpio::PinFunction::_1)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinA10, gpio::PinFunction::_0)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinB7,  gpio::PinFunction::_1)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinB11, gpio::PinFunction::_0)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinB15, gpio::PinFunction::_0)
			#endif // HTL_SPI2_EXIST
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G071


#endif // __STM32_G0_htlSPI_AF_G071__
