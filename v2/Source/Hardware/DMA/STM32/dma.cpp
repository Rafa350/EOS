module;


#include "HTL/htl.h"


export module Eos.Hardware.DMA;


export import Eos.Hardware.DMA.Identifiers;
export import Eos.Hardware.DMA.__CLASSES;
export import Eos.Hardware.DMA.__TEMPLATES;


export namespace eos::hardware::dma {

#ifdef HTL_DMA1_CHANNEL1_EXIST
    using DMADevice11 = DMADeviceX<DMADeviceID::dma11>;
#endif
#ifdef HTL_DMA1_CHANNEL2_EXIST
    using DMADevice12 = DMADeviceX<DMADeviceID::dma12>;
#endif
#ifdef HTL_DMA1_CHANNEL3_EXIST
    using DMADevice13 = DMADeviceX<DMADeviceID::dma13>;
#endif
#ifdef HTL_DMA1_CHANNEL4_EXIST
    using DMADevice14 = DMADeviceX<DMADeviceID::dma14>;
#endif
#ifdef HTL_DMA1_CHANNEL5_EXIST
    using DMADevice15 = DMADeviceX<DMADeviceID::dma15>;
#endif
#ifdef HTL_DMA1_CHANNEL6_EXIST
    using DMADevice16 = DMADeviceX<DMADeviceID::dma16>;
#endif
#ifdef HTL_DMA1_CHANNEL7_EXIST
    using DMADevice17 = DMADeviceX<DMADeviceID::dma17>;
#endif

}
