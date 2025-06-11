#pragma once
#ifndef __C8962654D1E741619889E55290DC7133__
#define __C8962654D1E741619889E55290DC7133__


#if !defined(EOS_PLATFORM_STM32G0B1)
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

