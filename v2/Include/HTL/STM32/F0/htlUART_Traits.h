#pragma once
#ifndef __STM32F0_htlUART_Traits__
#define __STM32F0_htlUART_Traits__


// HAL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
#if !defined(EOS_PLATFORM_STM32F0)
	#error "Valid for STM32F0 platform only"
#endif


namespace htl {
	namespace uart {
		namespace internal {

			#ifdef HTL_UART1_EXIST
			template <>
			struct UARTTraits<DeviceID::uart1> {
				static constexpr uint32_t usartAddr = USART1_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t activatePos = RCC_APB2ENR_USART1EN_Pos;

				static constexpr uint32_t clockSourcerAddr = RCC_BASE + offsetof(RCC_TypeDef, CFGR3);
				static constexpr uint32_t clockSourceMsk = RCC_CFGR3_USART1SW_Msk;
				static constexpr uint32_t clockSourcePos = RCC_CFGR3_USART1SW_Pos;
			};
			#endif

			#ifdef HTL_UART2_EXIST
			template <>
			struct UARTTraits<DeviceID::uart2> {
				static constexpr uint32_t usartAddr = USART2_BASE;
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t activatePos = RCC_APB1ENR_USART2EN_Pos;
			};
			#endif

			#ifdef HTL_UART3_EXIST
			template <>
			struct UARTTraits<DeviceID::uart3> {
			};
			#endif

			#ifdef HTL_UART4_EXIST
			template <>
			struct UARTTraits<DeviceID::uart4> {
			};
			#endif

		}
	}
}


#endif // __STM32F0_htlUART_Traits__
