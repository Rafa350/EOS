#ifndef __PIC32_halUART__
#define __PIC32_halUART__


#include "eos.h"


typedef uint8_t UARTModule;

typedef struct {
    UARTModule module;
    int baudRate;
} UARTInitializeInfo;


#define HAL_UART_MODULE_1         ((UARTModule) 0)
#ifdef _UART2
#define HAL_UART_MODULE_2         ((UARTModule) 1)  
#endif
#ifdef _UART3
#define HAL_UART_MODULE_3         ((UARTModule) 2)
#endif
#ifdef _UART4
#define HAL_UART_MODULE_4         ((UARTModule) 3)
#endif
#ifdef _UART5
#define HAL_UART_MODULE_5         ((UARTModule) 4)
#endif
#ifdef _UART6
#define HAL_UART_MODULE_6         ((UARTModule) 5)
#endif
#define HAL_UART_MODULE_NONE      ((UARTModule) 255)


void halUARTInitialize(const UARTInitializeInfo *info);



#endif // __PIC32_halUART__