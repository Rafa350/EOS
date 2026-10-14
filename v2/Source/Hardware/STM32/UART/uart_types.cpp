module;


#include "hardware.h"


export module Eos.Hardware.UART.Types;


import Eos.Hardware.UART.PlatformTraits;


export namespace eos::hardware::uart {

   	using UARTDeviceID = internal::PlatformTraits::DeviceID;
}
