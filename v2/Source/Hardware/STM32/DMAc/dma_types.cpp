module;


#include "hardware.h"


export module Eos.Hardware.DMA:Types;


import :PlatformTraits;


export namespace eos::hardware::dma {

    using DMADeviceID = internal::PlatformTraits::DeviceID;

}
