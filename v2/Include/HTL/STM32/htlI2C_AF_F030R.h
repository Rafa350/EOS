#pragma once
#ifndef __STM32_htlI2C_AF_F030R__
#define __STM32_htlI2C_AF_F030R__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F030R4) || \
	defined(EOS_PLATFORM_STM32F030R6) || \
	defined(EOS_PLATFORM_STM32F030R8) || \
	defined(EOS_PLATFORM_STM32F030RC)


namespace htl {

	#ifdef HTL_I2C1_EXIST
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B6, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};

		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B7, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};
	#endif

	#ifdef HTL_I2C2_EXIST
	#endif
}


#endif


#endif // __STM32_htlI2C_AF_F030R__
