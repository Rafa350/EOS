#ifndef __eosConfig__
#define __eosConfig__


#define USE_LEDS_LED1
#define USE_LEDS_LED2
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
	#define USE_LEDS_LED3
#endif

#define USE_SWITCHES_SW1
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #define USE_SWITCHES_SW2
#endif
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #define USE_SWITCHES_SW3
#endif

#define xUSE_APPLICATION_TICK
#define APPLICATION_TICK_PERIOD     10


#include "board/eosBoard.h"


// Configuracio del servei DigInputs
//
#define DigInputService_Enabled                       1    // Servei activat
#define DigInputService_SafeMode                      1    // Modus segur
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define DigInputService_Timer					      HAL_TMR_TIMER_2
#define DigInputService_TimerInterruptPriority        HAL_INT_PRIORITY_LEVEL2
#define DigInputService_TimerInterruptSubPriority     HAL_INT_SUBPRIORITY_LEVEL0
#elif defined(HARDWARE_STM32F429I_DISC1)
#define DigInputService_Timer					      HAL_TMR_TIMER_2
#define DigInputService_TimerInterruptPriority        HAL_INT_PRIORITY_LEVEL5
#define DigInputService_TimerInterruptSubPriority     HAL_INT_SUBPRIORITY_LEVEL0
#endif

// Configuracio del servei DigOutputs
//
#define DigOutputService_Enabled                      1    // Servei activat
#define DigOutputService_CommandQueueSize             5    // Tamany de la cua de comandes
#define DigOutputService_SafeMode                     1    // Modus segur
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define DigOutputService_Timer					      HAL_TMR_TIMER_3
#define DigOutputService_TimerInterruptPriority       HAL_INT_PRIORITY_LEVEL2
#define DigOutputService_TimerInterruptSubPriority    HAL_INT_SUBPRIORITY_LEVEL0
#elif defined(HARDWARE_STM32F429I_DISC1)
#define DigOutputService_Timer                        HAL_TMR_TIMER_3
#define DigOutputService_TimerInterruptPriority       HAL_INT_PRIORITY_LEVEL5
#define DigOutputService_TimerInterruptSubPriority    HAL_INT_SUBPRIORITY_LEVEL0
#endif


#endif // __eosConfig__
