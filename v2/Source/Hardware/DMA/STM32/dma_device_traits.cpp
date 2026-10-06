module;


#include "HTL/htl.h"


export module Eos.Hardware.DMA.__DEVICE_TRAITS;


import Eos.Hardware.DMA.__CLASSES;
import Eos.Hardware.DMA.__PLATFORM_TRAITS;
import Eos.Types;


export namespace eos::hardware::dma::internal {

    template <DMADeviceID>
    struct DMATraits;

#if defined(DMA1_BASE) && defined(DMA1_Channel1_BASE)
    template <>
    struct DMATraits<DMADeviceID::dma11> {
        static constexpr UInt32 dmaAddr              = DMA1_BASE;
        static constexpr UInt32 dmaChannelAddr       = DMA1_Channel1_BASE;
        static constexpr UInt32 muxChannelStatusAddr = DMAMUX1_ChannelStatus_BASE;
        static constexpr UInt32 muxChannelAddr       = DMAMUX1_Channel0_BASE;
        static constexpr UInt32 activateAddr         = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
#if defined(EOS_PLATFORM_STM32F0)
        static constexpr UInt32 activatePos          = RCC_AHBENR_DMAEN_Pos;
#else
        static constexpr UInt32 activatePos          = RCC_AHBENR_DMA1EN_Pos;
#endif
    };
#endif

#if defined(DMA1_BASE) && defined(DMA1_Channel2_BASE)
    template <>
    struct DMATraits<DMADeviceID::dma12> {
        static constexpr UInt32 dmaAddr              = DMA1_BASE;
        static constexpr UInt32 dmaChannelAddr       = DMA1_Channel2_BASE;
        static constexpr UInt32 muxChannelStatusAddr = DMAMUX1_ChannelStatus_BASE;
        static constexpr UInt32 muxChannelAddr       = DMAMUX1_Channel1_BASE;
        static constexpr UInt32 activateAddr         = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
        static constexpr UInt32 activatePos          = RCC_AHBENR_DMA1EN_Pos;
    };
#endif

#if defined(DMA1_BASE) && defined(DMA1_Channel3_BASE)
    template <>
    struct DMATraits<DMADeviceID::dma13> {
        static constexpr UInt32 dmaAddr              = DMA1_BASE;
        static constexpr UInt32 dmaChannelAddr       = DMA1_Channel3_BASE;
        static constexpr UInt32 muxChannelStatusAddr = DMAMUX1_ChannelStatus_BASE;
        static constexpr UInt32 muxChannelAddr       = DMAMUX1_Channel2_BASE;
        static constexpr UInt32 activateAddr         = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
        static constexpr UInt32 activatePos          = RCC_AHBENR_DMA1EN_Pos;
    };
#endif
}
