#pragma once
#ifndef __STM32_htlUART_AF_F030R__
#define __STM32_htlUART_AF_F030R__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32F030Rx)


namespace htl {

	#ifdef HTL_UART1_EXIST
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A2, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A3, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A9, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A10, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A14, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A15, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
	#endif

	#ifdef HTL_UART2_EXIST
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_A0, UARTPin::CTS> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_A1, UARTPin::RTS> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_A2, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_A3, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_A14, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
		template <>
		struct UARTPinTrait<UARTChannel::_2, GPIO_A15, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_1;
		};
	#endif
}


#endif // EOS_PLATFORM_STM32F030Rx


#endif // __STM32_htlUART_AF_F030R__

