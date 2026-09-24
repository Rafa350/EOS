module;


#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.UART.Pins;


import Eos.Hardware.UART.Identifiers;


namespace g = htl::gpio;


export namespace eos::hardware::uart {

    namespace internal {

        enum class PinUse {
            tx,
            rx,
            cts,
            rts,
            de
        };

        template <UARTDeviceID, PinUse, g::PortID, g::PinID>
        struct PinTraits;

        #if defined(HTL_UART1_EXIST)
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::tx, g::PortID::portA, g::PinID::pin9> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::tx, g::PortID::portB, g::PinID::pin6> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::rx, g::PortID::portA, g::PinID::pin10> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::rx, g::PortID::portB, g::PinID::pin7> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::cts, g::PortID::portA, g::PinID::pin11> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::cts, g::PortID::portB, g::PinID::pin4> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::rts, g::PortID::portA, g::PinID::pin12> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart1, PinUse::rts, g::PortID::portA, g::PinID::pin3> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        #endif

        #if defined(HTL_UART2_EXIST)
        template<>
        struct PinTraits<UARTDeviceID::uart2, PinUse::tx, g::PortID::portA, g::PinID::pin2> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart2, PinUse::tx, g::PortID::portA, g::PinID::pin14> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart2, PinUse::rx, g::PortID::portA, g::PinID::pin3> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart2, PinUse::rx, g::PortID::portA, g::PinID::pin15> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart2, PinUse::cts, g::PortID::portA, g::PinID::pin0> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart2, PinUse::cts, g::PortID::portD, g::PinID::pin3> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart2, PinUse::rts, g::PortID::portA, g::PinID::pin1> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
        #endif

        #if defined(HTL_UART3_EXIST)
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::tx, g::PortID::portA, g::PinID::pin4> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::tx, g::PortID::portB, g::PinID::pin2> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::tx, g::PortID::portB, g::PinID::pin8> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::tx, g::PortID::portB, g::PinID::pin10> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::rx, g::PortID::portB, g::PinID::pin0> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::rx, g::PortID::portB, g::PinID::pin9> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::rx, g::PortID::portB, g::PinID::pin11> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::cts, g::PortID::portA, g::PinID::pin6> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::cts, g::PortID::portB, g::PinID::pin13> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::rts, g::PortID::portA, g::PinID::pin15> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_5;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::rts, g::PortID::portB, g::PinID::pin1> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<UARTDeviceID::uart3, PinUse::rts, g::PortID::portB, g::PinID::pin14> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_4;
        };
        #endif
    }
}
