#pragma once
#ifndef __2D12CC9818DA413D87B5DFBC2192F24A__
#define __2D12CC9818DA413D87B5DFBC2192F24A__


#if !defined(EOS_PLATFORM_STM32G0B1)
    #error 'Unsupported platform'
#endif


namespace htl::can::internal {

    #if defined(HTL_CAN1_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::can1, PinFunction::tx, htl::gpio::PortID::portA, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can1, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can1, PinFunction::tx, htl::gpio::PortID::portD, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can1, PinFunction::rx, htl::gpio::PortID::portA, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can1, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can1, PinFunction::rx, htl::gpio::PortID::portD, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    #endif

    #if defined(HTL_CAN2_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::tx, htl::gpio::PortID::portB, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::tx, htl::gpio::PortID::portD, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::rx, htl::gpio::PortID::portB, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    template<>
    struct PinFunctionInfo<DeviceID::can2, PinFunction::rx, htl::gpio::PortID::portD, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_3;
    };
    #endif

}


#endif

