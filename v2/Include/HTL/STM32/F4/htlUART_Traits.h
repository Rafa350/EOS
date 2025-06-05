#pragma once
#ifndef __STM32F4_htlUART_Traits__
#define __STM32F4_htlUART_traits__


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
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
                static constexpr uint32_t activatePos = RCC_APB2ENR_USART1EN_Pos;

                static constexpr bool isRTOAvailable = false;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk2;
			};
#endif

#ifdef HTL_UART2_EXIST
			template <>
			struct UARTTraits<DeviceID::uart2> {
				static constexpr uint32_t usartAddr = USART2_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_USART2EN_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool isRTOAvailable = true;
			};
#endif

#ifdef HTL_UART3_EXIST
			template <>
			struct UARTTraits<DeviceID::uart3> {
				static constexpr uint32_t usartAddr = USART3_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_USART3EN_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool isRTOAvailable = true;
			};
#endif

#ifdef HTL_UART4_EXIST
			template <>
			struct UARTTraits<DeviceID::uart4> {
				static constexpr uint32_t usartAddr = UART4_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_UART4EN_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool isRTOAvailable = true;
			};
#endif

#ifdef HTL_UART5_EXIST
			template <>
			struct UARTTraits<DeviceID::uart5> {
				static constexpr uint32_t usartAddr = UART5_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_UART5EN_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool isRTOAvailable = true;
			};
#endif

#ifdef HTL_UART6_EXIST
			template <>
			struct UARTTraits<DeviceID::uart6> {
				static constexpr uint32_t usartAddr = USART6_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
                static constexpr uint32_t activatePos = RCC_APB2ENR_USART6EN_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk2;

                static constexpr bool isRTOAvailable = true;
			};
#endif

#ifdef HTL_UART7_EXIST
			template <>
			struct UARTTraits<DeviceID::uart7> {
				static constexpr uint32_t usartAddr = UART7_BASE;
                static constexpr uint32_t activateAddrAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_UART7EN_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool isRTOAvailable = true;
			};
#endif

#ifdef HTL_UART8_EXIST
			template <>
			struct UARTTraits<DeviceID::uart8> {
				static constexpr uint32_t usartAddr = UART8_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_UART8EN_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool isRTOAvailable = true;
			};
#endif
		}
	}
}


#endif // __STM32F4_htlUART_Traits__
