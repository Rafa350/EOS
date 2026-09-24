module;


#include "HTL/htl.h"


export module Eos.Hardware.UART.Identifiers;


export namespace eos::hardware::uart {

	/// @brief Identificador del dispositiu UART
	///
	enum class UARTDeviceID {
#ifdef HTL_UART1_EXIST
		uart1,
#endif
#ifdef HTL_UART2_EXIST
		uart2,
#endif
#ifdef HTL_UART3_EXIST
		uart3,
#endif
#ifdef HTL_UART4_EXIST
		uart4,
#endif
#ifdef HTL_UART5_EXIST
		uart5,
#endif
#ifdef HTL_UART6_EXIST
		uart6,
#endif
#ifdef HTL_UART7_EXIST
		uart7,
#endif
#ifdef HTL_UART8_EXIST
		uart8,
#endif
	};

}
