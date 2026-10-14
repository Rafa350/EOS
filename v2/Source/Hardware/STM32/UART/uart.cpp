module;


#include "hardware.h"


export module Eos.Hardware.UART;


export import Eos.Hardware.UART.Classes;
export import Eos.Hardware.UART.PlatformTraits;
export import Eos.Hardware.UART.Templates;
export import Eos.Hardware.UART.Types;


export namespace eos::hardware::uart {

#ifdef USART1_BASE
	using UARTDevice1 = UARTDeviceX<UARTDeviceID::uart1>;
#endif
#ifdef USART2_BASE
	using UARTDevice2 = UARTDeviceX<UARTDeviceID::uart2>;
#endif
#ifdef USART3_BASE
	using UARTDevice3 = UARTDeviceX<UARTDeviceID::uart3>;
#endif
#if defined(USART4_BASE) || defined(UART4_BASE)
	using UARTDevice4 = UARTDeviceX<UARTDeviceID::uart4>;
#endif
#if defined(USART5_BASE) || defined(UART5_BASE)
	using UARTDevice5 = UARTDeviceX<UARTDeviceID::uart5>;
#endif
#ifdef USART6_BASE
	using UARTDevice6 = UARTDeviceX<UARTDeviceID::uart6>;
#endif
#if defined(USART7_BASE) || defined(UART8_BASE)
	using UARTDevice7 = UARTDeviceX<UARTDeviceID::uart7>;
#endif
#if defined(USART8_BASE) || defined(UART8_BASE)
	using UARTDevice8 = UARTDeviceX<UARTDeviceID::uart8>;
#endif

}
