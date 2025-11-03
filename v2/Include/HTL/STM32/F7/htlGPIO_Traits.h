#pragma once
#ifndef __STM32F7_htlGPIO_Traits__
#define __STM32F7_htlGPIO_Traits__


#include "HTL/htl.h"


namespace htl {
	namespace gpio {
		namespace internal {
#ifdef HTL_GPIOA_EXIST
			template<>
			struct PortTraits<PortID::portA> {
				static constexpr uint32_t gpioAddr = GPIOA_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOAEN_Pos;
			};
#endif
#ifdef HTL_GPIOB_EXIST
			template  <>
			struct PortTraits<PortID::portB> {
				static constexpr uint32_t gpioAddr = GPIOB_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOBEN_Pos;
			};
#endif
#ifdef HTL_GPIOC_EXIST
			template  <>
			struct PortTraits<PortID::portC> {
				static constexpr uint32_t gpioAddr = GPIOC_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOCEN_Pos;
			};
#endif
#ifdef HTL_GPIOD_EXIST
			template  <>
			struct PortTraits<PortID::portD> {
				static constexpr uint32_t gpioAddr = GPIOD_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIODEN_Pos;
			};
#endif
#ifdef HTL_GPIOE_EXIST
			template  <>
			struct PortTraits<PortID::portE> {
				static constexpr uint32_t gpioAddr = GPIOE_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOEEN_Pos;
			};
#endif
#ifdef HTL_GPIOF_EXIST
			template  <>
			struct PortTraits<PortID::portF> {
				static constexpr uint32_t gpioAddr = GPIOF_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOFEN_Pos;
			};
#endif
#ifdef HTL_GPIOG_EXIST
			template  <>
			struct PortTraits<PortID::portG> {
				static constexpr uint32_t gpioAddr = GPIOG_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOGEN_Pos;
			};
#endif
#ifdef HTL_GPIOH_EXIST
			template  <>
			struct PortTraits<PortID::portH> {
				static constexpr uint32_t gpioAddr = GPIOH_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOHEN_Pos;
			};
#endif
#ifdef HTL_GPIOI_EXIST
			template  <>
			struct PortTraits<PortID::portI> {
				static constexpr uint32_t gpioAddr = GPIOI_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOIEN_Pos;
			};
#endif
#ifdef HTL_GPIOJ_EXIST
			template  <>
			struct PortTraits<PortID::portJ> {
				static constexpr uint32_t gpioAddr = GPIOJ_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOJEN_Pos;
			};
#endif
#ifdef HTL_GPIOK_EXIST
			template  <>
			struct PortTraits<PortID::portK> {
				static constexpr uint32_t gpioAddr = GPIOK_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOKEN_Pos;
			};
#endif
		}
	}
}


#endif // __STM32F7_htlGPIO_Traits__
