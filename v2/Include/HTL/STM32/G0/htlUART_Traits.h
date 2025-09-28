#pragma once
#ifndef __STM32G0_htlUART_Traits__
#define __STM32G0_htlUART_traits__


// HAL includes
//
#include "HTL/STM32/htl.h"


namespace htl {
	namespace uart {
		namespace internal {

#ifdef HTL_UART1_EXIST
			template <>
			struct UARTTraits<DeviceID::uart1> {
				static constexpr uint32_t usartAddr = USART1_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t activatePos = RCC_APBENR2_USART1EN_Pos;

				static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR);
				static constexpr uint32_t clockSourcePos = RCC_CCIPR_USART1SEL_Pos;
				static constexpr uint32_t clockSourceMsk = RCC_CCIPR_USART1SEL_Msk;

				static constexpr bool isFIFOAvailable = true;
				static constexpr bool isRTOAvailable = true;
			};
#endif

#ifdef HTL_UART2_EXIST
			template <>
			struct UARTTraits<DeviceID::uart2> {
				static constexpr uint32_t usartAddr = USART2_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t activatePos = RCC_APBENR1_USART2EN_Pos;

				static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR);
				static constexpr uint32_t clockSourcePos = RCC_CCIPR_USART2SEL_Pos;
				static constexpr uint32_t clockSourceMsk = RCC_CCIPR_USART2SEL_Msk;

#if defined(EOS_PLATFORM_STM32G071) || defined(EOS_PLATFORM_STM32G081) || \
    defined(EOS_PLATFORM_STM32G0B1) || defined(EOS_PLATFORM_STM32G0C1)
				static constexpr bool isFIFOAvailable = true;
				static constexpr bool isRTOAvailable = true;
#else
				static constexpr bool isFIFOAvailable = false;
				static constexpr bool isRTOAvailable = false;
#endif
			};
#endif

#ifdef HTL_UART3_EXIST
			template <>
			struct UARTTraits<DeviceID::uart3> {
				static constexpr uint32_t usartAddr = USART3_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t activatePos = RCC_APBENR1_USART3EN_Pos;

#if defined(EOS_PLATFORM_STM32G0B1) || defined(EOS_PLATFORM_STM32G0C1)
				static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR);
				static constexpr uint32_t clockSourcePos = RCC_CCIPR_USART3SEL_Pos;
				static constexpr uint32_t clockSourceMsk = RCC_CCIPR_USART3SEL_Msk;
#endif

#if defined(EOS_PLATFORM_STM32G0B1) || defined(EOS_PLATFORM_STM32G0C1)
				static constexpr bool isFIFOAvailable = true;
				static constexpr bool isRTOAvailable = true;
#else
				static constexpr bool isFIFOAvailable = false;
				static constexpr bool isRTOAvailable = false;
#endif
			};
#endif

#ifdef HTL_UART4_EXIST
			template <>
			struct UARTTraits<DeviceID::uart4> {
				static constexpr uint32_t usartAddr = USART4_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t activatePos = RCC_APBENR1_USART4EN_Pos;

				static constexpr bool isFIFOAvailable = false;
				static constexpr bool isRTOAvailable = false;
			};
#endif

#ifdef HTL_UART5_EXIST
			template <>
			struct UARTTraits<DeviceID::uart5> {
				static constexpr uint32_t usartAddr = USART5_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t activatePos = RCC_APBENR1_USART5EN_Pos;

				static constexpr bool isFIFOAvailable = false;
				static constexpr bool isRTOAvailable = false;
			};
#endif

#ifdef HTL_UART6_EXIST
			template <>
			struct UARTTraits<DeviceID::uart6> {
				static constexpr uint32_t usartAddr = USART6_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t activatePos = RCC_APBENR1_USART6EN_Pos;

				static constexpr bool isFIFOAvailable = false;
				static constexpr bool isRTOAvailable = false;
			};
#endif
		}
	}
}


#endif // __STM32G0_htlUART_Traits__
