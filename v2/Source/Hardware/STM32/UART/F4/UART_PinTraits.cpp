module;

#include "hardware.h"


export module Eos.Hardware.UART._PinTraits;


import Eos.Hardware.GPIO;
import Eos.Hardware.UART._Types;


export namespace eos::hardware::uart::internal {

    enum class PinFunction { tx, rx, cts, rts, de };

    template <UARTDeviceID, PinFunction, gpio::PortID, gpio::PinID>
    struct PinTraits;

    #if defined(USART1_BASE)
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::tx, gpio::PortID::portA, gpio::PinID::pin9> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rx, gpio::PortID::portA, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    #endif

    #if defined(USART2_BASE)
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::tx, gpio::PortID::portA, gpio::PinID::pin2> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::tx, gpio::PortID::portD, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rx, gpio::PortID::portA, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rx, gpio::PortID::portD, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    #endif

    #if defined(USART3_BASE)
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, gpio::PortID::portC, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, gpio::PortID::portD, gpio::PinID::pin8> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, gpio::PortID::portC, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, gpio::PortID::portD, gpio::PinID::pin9> {
        static constexpr auto value = gpio::AlternateFunction::_7;
    };
    #endif

    #if defined(UART4_BASE)
    template<>
    struct PinTraits<UARTDeviceID::uart4, PinFunction::tx, gpio::PortID::portA, gpio::PinID::pin0> {
        static constexpr auto value = gpio::AlternateFunction::_8;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart4, PinFunction::tx, gpio::PortID::portC, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_8;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart4, PinFunction::rx, gpio::PortID::portA, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_8;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart4, PinFunction::rx, gpio::PortID::portC, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_8;
    };
    #endif

    #if defined(UART5_BASE)
    #endif

    #if defined(USART6_BASE)
    template<>
    struct PinTraits<UARTDeviceID::uart6, PinFunction::tx, gpio::PortID::portC, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_8;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart6, PinFunction::rx, gpio::PortID::portC, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_8;
    };
    #endif

    #if defined(USART7_BASE)
    #endif

    #if defined(USART8_BASE)
    #endif
}
