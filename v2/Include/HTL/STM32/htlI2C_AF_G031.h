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
        DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SCL, GPIO_A11, GPIOAlt::_6)
        DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SDA, GPIO_A12, GPIOAlt::_6)
        DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SCL, GPIO_B10, GPIOAlt::_6)
        DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SDA, GPIO_B11, GPIOAlt::_6)
        DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SCL, GPIO_B13, GPIOAlt::_6)
        DECLARE_I2C_PIN(I2CChannel::_2, I2CPin::SDA, GPIO_B14, GPIOAlt::_6)
        
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


#undef DECLARE_I2C_PIN


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_htlI2C_AF_G031__
