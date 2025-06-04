#pragma once
#ifndef __STM32F7_htlUART_Traits__
#define __STM32F7_htlUART_traits__


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

                static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_USART1SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_USART1SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk2;
			};
#endif

#ifdef HTL_UART2_EXIST
			template <>
			struct UARTTraits<DeviceID::uart2> {
				static constexpr uint32_t usartAddr = USART2_BASE;

				static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_USART2SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_USART2SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool supportedRxTimeout = true;
			};
#endif

#ifdef HTL_UART3_EXIST
			template <>
			struct UARTTraits<DeviceID::uart3> {
				static constexpr uint32_t usartAddr = USART3_BASE;

				static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_USART3SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_USART3SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool supportedRxTimeout = true;
			};
#endif

#ifdef HTL_UART4_EXIST
			template <>
			struct UARTTraits<DeviceID::uart4> {
				static constexpr uint32_t usartAddr = UART4_BASE;

				static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_UART4SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_UART4SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool supportedRxTimeout = true;
			};
#endif

#ifdef HTL_UART5_EXIST
			template <>
			struct UARTTraits<DeviceID::uart5> {
				static constexpr uint32_t usartAddr = UART5_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_UART5EN_Pos;

                static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_UART5SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_UART5SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool supportedRxTimeout = true;
			};
#endif

#ifdef HTL_UART6_EXIST
			template <>
			struct UARTTraits<DeviceID::uart6> {
				static constexpr uint32_t usartAddr = USART6_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
                static constexpr uint32_t activatePos = RCC_APB2ENR_USART6EN_Pos;

                static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_USART6SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_USART6SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk2;

                static constexpr bool supportedRxTimeout = true;
			};
#endif

#ifdef HTL_UART7_EXIST
			template <>
			struct UARTTraits<DeviceID::uart7> {
				static constexpr uint32_t usartAddr = UART7_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_UART7EN_Pos;

                static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_UART7SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_UART7SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool supportedRxTimeout = true;
			};
#endif

#ifdef HTL_UART8_EXIST
			template <>
			struct UARTTraits<DeviceID::uart8> {
				static constexpr uint32_t usartAddr = UART8_BASE;
                static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
                static constexpr uint32_t activatePos = RCC_APB1ENR_UART8EN_Pos;

                static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, DCKCFGR2);
                static constexpr uint32_t clockSourceMsk = RCC_DCKCFGR2_UART8SEL_Msk;
                static constexpr uint32_t clockSourcePos = RCC_DCKCFGR2_UART8SEL_Pos;

                static constexpr clock::ClockID pclkX = clock::ClockID::pclk1;

                static constexpr bool supportedRxTimeout = true;
			};
#endif
		}
	}
}


#endif // __STM32F7_htlUART_Traits__
