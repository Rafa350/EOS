#pragma once
#ifndef __STM32_htlI2C_AF_F030__
#define __STM32_htlI2C_AF_F030__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F030)


namespace htl {

	#ifdef HTL_I2C1_EXIST
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_A9, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_A10, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B6, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B7, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B8, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B9, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B10, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B11, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
	#endif

	#ifdef HTL_I2C2_EXIST
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_A11, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_A12, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_B13, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_B14, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_F6, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_0;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_F7, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_0;
		};
	#endif
}


#endif // EOS_PLATFORM_STM32F030


#endif // __STM32_htlI2C_AF_F030__
