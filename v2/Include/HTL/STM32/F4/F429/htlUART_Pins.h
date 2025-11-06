#pragma once
#ifndef __C416FEC4660B4D6B986C41909A10F9DC__
#define __C416FEC4660B4D6B986C41909A10F9DC__


#if !defined(EOS_PLATFORM_STM32F429)
    #error 'Unsupported platform'
#endif


namespace htl::uart::internal {

    #if defined(HTL_UART1_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart1, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    #endif

    #if defined(HTL_UART2_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::tx, htl::gpio::PortID::portD, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart2, PinFunction::rx, htl::gpio::PortID::portD, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    #endif

    #if defined(HTL_UART3_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::tx, htl::gpio::PortID::portC, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::tx, htl::gpio::PortID::portD, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rx, htl::gpio::PortID::portC, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart3, PinFunction::rx, htl::gpio::PortID::portD, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_7;
    };
    #endif

    #if defined(HTL_UART4_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart4, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_8;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart4, PinFunction::tx, htl::gpio::PortID::portC, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_8;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart4, PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_8;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart4, PinFunction::rx, htl::gpio::PortID::portC, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_8;
    };
    #endif

    #if defined(HTL_UART5_EXIST)
    #endif

    #if defined(HTL_UART6_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::uart6, PinFunction::tx, htl::gpio::PortID::portC, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_8;
    };
    template<>
    struct PinFunctionInfo<DeviceID::uart6, PinFunction::rx, htl::gpio::PortID::portC, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_8;
    };
    #endif

    #if defined(HTL_UART7_EXIST)
    #endif

    #if defined(HTL_UART8_EXIST)
    #endif

}


#endif

