module;


#include "hardware.h"


export module Eos.Hardware.SPI.Types;


import Eos.Hardware.SPI.PlatformTraits;


export namespace eos::hardware::spi {

    using SPIDeviceID = internal::PlatformTraits::DeviceID;

}
