module;


#include "hardware.h"


export module Eos.Hardware.DMA;


export import :Types;
export import :Templates;
export import :Classes;
export import :PlatformTraits;
export import :DeviceTraits;


export namespace eos::hardware::dma {

#ifdef DMA1_Channel1_BASE
    using DMADevice11 = DMADeviceX<DMADeviceID::dma11>;
#endif
#ifdef DMA1_Channel2_BASE
    using DMADevice12 = DMADeviceX<DMADeviceID::dma12>;
#endif
#ifdef DMA1_Channel3_BASE
    using DMADevice13 = DMADeviceX<DMADeviceID::dma13>;
#endif
#ifdef DMA1_Channel4_BASE
    using DMADevice14 = DMADeviceX<DMADeviceID::dma14>;
#endif
#ifdef DMA1_Channel5_BASE
    using DMADevice15 = DMADeviceX<DMADeviceID::dma15>;
#endif
#ifdef DMA1_Channel6_BASE
    using DMADevice16 = DMADeviceX<DMADeviceID::dma16>;
#endif
#ifdef DMA1_Channel7_BASE
    using DMADevice17 = DMADeviceX<DMADeviceID::dma17>;
#endif

}
