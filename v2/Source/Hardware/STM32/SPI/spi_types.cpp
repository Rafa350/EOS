module;


#include "hardware.h"


export module Eos.Hardware.SPI._Types;


import Eos.Hardware.SPI._PlatformTraits;


export namespace eos::hardware::spi {

    using SPIDeviceID = internal::PlatformTraits::DeviceID;

}
