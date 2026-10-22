module;

#include "hardware.h"


export module Eos.Hardware.SPI._PinTraits;


import Eos.Hardware.GPIO;
import Eos.Hardware.SPI._Types;
import Eos.Platform;


static_assert(eos::platformCheck("STM32F4xxxx"));


export namespace eos::hardware::spi::internal {

    enum class PinFunction { sck, miso, mosi };


    template <SPIDeviceID, PinFunction, gpio::PortID, gpio::PinID>
    struct PinTraits;

    #ifdef SPI1_BASE
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, gpio::PortID::portA, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, gpio::PortID::portA, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, gpio::PortID::portB, gpio::PinID::pin4> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, gpio::PortID::portA, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, gpio::PortID::portB, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    #endif

    #ifdef SPI2_BASE
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin13> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portD, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portI, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, gpio::PortID::portB, gpio::PinID::pin14> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, gpio::PortID::portI, gpio::PinID::pin2> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portB, gpio::PinID::pin15> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portC, gpio::PinID::pin2> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portC, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portI, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    #endif

    #ifdef SPI3_BASE
    template<>
    struct PinTraits<SPIDeviceID::spi3, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_6;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi3, PinFunction::sck, gpio::PortID::portC, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_6;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi3, PinFunction::miso, gpio::PortID::portB, gpio::PinID::pin4> {
        static constexpr auto value = gpio::AlternateFunction::_6;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi3, PinFunction::miso, gpio::PortID::portC, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_6;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi3, PinFunction::mosi, gpio::PortID::portB, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_6;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi3, PinFunction::mosi, gpio::PortID::portC, gpio::PinID::pin12> {
        static constexpr auto value = gpio::AlternateFunction::_6;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi3, PinFunction::mosi, gpio::PortID::portD, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    #endif

    #ifdef SPI4_BASE
    #endif

    #ifdef SPI5_BASE
    template<>
    struct PinTraits<SPIDeviceID::spi5, PinFunction::sck, gpio::PortID::portF, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi5, PinFunction::mosi, gpio::PortID::portF, gpio::PinID::pin9> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    #endif

}
