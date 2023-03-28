#pragma once
#ifndef __STM32_htlSPI_AF_G0301__
#define __STM32_htlSPI_AF_G031__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G031)


#define DECLARE_SPI_PIN(ch, fn, pin, af)   \
	template <>                            \
	struct SPIPinTrait<ch, pin, fn> {      \
		static constexpr GPIOAlt alt = af; \
	};


namespace htl {

	#ifdef HTL_SPI1_EXIST
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::SCK,  GPIO_A1,  GPIOAlt::_0)
    DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MOSI, GPIO_A2,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::SCK,  GPIO_A5,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MISO, GPIO_A6,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MOSI, GPIO_A7,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MISO, GPIO_A11, GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MOSI, GPIO_A12, GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::SCK,  GPIO_B3,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MISO, GPIO_B4,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_1, SPIPin::MOSI, GPIO_B5,  GPIOAlt::_0)
	#endif // HTL_SPI1_EXIST

	#ifdef HTL_SPI2_EXIST
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_A0,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MISO, GPIO_A3,  GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_A4,  GPIOAlt::_1)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MISO, GPIO_A9,  GPIOAlt::_4)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_A10, GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MISO, GPIO_B1,  GPIOAlt::_1)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MISO, GPIO_B6,  GPIOAlt::_4)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_B7,  GPIOAlt::_1)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_B8,  GPIOAlt::_1)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_B10, GPIOAlt::_5)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_B11, GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::SCK,  GPIO_B13, GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MISO, GPIO_B14, GPIOAlt::_0)
	DECLARE_SPI_PIN(SPIChannel::_2, SPIPin::MOSI, GPIO_B15, GPIOAlt::_0)
	#endif // HTL_SPI2_EXIST
}


#undef DECLARE_SPI_PIN


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_htlSPI_AF_G030__
