module;

#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.SPI._DeviceTraits;


import Eos.Hardware.SPI._Types;
import Eos.Platform;
import Eos.Types;


static_assert(eos::platformCheck("STM32F4xxxx"));


export namespace eos::hardware::spi::internal {

    template <SPIDeviceID>
    struct SPITraits;

    #ifdef SPI1_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi1> {
        static constexpr UInt32 spiAddr = SPI1_BASE;
		static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
		static constexpr uint32_t activatePos = RCC_APB2ENR_SPI1EN_Pos;
    };
    #endif

    #ifdef SPI2_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi2> {
        static constexpr UInt32 spiAddr = SPI2_BASE;
		static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t activatePos = RCC_APB1ENR_SPI2EN_Pos;
    };
    #endif

    #ifdef SPI3_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi3> {
        static constexpr UInt32 spiAddr = SPI3_BASE;
		static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t activatePos = RCC_APB1ENR_SPI3EN_Pos;
    };
    #endif

    #ifdef SPI4_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi4> {
        static constexpr uint32_t spiAddr = SPI4_BASE;
        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
        static constexpr uint32_t activatePos = RCC_APB2ENR_SPI4EN_Pos;
    };
    #endif

    #ifdef SPI5_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi5> {
        static constexpr uint32_t spiAddr = SPI5_BASE;
        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
        static constexpr uint32_t activatePos = RCC_APB2ENR_SPI5EN_Pos;
    };
    #endif

    #ifdef SPI6_BASE
    template<>
    struct SPITraits<SPIDeviceID::spi6> {
        static constexpr uint32_t spiAddr = SPI6_BASE;
        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
        static constexpr uint32_t activatePos = RCC_APB2ENR_SPI6EN_Pos;
    };
    #endif
}
