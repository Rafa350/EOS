#pragma once
#ifndef __STM32_htlI2C_AF_G031__
#define __STM32_htlI2C_AF_G031__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G031)


#define DECLARE_I2C_PIN(ch, fn, pin, af)   \
	template <>                            \
	struct I2CPinTrait<ch, pin, fn> {      \
		static constexpr GPIOAlt alt = af; \
	};


namespace htl {

	#ifdef HTL_I2C1_EXIST
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SCL, GPIO_A9, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SDA, GPIO_A10, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SCL, GPIO_B6, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SDA, GPIO_B7, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SCL, GPIO_B8, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SDA, GPIO_B9, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SCL, GPIO_B10, GPIOAlt::_1)
	DECLARE_I2C_PIN(I2CChannel::_1, I2CPin::SDA, GPIO_B11, GPIOAlt::_1)
	#endif // HTL_I2C1_EXIST

	#ifdef HTL_I2C2_EXIST
	DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SCL, GPIO_A11, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SDA, GPIO_A12, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SCL, GPIO_B10, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SDA, GPIO_B11, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SCL, GPIO_B13, GPIOAlt::_6)
	DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SDA, GPIO_B14, GPIOAlt::_6)
	#endif // HTL_I2C2_EXIST
}


#undef DECLARE_I2C_PIN


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_htlI2C_AF_G031__
