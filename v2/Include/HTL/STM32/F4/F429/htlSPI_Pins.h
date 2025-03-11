#pragma once
#ifndef __FC43FE2006904B9EB279A6BAC4A317FE__
#define __FC43FE2006904B9EB279A6BAC4A317FE__


#if !defined(EOS_PLATFORM_STM32F429)
    #error 'Unsupppined platform'
#endif


namespace htl::spi::internal {

    #if defined(HTL_SPI1_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::sck, htl::gpio::PortID::portA, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::miso, htl::gpio::PortID::portA, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::miso, htl::gpio::PortID::portB, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::mosi, htl::gpio::PortID::portA, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi1, PinFunction::mosi, htl::gpio::PortID::portB, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    #endif

    #if defined(HTL_SPI2_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin13> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portD, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::sck, htl::gpio::PortID::portI, htl::gpio::PinID::pin1> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::miso, htl::gpio::PortID::portB, htl::gpio::PinID::pin14> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::miso, htl::gpio::PortID::portI, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portB, htl::gpio::PinID::pin15> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portC, htl::gpio::PinID::pin2> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portC, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi2, PinFunction::mosi, htl::gpio::PortID::portI, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    #endif

    #if defined(HTL_SPI3_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::spi3, PinFunction::sck, htl::gpio::PortID::portB, htl::gpio::PinID::pin3> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi3, PinFunction::sck, htl::gpio::PortID::portC, htl::gpio::PinID::pin10> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi3, PinFunction::miso, htl::gpio::PortID::portB, htl::gpio::PinID::pin4> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi3, PinFunction::miso, htl::gpio::PortID::portC, htl::gpio::PinID::pin11> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi3, PinFunction::mosi, htl::gpio::PortID::portB, htl::gpio::PinID::pin5> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi3, PinFunction::mosi, htl::gpio::PortID::portC, htl::gpio::PinID::pin12> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_6;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi3, PinFunction::mosi, htl::gpio::PortID::portD, htl::gpio::PinID::pin6> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    #endif

    #if defined(HTL_SPI4_EXIST)
    #endif

    #if defined(HTL_SPI5_EXIST)
    template<>
    struct PinFunctionInfo<DeviceID::spi5, PinFunction::sck, htl::gpio::PortID::portF, htl::gpio::PinID::pin7> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    template<>
    struct PinFunctionInfo<DeviceID::spi5, PinFunction::mosi, htl::gpio::PortID::portF, htl::gpio::PinID::pin9> {
        static constexpr htl::gpio::AlternateFunction value = htl::gpio::AlternateFunction::_5;
    };
    #endif

}


#endif

