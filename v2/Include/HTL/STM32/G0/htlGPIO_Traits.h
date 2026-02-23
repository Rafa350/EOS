#pragma once
#ifndef __STM32G0_htlGPIO_Traits__
#define __STM32G0_htlGPIO_Traits__


// HTL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32G0)
	#error "Valid for STM32G0 platform only"
#endif


namespace htl {
	namespace gpio {
		namespace internal {
#ifdef HTL_GPIOA_EXIST
			template <>
			struct PortTraits<PortID::portA> {
				static constexpr uint32_t gpioAddr = GPIOA_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t activatePos = RCC_IOPENR_GPIOAEN_Pos;
			};
#endif
#ifdef HTL_GPIOB_EXIST
			template  <>
			struct PortTraits<PortID::portB> {
				static constexpr uint32_t gpioAddr = GPIOB_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t activatePos = RCC_IOPENR_GPIOBEN_Pos;
			};
#endif
#ifdef HTL_GPIOC_EXIST
			template  <>
			struct PortTraits<PortID::portC> {
				static constexpr uint32_t gpioAddr = GPIOC_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t activatePos = RCC_IOPENR_GPIOCEN_Pos;
			};
#endif
#ifdef HTL_GPIOD_EXIST
			template  <>
			struct PortTraits<PortID::portD> {
				static constexpr uint32_t gpioAddr = GPIOD_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t activatePos = RCC_IOPENR_GPIODEN_Pos;
			};
#endif
#ifdef HTL_GPIOE_EXIST
			template  <>
			struct PortTraits<PortID::portE> {
				static constexpr uint32_t gpioAddr = GPIOE_BASE;
			};
#endif
#ifdef HTL_GPIOF_EXIST
			template  <>
			struct PortTraits<PortID::portF> {
				static constexpr uint32_t gpioAddr = GPIOF_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t activatePos = RCC_IOPENR_GPIOFEN_Pos;
			};
#endif
#ifdef HTL_GPIOG_EXIST
			template  <>
			struct PortTraits<PortID::portG> {
				static constexpr uint32_t gpioAddr = GPIOG_BASE;
			};
#endif
#ifdef HTL_GPIOH_EXIST
			template  <>
			struct PortTraits<PortID::portH> {
				static constexpr uint32_t gpioAddr = GPIOH_BASE;
			};
#endif
#ifdef HTL_GPIOI_EXIST
			template  <>
			struct PortTraits<PortID::portI> {
				static constexpr uint32_t gpioAddr = GPIOI_BASE;
			};
#endif
#ifdef HTL_GPIOJ_EXIST
			template  <>
			struct PortTraits<PortID::portJ> {
				static constexpr uint32_t gpioAddr = GPIOJ_BASE;
			};
#endif
#ifdef HTL_GPIOK_EXIST
			template  <>
			struct PortTraits<PortID::portK> {
				static constexpr uint32_t gpioAddr = GPIOK_BASE;
			};
#endif
		}
	}
}


#endif // __htlGPIO_Traits__
