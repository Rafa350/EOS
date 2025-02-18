#pragma once
#ifndef __00301F2F78BC47098ACD327B9E6FB193__
#define __00301F2F78BC47098ACD327B9E6FB193__


#if !defined(EOS_PLATFORM_STM32F030)
    #error 'Unsupported platform'
#endif


namespace htl::uart::internal {

    #if defined(HTL_UART1_EXIST)
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::cts, htl::gpio::PortID::portA, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart1, htl::uart::PinFunction::rts, htl::gpio::PortID::portA, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    #endif

    #if defined(HTL_UART2_EXIST)
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart2, htl::uart::PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart2, htl::uart::PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart2, htl::uart::PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart2, htl::uart::PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart2, htl::uart::PinFunction::cts, htl::gpio::PortID::portA, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<htl::uart::DeviceID::uart2, htl::uart::PinFunction::rts, htl::gpio::PortID::portA, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    #endif

}


#endif

