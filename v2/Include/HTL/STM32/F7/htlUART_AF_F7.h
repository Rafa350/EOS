#pragma once
#ifndef __STM32_F7_htlUART_AF_F7__
#define __STM32_F7_htlUART_AF_F7__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F7)


namespace htl {

	#ifdef HTL_UART1_EXIST
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A9, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_B7, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};
	#endif

	#ifdef HTL_UART2_EXIST
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_A9, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_B7, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};
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


#endif // EOS_PLATFORM_STM32F7


#endif // __STM32_F7_htlUART_AF_F7__

