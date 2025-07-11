#pragma once
#ifndef __C151E06264B34EAB9D0A816F29232A7F__
#define __C151E06264B34EAB9D0A816F29232A7F__


#if !defined(EOS_PLATFORM_STM32G071)
    #error 'Unsupported platform'
#endif


namespace htl::spi::internal {

    #if defined(HTL_SPI1_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::sck, htl::gpio::PortID::portA, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::sck, htl::gpio::PortID::portA, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::miso, htl::gpio::PortID::portA, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::miso, htl::gpio::PortID::portA, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::miso, htl::gpio::PortID::portB, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::mosi, htl::gpio::PortID::portA, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::mosi, htl::gpio::PortID::portA, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::mosi, htl::gpio::PortID::portA, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::mosi, htl::gpio::PortID::portB, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    #endif

    #if defined(HTL_SPI2_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portA, htl::gpio::PinID::pin0> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin8> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::miso, htl::gpio::PortID::portA, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::miso, htl::gpio::PortID::portA, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::miso, htl::gpio::PortID::portB, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::miso, htl::gpio::PortID::portB, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_4;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::miso, htl::gpio::PortID::portB, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portA, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portA, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portB, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_1;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portB, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portB, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_0;
    };
    #endif

}


#endif

