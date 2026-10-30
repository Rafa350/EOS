module;

#include "hardware.h"


export module Eos.Hardware.LTDC._LayerTraits;

import Eos.Hardware.LTDC._Types;
import Eos.Types;


export namespace eos::hardware::ltdc::internal {


    template <LTDCLayerID layerId_>
    struct LayerTraits;

#ifdef LTDC_Layer1_BASE
    template <>
    struct LayerTraits<LTDCLayerID::layer1> {
        static constexpr UInt32 layerAddr = LTDC_Layer1_BASE;
    };
#endif

#ifdef LTDC_Layer2_BASE
    template <>
    struct LayerTraits<LTDCLayerID::layer2> {
        static constexpr UInt32 layerAddr = LTDC_Layer2_BASE;
    };
#endif
}
