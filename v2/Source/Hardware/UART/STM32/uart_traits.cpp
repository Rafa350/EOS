module;


#include "HTL/htl.h"


export module Eos.Hardware.UART.Traits;


import Eos.Hardware.UART.Identifiers;
import Eos.Types;


export namespace eos::hardware::uart::internal {

    template <UARTDeviceID>
    struct UARTTraits;

#ifdef HTL_UART1_EXIST
    template <>
    struct UARTTraits<UARTDeviceID::uart1> {
        static constexpr UInt32 usartAddr = USART1_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
        static constexpr UInt32 activatePos = RCC_APBENR2_USART1EN_Pos;

        static constexpr UInt32 clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR);
        static constexpr UInt32 clockSourcePos = RCC_CCIPR_USART1SEL_Pos;
        static constexpr UInt32 clockSourceMsk = RCC_CCIPR_USART1SEL_Msk;

        static constexpr bool isFIFOAvailable = true;
        static constexpr bool isRTOAvailable = true;
    };
#endif

#ifdef HTL_UART2_EXIST
    template <>
    struct UARTTraits<UARTDeviceID::uart2> {
        static constexpr UInt32 usartAddr = USART2_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_USART2EN_Pos;

        static constexpr UInt32 clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR);
        static constexpr UInt32 clockSourcePos = RCC_CCIPR_USART2SEL_Pos;
        static constexpr UInt32 clockSourceMsk = RCC_CCIPR_USART2SEL_Msk;

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
    struct UARTTraits<UARTDeviceID::uart3> {
        static constexpr UInt32 usartAddr = USART3_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_USART3EN_Pos;

#if defined(EOS_PLATFORM_STM32G0B1) || defined(EOS_PLATFORM_STM32G0C1)
        static constexpr UInt32 clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR);
        static constexpr UInt32 clockSourcePos = RCC_CCIPR_USART3SEL_Pos;
        static constexpr UInt32 clockSourceMsk = RCC_CCIPR_USART3SEL_Msk;
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
    struct UARTTraits<UARTDeviceID::uart4> {
        static constexpr UInt32 usartAddr = USART4_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_USART4EN_Pos;

        static constexpr bool isFIFOAvailable = false;
        static constexpr bool isRTOAvailable = false;
    };
#endif

#ifdef HTL_UART5_EXIST
    template <>
    struct UARTTraits<UARTDeviceID::uart5> {
        static constexpr UInt32 usartAddr = USART5_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_USART5EN_Pos;

        static constexpr bool isFIFOAvailable = false;
        static constexpr bool isRTOAvailable = false;
    };
#endif

#ifdef HTL_UART6_EXIST
    template <>
    struct UARTTraits<UARTDeviceID::uart6> {
        static constexpr UInt32 usartAddr = USART6_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_USART6EN_Pos;

        static constexpr bool isFIFOAvailable = false;
        static constexpr bool isRTOAvailable = false;
    };
#endif
}
