#pragma once
#ifndef __STM32_G0_htlSPI_AF_G031__
#define __STM32_G0_htlSPI_AF_G031__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G031)


#define DEF(deviceID, pinFunction, pin, af)                  \
	template <>                                        \
	struct PinFunctionInfo<deviceID, pinFunction, pin> { \
		static constexpr gpio::AlternateFunction alt = af;   \
	};


namespace htl {
	namespace spi {
		namespace internal {

			#ifdef HTL_SPI1_EXIST
			DEF(DeviceID::_1, PinFunction::sck,  gpio::PinA1,  gpio::AlternateFunction::_0)
			DEF(DeviceID::_1, PinFunction::sck,  gpio::PinA5,  gpio::AlternateFunction::_0)
			DEF(DeviceID::_1, PinFunction::sck,  gpio::PinB3,  gpio::AlternateFunction::_0)

			DEF(DeviceID::_1, PinFunction::miso, gpio::PinA6,  gpio::AlternateFunction::_0)
			DEF(DeviceID::_1, PinFunction::miso, gpio::PinA11, gpio::AlternateFunction::_0)
			DEF(DeviceID::_1, PinFunction::miso, gpio::PinB4,  gpio::AlternateFunction::_0)

			DEF(DeviceID::_1, PinFunction::mosi, gpio::PinA2,  gpio::AlternateFunction::_0)
			DEF(DeviceID::_1, PinFunction::mosi, gpio::PinA7,  gpio::AlternateFunction::_0)
			DEF(DeviceID::_1, PinFunction::mosi, gpio::PinA12, gpio::AlternateFunction::_0)
			DEF(DeviceID::_1, PinFunction::mosi, gpio::PinB5,  gpio::AlternateFunction::_0)
			#endif // HTL_SPI1_EXIST

			#ifdef HTL_SPI2_EXIST
			DEF(DeviceID::_2, PinFunction::sck,  gpio::PinA0,  gpio::AlternateFunction::_0)
			DEF(DeviceID::_2, PinFunction::sck,  gpio::PinB8,  gpio::AlternateFunction::_1)
			DEF(DeviceID::_2, PinFunction::sck,  gpio::PinB10, gpio::AlternateFunction::_5)
			DEF(DeviceID::_2, PinFunction::sck,  gpio::PinB13, gpio::AlternateFunction::_0)

			DEF(DeviceID::_2, PinFunction::miso, gpio::PinA3,  gpio::AlternateFunction::_0)
			DEF(DeviceID::_2, PinFunction::miso, gpio::PinA9,  gpio::AlternateFunction::_4)
			DEF(DeviceID::_2, PinFunction::miso, gpio::PinB1,  gpio::AlternateFunction::_1)
			DEF(DeviceID::_2, PinFunction::miso, gpio::PinB6,  gpio::AlternateFunction::_4)
			DEF(DeviceID::_2, PinFunction::miso, gpio::PinB14, gpio::AlternateFunction::_0)

			DEF(DeviceID::_2, PinFunction::mosi, gpio::PinA4,  gpio::AlternateFunction::_1)
			DEF(DeviceID::_2, PinFunction::mosi, gpio::PinA10, gpio::AlternateFunction::_0)
			DEF(DeviceID::_2, PinFunction::mosi, gpio::PinB7,  gpio::AlternateFunction::_1)
			DEF(DeviceID::_2, PinFunction::mosi, gpio::PinB11, gpio::AlternateFunction::_0)
			DEF(DeviceID::_2, PinFunction::mosi, gpio::PinB15, gpio::AlternateFunction::_0)
			#endif // HTL_SPI2_EXIST
		}
	}
}


#undef DEf


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_G0_htlSPI_AF_G031__
