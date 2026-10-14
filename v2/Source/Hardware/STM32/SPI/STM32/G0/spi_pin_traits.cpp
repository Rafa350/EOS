module;


#include "hardware.h"


export module Eos.Hardware.SPI.PinTraits;


import Eos.Hardware.GPIO;
import Eos.Hardware.SPI.Types;


export namespace eos::hardware::spi::internal {

    enum class PinFunction { sck, miso, mosi };

    template <SPIDeviceID, PinFunction, gpio::PortID, gpio::PinID>
    struct PinTraits;

    #if defined(SPI1_BASE)
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, gpio::PortID::portA, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, gpio::PortID::portA, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, gpio::PortID::portA, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, gpio::PortID::portA, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, gpio::PortID::portB, gpio::PinID::pin4> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, gpio::PortID::portA, gpio::PinID::pin2> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, gpio::PortID::portA, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, gpio::PortID::portA, gpio::PinID::pin12> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, gpio::PortID::portB, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    #endif

    #if defined(SPI2_BASE)
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portA, gpio::PinID::pin0> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin8> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_5;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, gpio::PortID::portB, gpio::PinID::pin13> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, gpio::PortID::portA, gpio::PinID::pin3> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, gpio::PortID::portA, gpio::PinID::pin9> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, gpio::PortID::portB, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, gpio::PortID::portB, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_4;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, gpio::PortID::portB, gpio::PinID::pin14> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portA, gpio::PinID::pin4> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portA, gpio::PinID::pin10> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portB, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portB, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    template<>
    struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, gpio::PortID::portB, gpio::PinID::pin15> {
        static constexpr auto value = gpio::AlternateFunction::_0;
    };
    #endif

}
