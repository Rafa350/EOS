#pragma once
#ifndef __STM32_htlSPI_AF_G031__
#define __STM32_htlSPI_AF_G031__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G031)


#define ALT_FUNCTION(id, fn, pin, af)                 \
	template <>                                       \
	struct SPIAltFunction<DeviceID::_##id, fn, pin> { \
		static constexpr gpio::GPIOAlt alt = af;      \
	};


namespace htl {
	namespace spi {
		namespace internal {

			#ifdef HTL_SPI1_EXIST
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinA1,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinA5,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::sck,  gpio::PinB3,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::miso, gpio::PinA6,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::miso, gpio::PinA11, gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::miso, gpio::PinB4,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinA2,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinA7,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinA12, gpio::GPIOAlt::_0)
			ALT_FUNCTION(1, PinFunction::mosi, gpio::PinB5,  gpio::GPIOAlt::_0)
			#endif // HTL_SPI1_EXIST

			#ifdef HTL_SPI2_EXIST
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinA0,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB8,  gpio::GPIOAlt::_1)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB10, gpio::GPIOAlt::_5)
			ALT_FUNCTION(2, PinFunction::sck,  gpio::PinB13, gpio::GPIOAlt::_0)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinA3,  gpio::GPIOAlt::_0)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinA9,  gpio::GPIOAlt::_4)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinB1,  gpio::GPIOAlt::_1)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinB6,  gpio::GPIOAlt::_4)
			ALT_FUNCTION(2, PinFunction::miso, gpio::PinB14, gpio::GPIOAlt::_0)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinA4,  gpio::GPIOAlt::_1)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinA10, gpio::GPIOAlt::_0)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinB7,  gpio::GPIOAlt::_1)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinB11, gpio::GPIOAlt::_0)
			ALT_FUNCTION(2, PinFunction::mosi, gpio::PinB15, gpio::GPIOAlt::_0)
			#endif // HTL_SPI2_EXIST
		}
	}
}


#undef ALT_FUNCTION


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_htlSPI_AF_G031__
