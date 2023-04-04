#pragma once
#ifndef __STM32_htlI2C_AF_F7__
#define __STM32_htlI2C_AF_F7__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F7)


#define DECLARE_I2C_PIN(ch, fn, pin, af)   \
	template <>                            \
	struct I2CPinTrait<ch, pin, fn> {      \
		static constexpr GPIOAlt alt = af; \
	};


namespace htl {

	#ifdef HTL_I2C1_EXIST
	#endif // HTL_I2C1_EXIST

	#ifdef HTL_I2C2_EXIST
	#endif // HTL_I2C2_EXIST

	#ifdef HTL_I2C3_EXIST
	DECLARE_I2C_PIN(I2CChannel::_3, I2CPin::SCL, GPIO_H7, GPIOAlt::_4)
	DECLARE_I2C_PIN(I2CChannel::_3, I2CPin::SDA, GPIO_H8, GPIOAlt::_4)
	#endif // HTL_I2C3_EXIST
}


#undef DECLARE_I2C_PIN


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_htlI2C_AF_F7__
