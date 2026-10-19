module;

#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.SPI._DeviceTraits;


import Eos.Hardware.SPI._Types;
import Eos.Platform;
import Eos.Types;


static_assert(eos::platformCheck("STM32G0xxxx"));


export namespace eos::hardware::spi::internal {

    template <SPIDeviceID>
    struct SPITraits;

    #ifdef SPI1_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi1> {
        static constexpr UInt32 spiAddr = SPI1_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
        static constexpr UInt32 activatePos = RCC_APBENR2_SPI1EN_Pos;
    };
    #endif

    #ifdef SPI2_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi2> {
        static constexpr UInt32 spiAddr = SPI2_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_SPI2EN_Pos;
    };
    #endif

    #ifdef SPI3_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi3> {
        static constexpr UInt32 spiAddr = SPI3_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_SPI3EN_Pos;
    };
    #endif

}
