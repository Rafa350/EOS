#pragma once
#ifndef __EA0D543B93F74B2083B88FE0573DF497__
#define __EA0D543B93F74B2083B88FE0573DF497__


#if !defined(EOS_PLATFORM_STM32G0B1)
    #error 'Unsupported platform'
#endif


namespace htl::uart::internal {

    #if defined(HTL_UART1_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::cts, htl::gpio::PortID::portA, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::cts, htl::gpio::PortID::portB, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::rts, htl::gpio::PortID::portA, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::rts, htl::gpio::PortID::portA, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    #endif

    #if defined(HTL_UART2_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::cts, htl::gpio::PortID::portA, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::cts, htl::gpio::PortID::portD, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::rts, htl::gpio::PortID::portA, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    #endif

    #if defined(HTL_UART3_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::cts, htl::gpio::PortID::portA, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::cts, htl::gpio::PortID::portB, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rts, htl::gpio::PortID::portA, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rts, htl::gpio::PortID::portB, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rts, htl::gpio::PortID::portB, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    #endif

}


#endif

