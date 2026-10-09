module;


#include "HTL/htlGPIO.h"


export module Eos.Hardware.SPI.__PIN_TRAITS;


import Eos.Hardware.SPI.Identifiers;


export namespace eos::hardware::spi {

    namespace internal {

        namespace g = htl::gpio;

        enum class PinFunction {
            sck,
            miso,
            mosi
        };

        template <SPIDeviceID, PinFunction, g::PortID, g::PinID>
        struct PinTraits;

        #if defined(HTL_SPI1_EXIST)
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, g::PortID::portA, g::PinID::pin1> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, g::PortID::portA, g::PinID::pin5> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::sck, g::PortID::portB, g::PinID::pin3> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, g::PortID::portA, g::PinID::pin6> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, g::PortID::portA, g::PinID::pin11> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::miso, g::PortID::portB, g::PinID::pin4> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, g::PortID::portA, g::PinID::pin2> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, g::PortID::portA, g::PinID::pin7> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, g::PortID::portA, g::PinID::pin12> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi1, PinFunction::mosi, g::PortID::portB, g::PinID::pin5> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        #endif

        #if defined(HTL_SPI2_EXIST)
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, g::PortID::portA, g::PinID::pin0> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, g::PortID::portB, g::PinID::pin8> {
            static constexpr auto value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, g::PortID::portB, g::PinID::pin10> {
            static constexpr auto value = g::AlternateFunction::_5;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::sck, g::PortID::portB, g::PinID::pin13> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, g::PortID::portA, g::PinID::pin3> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, g::PortID::portA, g::PinID::pin9> {
            static constexpr auto value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, g::PortID::portB, g::PinID::pin1> {
            static constexpr auto value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, g::PortID::portB, g::PinID::pin6> {
            static constexpr auto value = g::AlternateFunction::_4;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::miso, g::PortID::portB, g::PinID::pin14> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, g::PortID::portA, g::PinID::pin4> {
            static constexpr auto value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, g::PortID::portA, g::PinID::pin10> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, g::PortID::portB, g::PinID::pin7> {
            static constexpr auto value = g::AlternateFunction::_1;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, g::PortID::portB, g::PinID::pin11> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        template<>
        struct PinTraits<SPIDeviceID::spi2, PinFunction::mosi, g::PortID::portB, g::PinID::pin15> {
            static constexpr auto value = g::AlternateFunction::_0;
        };
        #endif

    }
}
