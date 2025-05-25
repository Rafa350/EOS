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
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_USART1EN_Pos;
				static constexpr bool isFIFOAvailable = true;
			};
			#endif

			#ifdef HTL_UART2_EXIST
			template <>
			struct UARTTraits<DeviceID::uart2> {
				static constexpr uint32_t usartAddr = USART2_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART2EN_Pos;
				static constexpr bool isFIFOAvailable = true;
				static constexpr bool supportedRxTimeout = false;
			};
			#endif

			#ifdef HTL_UART3_EXIST
			template <>
			struct UARTTraits<DeviceID::uart3> {
				static constexpr uint32_t usartAddr = USART3_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART3EN_Pos;
				static constexpr bool supportedRxTimeout = false;
			};
			#endif

			#ifdef HTL_UART4_EXIST
			template <>
			struct UARTTraits<DeviceID::uart4> {
				static constexpr uint32_t usartAddr = USART4_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART4EN_Pos;
				static constexpr bool supportedRxTimeout = false;
			};
			#endif

			#ifdef HTL_UART5_EXIST
			template <>
			struct UARTTraits<DeviceID::uart5> {
				static constexpr uint32_t usartAddr = USART5_BASE;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART6_EXIST
			template <>
			struct UARTTraits<DeviceID::uart6> {
				static constexpr uint32_t usartAddr = USART6_BASE;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

		}
	}
}


#endif // __STM32G0_htlUART_Traits__
