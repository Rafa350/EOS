#ifndef __eosConfig__
#define __eosConfig__


#define USE_LED1
#define USE_SW1
#define USE_ARDUINO


#include "Board/eosBoard.h"

#ifdef __cplusplus

#include "HTL/htlTMR.h"
#include "HTL/htlINT.h"

namespace config {

	namespace digInputService {

		using TMR = htl::TMR_2;

		constexpr unsigned tmrPeriod = 5;
		constexpr htl::INTVector tmrVector = htl::INTVector::vTMR2;
		#if defined(EOS_PLATFORM_PIC32)
			constexpr htl::INTPriority tmrVectorPriority = htl::INTPriority::p2;
	    	constexpr htl::INTSubPriority tmrVectorSubPriority = htl::INTSubPriority::s0;
		#elif defined(EOS_PLATFORM_STM32)
			constexpr htl::INTPriority tmrVectorPriority = htl::INTPriority::p5;
	    	constexpr htl::INTSubPriority tmrVectorSubPriority = htl::INTSubPriority::s0;
		#endif
	}

	namespace digOutputService {

		using TMR = htl::TMR_3;

		constexpr unsigned tmrPeriod = 1;
		constexpr htl::INTVector tmrVector = htl::INTVector::vTMR3;
		#if defined(EOS_PLATFORM_PIC32)
			constexpr htl::INTPriority tmrVectorPriority = htl::INTPriority::p2;
	    	constexpr htl::INTSubPriority tmrVectorSubPriority = htl::INTSubPriority::s0;
		#elif defined(EOS_PLATFORM_STM32)
			constexpr htl::INTPriority tmrVectorPriority = htl::INTPriority::p5;
	    	constexpr htl::INTSubPriority tmrVectorSubPriority = htl::INTSubPriority::s0;
		#endif
	}

	namespace uartService {

		using UART = board::arduino::UART;
		using GPIO_TX = board::arduino::GPIO_TX;
		using GPIO_RX = board::arduino::GPIO_RX;

		constexpr htl::INTVector uartVector = htl::INTVector::vUART6;
		constexpr htl::INTPriority uartVectorPriority = htl::INTPriority::p10;
    	constexpr htl::INTSubPriority uartVectorSubPriority = htl::INTSubPriority::s0;
	}
}

#endif // __cplusplus

// Configuracio del servei DigInputs
//
#define DigInputService_Enabled                       1    // Servei activat
#define DigInputService_SafeMode                      1    // Modus segur
#define DigInputService_TimerPeriod                   5    // 5 ms de periode
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define DigInputService_Timer					      HAL_TMR_TIMER_2
#define DigInputService_TimerInterruptVector          HAL_INT_VECTOR_TMR2
#define DigInputService_TimerInterruptSource          HAL_INT_SOURCE_TMR2
#define DigInputService_TimerInterruptPriority        HAL_INT_PRIORITY_2
#define DigInputService_TimerInterruptSubPriority     HAL_INT_SUBPRIORITY_0
#elif defined(HARDWARE_STM32F429I_DISC1) || defined(HARDWARE_STM32F746G_DISCO)
#define DigInputService_Timer					      htl::TMR_2
#define DigInputService_TimerInterruptVector          HAL_INT_VECTOR_TMR2
#define DigInputService_TimerInterruptPriority        HAL_INT_PRIORITY_5
#define DigInputService_TimerInterruptSubPriority     HAL_INT_SUBPRIORITY_0
#endif

// Configuracio del servei DigOutputs
//
#define DigOutputService_Enabled                      1    // Servei activat
#define DigOutputService_CommandQueueSize             5    // Tamany de la cua de comandes
#define DigOutputService_SafeMode                     1    // Modus segur
#define DigOutputService_TimerPeriod                  1    // 1 ms de periode
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define DigOutputService_Timer					      HAL_TMR_TIMER_3
#define DigOutputService_TimerInterruptVector         HAL_INT_VECTOR_TMR3
#define DigOutputService_TimerInterruptSource         HAL_INT_SOURCE_TMR3
#define DigOutputService_TimerInterruptPriority       HAL_INT_PRIORITY_2
#define DigOutputService_TimerInterruptSubPriority    HAL_INT_SUBPRIORITY_0
#elif defined(HARDWARE_STM32F429I_DISC1) || defined(HARDWARE_STM32F746G_DISCO)
#define DigOutputService_Timer                        htl::TMR_3
#define DigOutputService_TimerInterruptVector         HAL_INT_VECTOR_TMR3
#define DigOutputService_TimerInterruptPriority       HAL_INT_PRIORITY_5
#define DigOutputService_TimerInterruptSubPriority    HAL_INT_SUBPRIORITY_0
#endif

// Configuracio del servei USART
//
#define UARTService_Enabled                           1    // Servei activat
#define UARTService_UART                              board::arduino::UART
#define UARTService_GPIO_TX                           board::arduino::GPIO_TX;
#define UARTService_GPIO_RX                           board::arduino::GPIO_RX;



#endif // __eosConfig__
