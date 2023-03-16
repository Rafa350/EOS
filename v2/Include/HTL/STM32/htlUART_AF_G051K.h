#pragma once
#ifndef __STM32_htlUART_AF_G051K__
#define __STM32_htlUART_AF_GO51K__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


#if defined(EOS_PLATFORM_STM32G051Kx) 


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
        struct UARTPinTrait<UARTChannel::_1, GPIO_B6, UARTPin::TX> {
            static constexpr GPIOAlt alt = GPIOAlt::_0;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_1, GPIO_B7, UARTPin::RX> {
            static constexpr GPIOAlt alt = GPIOAlt::_0;
        };
	#endif

	#ifdef HTL_UART2_EXIST
        template <>
        struct UARTPinTrait<UARTChannel::_2, GPIO_A0, UARTPin::CTS> {
            static constexpr GPIOAlt alt = GPIOAlt::_1;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_2, GPIO_A1, UARTPin::RST> {
            static constexpr GPIOAlt alt = GPIOAlt::_1;
        };
        template <>
        struct UARTPinTrait<UARTChannel::_2, GPIO_A2, UARTPin::TX> {
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


#endif // EOS_PLATFORM_STM32G051Kx


#endif // __STM32_htlUART_AF_G051K__

