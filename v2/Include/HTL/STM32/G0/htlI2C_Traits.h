#pragma once
#ifndef __STM32G0_htlI2C_Traits__
#define __STM32G0_htlI2C_Traits__


// HTL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32G0)
	#error "Valid for STM32G0 platform only"
#endif


namespace htl {
	namespace i2c {
		namespace internal {

			#ifdef HTL_I2C1_EXIST
			template <>
			struct I2CTraits<DeviceID::i2c1> {
				static constexpr uint32_t i2cAddr = I2C1_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C1EN_Pos;
                static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
                static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C1RST_Pos;
			};
			#endif

			#ifdef HTL_I2C2_EXIST
			template <>
			struct I2CTraits<DeviceID::i2c2> {
				static constexpr uint32_t i2cAddr = I2C2_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C2EN_Pos;
                static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
                static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C2RST_Pos;
			};
			#endif

			#ifdef HTL_I2C3_EXIST
			template <>
			struct I2CTraits<DeviceID::i2c3> {
				static constexpr uint32_t i2cAddr = I2C3_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C3EN_Pos;
                static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
                static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C3RST_Pos;
			};
			#endif
		}
	}
}


#endif // __STM32G0_htlI2C_Traits__
