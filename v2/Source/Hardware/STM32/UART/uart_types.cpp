module;


#include "hardware.h"


export module Eos.Hardware.UART._Types;


import Eos.Hardware.UART._PlatformTraits;


export namespace eos::hardware::uart {

   	using UARTDeviceID = internal::PlatformTraits::DeviceID;
}
