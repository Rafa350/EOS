module;


#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.UART._DeviceTraits;


import Eos.Hardware.Clock;
import Eos.Hardware.UART._Types;
import Eos.Hardware.Interrupts;
import Eos.Types;


namespace eos::hardware::uart::internal {

    export {

        template <UARTDeviceID>
        struct UARTTraits;

#ifdef USART1_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart1> {
            static constexpr UInt32 usartAddr = USART1_BASE;

            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
            static constexpr UInt32 activatePos  = RCC_APB2ENR_USART1EN_Pos;

            static constexpr bool isRTOAvailable = false;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk2;
        };
#endif

#ifdef USART2_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart2> {
            static constexpr UInt32 usartAddr = USART2_BASE;

            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
            static constexpr UInt32 activatePos  = RCC_APB1ENR_USART2EN_Pos;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk1;

            static constexpr bool isRTOAvailable = true;
        };
#endif

#ifdef USART3_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart3> {
            static constexpr UInt32 usartAddr = USART3_BASE;

            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
            static constexpr UInt32 activatePos  = RCC_APB1ENR_USART3EN_Pos;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk1;

            static constexpr bool isRTOAvailable = true;
        };
#endif

#ifdef UART4_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart4> {
            static constexpr UInt32 usartAddr  = UART4_BASE;

            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
            static constexpr UInt32 activatePos = RCC_APB1ENR_UART4EN_Pos;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk1;

            static constexpr bool isRTOAvailable = true;
        };
#endif

#ifdef UART5_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart5> {
            static constexpr UInt32 usartAddr = UART5_BASE;

            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
            static constexpr UInt32 activatePos = RCC_APB1ENR_UART5EN_Pos;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk1;

            static constexpr bool isRTOAvailable = true;
        };
#endif

#ifdef USART6_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart6> {
            static constexpr UInt32 usartAddr = USART6_BASE;

            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
            static constexpr UInt32 activatePos = RCC_APB2ENR_USART6EN_Pos;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk2;

            static constexpr bool isRTOAvailable = true;
        };
#endif

#ifdef UART7_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart7> {
            static constexpr UInt32 usartAddr = UART7_BASE;

            static constexpr UInt32 activateAddrAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
            static constexpr UInt32 activatePos = RCC_APB1ENR_UART7EN_Pos;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk1;

            static constexpr bool isRTOAvailable = true;
        };
#endif

#ifdef UART8_BASE
        template <>
        struct UARTTraits<UARTDeviceID::uart8> {
            static constexpr UInt32 usartAddr = UART8_BASE;

            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
            static constexpr UInt32 activatePos = RCC_APB1ENR_UART8EN_Pos;

            static constexpr clock::Clock::ClockID pclkX = clock::Clock::ClockID::pclk1;

            static constexpr bool isRTOAvailable = true;
        };
#endif
    }
}
