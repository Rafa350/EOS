#pragma once
#ifndef __STM32_G0_htlI2C_AF_G030__
#define __STM32_G0_htlI2C_AF_G030__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G030)


namespace htl {

	#ifdef HTL_I2C1_EXIST
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_A9, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_A10, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B6, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B7, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B8, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B9, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
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
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};

		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_A12, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_B10, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_B11, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_B13, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_2, GPIO_B14, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_6;
		};
	#endif
}


#endif // EOS_PLATFORM_STM32G030


#endif // __STM32_G0_htlI2C_AF_G030__
