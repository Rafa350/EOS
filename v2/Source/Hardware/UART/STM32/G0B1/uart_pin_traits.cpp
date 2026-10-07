module;


#include "HTL/htl.h"
#include "HTL/htlGPIO.h"
#include <concepts>


export module Eos.Hardware.UART.__PIN_TRAITS;


import Eos.Hardware.UART.__PLATFORM_TRAITS;


namespace g = htl::gpio;


namespace eos::hardware::uart::internal {

	using UARTDeviceID = PlatformTraits::DeviceID;
}

export namespace eos::hardware::uart::internal {

    enum class PinFunction { tx, rx, cts, rts, de };

    template <UARTDeviceID, PinFunction, g::PortID, g::PinID>
    struct PinTraits {
    };

    #if defined(HTL_UART1_EXIST)
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::tx, g::PortID::portA, g::PinID::pin9> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::tx, g::PortID::portB, g::PinID::pin6> {
        static constexpr auto value = g::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rx, g::PortID::portA, g::PinID::pin10> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rx, g::PortID::portB, g::PinID::pin7> {
        static constexpr auto value = g::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::cts, g::PortID::portA, g::PinID::pin11> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::cts, g::PortID::portB, g::PinID::pin4> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rts, g::PortID::portA, g::PinID::pin12> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart1, PinFunction::rts, g::PortID::portA, g::PinID::pin3> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    #endif

    #if defined(HTL_UART2_EXIST)
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::tx, g::PortID::portA, g::PinID::pin2> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::tx, g::PortID::portA, g::PinID::pin14> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rx, g::PortID::portA, g::PinID::pin3> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rx, g::PortID::portA, g::PinID::pin15> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::cts, g::PortID::portA, g::PinID::pin0> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::cts, g::PortID::portD, g::PinID::pin3> {
        static constexpr auto value = g::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart2, PinFunction::rts, g::PortID::portA, g::PinID::pin1> {
        static constexpr auto value = g::AlternateFunction::_1;
    };
    #endif

    #if defined(HTL_UART3_EXIST)
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, g::PortID::portA, g::PinID::pin4> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, g::PortID::portB, g::PinID::pin2> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, g::PortID::portB, g::PinID::pin8> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::tx, g::PortID::portB, g::PinID::pin10> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, g::PortID::portB, g::PinID::pin0> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, g::PortID::portB, g::PinID::pin9> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rx, g::PortID::portB, g::PinID::pin11> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::cts, g::PortID::portA, g::PinID::pin6> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::cts, g::PortID::portB, g::PinID::pin13> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rts, g::PortID::portA, g::PinID::pin15> {
        static constexpr auto value = g::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rts, g::PortID::portB, g::PinID::pin1> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<UARTDeviceID::uart3, PinFunction::rts, g::PortID::portB, g::PinID::pin14> {
        static constexpr auto value = g::AlternateFunction::_4;
    };
    #endif
}
