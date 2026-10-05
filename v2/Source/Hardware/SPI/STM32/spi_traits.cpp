module;


#include "HTL/htl.h"


export module Eos.Hardware.SPI.Traits;


import Eos.Hardware.SPI.Identifiers;
import Eos.Types;


export namespace eos::hardware::spi::internal {

    template <SPIDeviceID>
    struct SPITraits;

    #ifdef HTL_SPI1_EXIST
    template<>
    struct SPITraits<SPIDeviceID::spi1> {
        static constexpr UInt32 spiAddr = SPI1_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
        static constexpr UInt32 activatePos = RCC_APBENR2_SPI1EN_Pos;
    };
    #endif

    #ifdef HTL_SPI2_EXIST
    template<>
    struct SPITraits<SPIDeviceID::spi2> {
        static constexpr UInt32 spiAddr = SPI2_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_SPI2EN_Pos;
    };
    #endif

    #ifdef HTL_SPI3_EXIST
    template<>
    struct SPITraits<SPIDeviceID::spi3> {
        static constexpr UInt32 spiAddr = SPI3_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_SPI3EN_Pos;
    };
    #endif

}
