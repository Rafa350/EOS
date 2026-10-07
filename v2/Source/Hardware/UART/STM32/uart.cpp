module;


#include "hardware.h"


export module Eos.Hardware.UART;


export import Eos.Hardware.UART.__CLASSES;
export import Eos.Hardware.UART.__TEMPLATES;
export import Eos.Hardware.UART.__PLATFORM_TRAITS;


export namespace eos::hardware::uart {

	using UARTDeviceID = PlatformTraits::DeviceID;

#ifdef USART1_BASE
	using UARTDevice1 = UARTDeviceX<UARTDeviceID::uart1>;
#endif
#ifdef USART2_BASE
	using UARTDevice2 = UARTDeviceX<UARTDeviceID::uart2>;
#endif
#ifdef USART3_BASE
	using UARTDevice3 = UARTDeviceX<UARTDeviceID::uart3>;
#endif
#ifdef USART4_BASE
	using UARTDevice4 = UARTDeviceX<UARTDeviceID::uart4>;
#endif
#ifdef USART5_BASE
	using UARTDevice5 = UARTDeviceX<UARTDeviceID::uart5>;
#endif
#ifdef USART6_BASE
	using UARTDevice6 = UARTDeviceX<UARTDeviceID::uart6>;
#endif
#ifdef USART7_BASE
	using UARTDevice7 = UARTDeviceX<UARTDeviceID::uart7>;
#endif
#ifdef USART8_BASE
	using UARTDevice8 = UARTDeviceX<UARTDeviceID::uart8>;
#endif

}
