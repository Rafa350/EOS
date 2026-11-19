module;

#include "hardware.h"


export module Eos.Hardware.DMA._PlatformTraits;


import Eos.Platform;


namespace eos::hardware::dma::internal {

    namespace hidden {

        enum class DeviceID_Type1 { dma11, dma12, dma13, dma14, dma15, dma16, dma17 };

        template<PlatformID platformId_>
        struct PlatformTraits;

        template <>
        struct PlatformTraits<PlatformID::STM32_F429_ZI> {
            using DeviceID = DeviceID_Type1;
        };
    }

    export using PlatformTraits = hidden::PlatformTraits<Platform::id>;
}
