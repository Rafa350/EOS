#pragma once
#ifndef __STM32_htlUART_AF_G031__
#define __STM32_htlUART_AF_GO31__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G031) 


namespace htl {
	#ifdef HTL_UART1_EXIST
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_A9, UARTPin::TX> {
            static constexpr GPIOAlt alt = GPIOAlt::_1;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_A10, UARTPin::RX> {
            static constexpr GPIOAlt alt = GPIOAlt::_1;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_A11, UARTPin::CTS> {
            static constexpr GPIOAlt alt = GPIOAlt::_1;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_A12, UARTPin::RTS> {
            static constexpr GPIOAlt alt = GPIOAlt::_1;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_B3, UARTPin::RTS> {
            static constexpr GPIOAlt alt = GPIOAlt::_4;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_B4, UARTPin::CTS> {
            static constexpr GPIOAlt alt = GPIOAlt::_4;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_B6, UARTPin::TX> {
            static constexpr GPIOAlt alt = GPIOAlt::_1;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_B7, UARTPin::RX> {
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


#endif // EOS_PLATFORM_STM32G031


#endif // __STM32_htlUART_AF_G031__

