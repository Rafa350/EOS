module;


#include "HTL/htl.h"


export module Eos.Hardware.DMA.Traits;


import Eos.Hardware.DMA.Identifiers;
import Eos.Hardware.DMA.Classes;


export namespace eos::hardware::dma::internal {

    template <DMADeviceID>
    struct DMATraits;

#ifdef HTL_DMA1_CHANNEL1_EXIST
    template <>
    struct DMATraits<DMADeviceID::dma11> {
        static constexpr const DMADEV_TypeDef *dmadev = &__dmadev11;
        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
#if defined(EOS_PLATFORM_STM32F0)
        static constexpr uint32_t activatePos = RCC_AHBENR_DMAEN_Pos;
#else
        static constexpr uint32_t activatePos = RCC_AHBENR_DMA1EN_Pos;
#endif
    };
#endif

#ifdef HTL_DMA1_CHANNEL2_EXIST
    template <>
    struct DMATraits<DMADeviceID::dma12> {
        static constexpr const DMADEV_TypeDef *dmadev = &__dmadev12;
        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
#if defined(EOS_PLATFORM_STM32F0)
        static constexpr uint32_t activatePos = RCC_AHBENR_DMAEN_Pos;
#else
        static constexpr uint32_t activatePos = RCC_AHBENR_DMA1EN_Pos;
#endif
    };
#endif

#ifdef HTL_DMA1_CHANNEL3_EXIST
    template <>
    struct DMATraits<DMADeviceID::dma13> {
        static constexpr const DMADEV_TypeDef *dmadev = &__dmadev13;
        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
#if defined(EOS_PLATFORM_STM32F0)
        static constexpr uint32_t activatePos = RCC_AHBENR_DMAEN_Pos;
#else
        static constexpr uint32_t activatePos = RCC_AHBENR_DMA1EN_Pos;
#endif
    };
#endif
}
