#pragma once
#ifndef __F14A5458FC2D44F7BED08C7EB2E50299__
#define __F14A5458FC2D44F7BED08C7EB2E50299__


#if !defined(EOS_PLATFORM_STM32G071)
    #error 'Unsupported platform'
#endif


namespace htl::i2c::internal {

    #if defined(HTL_I2C1_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::scl, htl::gpio::PortID::portA, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::scl, htl::gpio::PortID::portB, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::scl, htl::gpio::PortID::portB, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::scl, htl::gpio::PortID::portB, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::sda, htl::gpio::PortID::portA, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::sda, htl::gpio::PortID::portB, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::sda, htl::gpio::PortID::portB, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::sda, htl::gpio::PortID::portB, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::smba, htl::gpio::PortID::portA, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c1, PinFunction::smba, htl::gpio::PortID::portB, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    #endif

    #if defined(HTL_I2C2_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::i2c2, PinFunction::scl, htl::gpio::PortID::portA, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c2, PinFunction::scl, htl::gpio::PortID::portB, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c2, PinFunction::scl, htl::gpio::PortID::portB, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c2, PinFunction::sda, htl::gpio::PortID::portA, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c2, PinFunction::sda, htl::gpio::PortID::portB, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::i2c2, PinFunction::sda, htl::gpio::PortID::portB, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    #endif

}


#endif

