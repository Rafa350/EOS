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
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rx, gpio::PortID::portA, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::cts, gpio::PortID::portA, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::cts, gpio::PortID::portB, gpio::PinID::pin4> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rts, gpio::PortID::portA, gpio::PinID::pin12> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rts, gpio::PortID::portA, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    #endif // USART1_BASE

    #if defined(USART2_BASE)
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::tx, gpio::PortID::portA, gpio::PinID::pin2> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::tx, gpio::PortID::portA, gpio::PinID::pin14> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rx, gpio::PortID::portA, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rx, gpio::PortID::portA, gpio::PinID::pin15> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::cts, gpio::PortID::portA, gpio::PinID::pin0> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::cts, gpio::PortID::portD, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rts, gpio::PortID::portA, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    #endif // USART2_BASE

    #if defined(USART3_BASE)
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, gpio::PortID::portA, gpio::PinID::pin4> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin2> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin8> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin0> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin9> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::cts, gpio::PortID::portA, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::cts, gpio::PortID::portB, gpio::PinID::pin13> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rts, gpio::PortID::portA, gpio::PinID::pin15> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rts, gpio::PortID::portB, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rts, gpio::PortID::portB, gpio::PinID::pin14> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    #endif // USART3_BASE
}
