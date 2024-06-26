#pragma once
#ifndef __STM32_F4_htlUART_AF_F4__
#define __STM32_F4_htlUART_AF_F4__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F4)


namespace htl {
	#ifdef HTL_UART1_EXIST
		#if defined(EOD_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			template <>
			struct UARTPinTrait<UARTChannel::_1, GPIO_A9, UARTPin::TX> {
				static constexpr GPIOAlt alt = GPIOAlt::_8;
			};
			template <>
			struct UARTPinTrait<UARTChannel::_1, GPIO_B7, UARTPin::RX> {
				static constexpr GPIOAlt alt = GPIOAlt::_8;
			};
		#endif
	#endif

	#ifdef HTL_UART2_EXIST
		template <>
		struct UARTTrait<UARTChannel::_2> {
			static constexpr uint32_t addr = USART2_BASE;
			static constexpr INTVector vector = INTVector::uart2;
			#if defined(EOS_PLATFORM_STM32F0)
				static constexpr bool supportedRxTimeout = false;
			#elif defined(EOS_PLATFORM_STM32F4)
				static constexpr bool supportedRxTimeout = true;
			#else
				#error Plataforma no soportada
			#endif
		};

		#if defined(EOD_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			template <>
			struct UARTPinTrait<UARTChannel::_2, GPIO_A9, UARTPin::TX> {
				static constexpr GPIOAlt alt = GPIOAlt::_8;
			};
			template <>
			struct UARTPinTrait<UARTChannel::_2, GPIO_B7, UARTPin::RX> {
				static constexpr GPIOAlt alt = GPIOAlt::_8;
			};
		#endif
	#endif

	#ifdef HTL_UART3_EXIST
	#endif

	#ifdef HTL_UART4_EXIST
	#endif

	#ifdef HTL_UART5_EXIST
	#endif

	#ifdef HTL_UART6_EXIST
		template <>
		struct UARTPinTrait<UARTChannel::_6, GPIO_C6, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};

		template <>
		struct UARTPinTrait<UARTChannel::_6, GPIO_C7, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};
	#endif

	#ifdef HTL_UART7_EXIST
	#endif

	#ifdef HTL_UART8_EXIST
	#endif
}


#endif // EOS_PLATFORM_STM32F4


#endif // __STM32_F4_htlUART_AF_F7__

