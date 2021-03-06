#ifndef __eosConfig__
#define __eosConfig__


#define USE_LEDS_LED1
#define USE_SWITCHES_SW1


#include "Board/eosBoard.h"


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
#define DigInputService_Timer					      HAL_TMR_TIMER_2
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
#define DigOutputService_Timer                        HAL_TMR_TIMER_3
#define DigOutputService_TimerInterruptVector         HAL_INT_VECTOR_TMR3
#define DigOutputService_TimerInterruptPriority       HAL_INT_PRIORITY_5
#define DigOutputService_TimerInterruptSubPriority    HAL_INT_SUBPRIORITY_0
#endif

// Configuracio del servei USART
//
#define USARTService_Enabled                          1    // Servei activat



#endif // __eosConfig__
