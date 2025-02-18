#pragma once
#ifndef __579DDBD6C0AB4769A55950710125E1C7__
#define __579DDBD6C0AB4769A55950710125E1C7__


#if !defined(EOS_PLATFORM_STM32F030)
    #error 'Unsupported platform'
#endif


namespace htl::tmr::internal {

    #if defined(HTL_TMR3_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::tmr3, PinFunction::ch1, htl::gpio::PortID::portA, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::tmr3, PinFunction::ch1, htl::gpio::PortID::portB, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::tmr3, PinFunction::ch2, htl::gpio::PortID::portA, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::tmr3, PinFunction::ch2, htl::gpio::PortID::portB, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::tmr3, PinFunction::ch3, htl::gpio::PortID::portB, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::tmr3, PinFunction::ch4, htl::gpio::PortID::portB, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    #endif

}


#endif

