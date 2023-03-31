#pragma once
#ifndef __STM32_htlSPI_AF_F4__
#define __STM32_htlSPI_AF_F4__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F4)


#define DECLARE_SPI_PIN(ch, fn, pin, af)   \
	template <>                            \
	struct SPIPinTrait<ch, pin, fn> {      \
		static constexpr GPIOAlt alt = af; \
	};


namespace htl {

	#ifdef HTL_SPI1_EXIST
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::SCK,  GPIO_A5, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MISO, GPIO_A6, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MOSI, GPIO_A7, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::SCK,  GPIO_B3, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MISO, GPIO_B4, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MOSI, GPIO_B5, GPIOAlt::_5)
	#endif

	#ifdef HTL_SPI2_EXIST
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_B10, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_B13, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MISO, GPIO_B14, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_B15, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_C2,  GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_C3,  GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_D3,  GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_I1,  GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MISO, GPIO_I2,  GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_I3,  GPIOAlt::_5)
	#endif

	#ifdef HTL_SPI3_EXIST
	DECLARE_SPI_PIN(SPIChannel::_3, SPIPin::SCK,  GPIO_B3,  GPIOAlt::_6)
	DECLARE_SPI_PIN(SPIChannel::_3, SPIPin::MISO, GPIO_B4,  GPIOAlt::_6)
	DECLARE_SPI_PIN(SPIChannel::_3, SPIPin::MOSI, GPIO_B5,  GPIOAlt::_6)
	DECLARE_SPI_PIN(SPIChannel::_3, SPIPin::SCK,  GPIO_C10, GPIOAlt::_6)
	DECLARE_SPI_PIN(SPIChannel::_3, SPIPin::MISO, GPIO_C11, GPIOAlt::_6)
	DECLARE_SPI_PIN(SPIChannel::_3, SPIPin::MOSI, GPIO_C12, GPIOAlt::_6)
	DECLARE_SPI_PIN(SPIChannel::_3, SPIPin::MOSI, GPIO_D6,  GPIOAlt::_5)
	#endif

	#ifdef HTL_SPI4_EXIST
	#endif

	#ifdef HTL_SPI5_EXIST
	DECLARE_SPI_PIN(SPIChannel::_5, SPIPin::SCK,  GPIO_F7, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_5, SPIPin::MOSI, GPIO_F9, GPIOAlt::_5)
	#endif

}


#endif // EOS_PLATFORM_STM32F4


#endif // __STM32_htlSPI_AF_F4__
