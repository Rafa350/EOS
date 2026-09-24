module;


#include "HTL/htl.h"


export module Eos.Hardware.UART;


export import Eos.Hardware.UART.Identifiers;
export import Eos.Hardware.UART.Device;
export import Eos.Hardware.UART.DeviceX;


export namespace eos::hardware::uart {

#ifdef HTL_UART1_EXIST
	using UARTDevice1 = UARTDeviceX<UARTDeviceID::uart1>;
#endif
#ifdef HTL_UART2_EXIST
	using UARTDevice2 = UARTDeviceX<UARTDeviceID::uart2>;
#endif
#ifdef HTL_UART3_EXIST
	using UARTDevice3 = UARTDeviceX<UARTDeviceID::uart3>;
#endif
#ifdef HTL_UART4_EXIST
	using UARTDevice4 = UARTDeviceX<UARTDeviceID::uart4>;
#endif
#ifdef HTL_UART5_EXIST
	using UARTDevice5 = UARTDeviceX<UARTDeviceID::uart5>;
#endif
#ifdef HTL_UART6_EXIST
	using UARTDevice6 = UARTDeviceX<UARTDeviceID::uart6>;
#endif
#ifdef HTL_UART7_EXIST
	using UARTDevice7 = UARTDeviceX<UARTDeviceID::uart7>;
#endif
#ifdef HTL_UART8_EXIST
	using UARTDevice8 = UARTDeviceX<UARTDeviceID::uart8>;
#endif
}
