#pragma once
#ifndef __STM32F0_htlGPIO_Traits__
#define __STM32F0_htlGPIO_Traits__


// HAL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32F0)
	#error "Valid for STM32F0 platform only"
#endif


namespace htl {
	namespace gpio {
		namespace internal {

#ifdef HTL_GPIOA_EXIST
			template<>
			struct PortTraits<PortID::portA> {
				static constexpr uint32_t gpioAddr = GPIOA_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOAEN_Pos;
			};
#endif

#ifdef HTL_GPIOB_EXIST
			template  <>
			struct PortTraits<PortID::portB> {
				static constexpr uint32_t gpioAddr = GPIOB_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOBEN_Pos;
			};
#endif

#ifdef HTL_GPIOC_EXIST
			template  <>
			struct PortTraits<PortID::portC> {
				static constexpr uint32_t gpioAddr = GPIOC_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOCEN_Pos;
			};
#endif

#ifdef HTL_GPIOD_EXIST
			template  <>
			struct PortTraits<PortID::portD> {
				static constexpr uint32_t gpioAddr = GPIOD_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIODEN_Pos;
			};
#endif

#ifdef HTL_GPIOF_EXIST
			template  <>
			struct PortTraits<PortID::portF> {
				static constexpr uint32_t gpioAddr = GPIOF_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOFEN_Pos;
			};
#endif

		}
	}
}


#endif // __STM32F0_htlGPIO_Traits__
