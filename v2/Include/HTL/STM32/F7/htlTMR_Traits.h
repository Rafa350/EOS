#pragma once
#ifndef __STM32F4_htlTMR_Traits__
#define __STM32F4_htlTMR_Traits__


// HTL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32F7)
	#error "Valid for STM32F7 platform only"
#endif


namespace htl {
	namespace tmr {
		namespace internal {

			#ifdef HTL_TMR1_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr1> {
				static constexpr uint32_t timAddr = TIM1_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t activatePos = RCC_APB2ENR_TIM1EN_Pos;
			};
			#endif

			#ifdef HTL_TMR2_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr2> {
				static constexpr uint32_t timAddr = TIM2_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM2EN_Pos;
			};
			#endif

			#ifdef HTL_TMR3_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr3> {
				static constexpr uint32_t timAddr = TIM3_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM3EN_Pos;
			};
			#endif

			#ifdef HTL_TMR4_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr4> {
				static constexpr uint32_t timAddr = TIM4_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM4EN_Pos;
			};
			#endif

			#ifdef HTL_TMR5_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr5> {
				static constexpr uint32_t timAddr = TIM5_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM5EN_Pos;
			};
			#endif

			#ifdef HTL_TMR6_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr6> {
				static constexpr uint32_t timAddr = TIM6_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM6EN_Pos;
			};
			#endif

			#ifdef HTL_TMR7_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr7> {
				static constexpr uint32_t timAddr = TIM7_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM7EN_Pos;
			};
			#endif

			#ifdef HTL_TMR8_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr8> {
				static constexpr uint32_t timAddr = TIM8_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t activatePos = RCC_APB2ENR_TIM8EN_Pos;
			};
			#endif

			#ifdef HTL_TMR9_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr9> {
				static constexpr uint32_t timAddr = TIM9_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t activatePos = RCC_APB2ENR_TIM9EN_Pos;
			};
			#endif

			#ifdef HTL_TMR10_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr10> {
				static constexpr uint32_t timAddr = TIM10_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t activatePos = RCC_APB2ENR_TIM10EN_Pos;
			};
			#endif

			#ifdef HTL_TMR11_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr11> {
				static constexpr uint32_t timAddr = TIM11_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t activatePos = RCC_APB2ENR_TIM11EN_Pos;
			};
			#endif

			#ifdef HTL_TMR12_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr12> {
				static constexpr uint32_t timAddr = TIM12_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM12EN_Pos;
			};
			#endif

			#ifdef HTL_TMR13_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr13> {
				static constexpr uint32_t timAddr = TIM13_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM13EN_Pos;
			};
			#endif

			#ifdef HTL_TMR14_EXIST
			template <>
			struct TMRTraits<DeviceID::tmr14> {
				static constexpr uint32_t timAddr = TIM14_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_TIM14EN_Pos;
			};
			#endif

		}
	}
}

#endif // __STM32F4_htlTMR_Traits__


