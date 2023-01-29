#pragma once
#ifndef __STM32_htlUART_IRQ__
#define __STM32_htlUART_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef HTL_UART1_EXIST
    void UART_1_InterruptHandler();
#endif	
#ifdef HTL_UART2_EXIST
    void UART_2_InterruptHandler();
#endif	
#ifdef HTL_UART3_EXIST
    void UART_3_InterruptHandler();
#endif	
#ifdef HTL_UART4_EXIST
    void UART_4_InterruptHandler();
#endif	
#ifdef HTL_UART5_EXIST
    void UART_5_InterruptHandler();
#endif	
#ifdef HTL_UART6_EXIST
    void UART_6_InterruptHandler();
#endif	
#ifdef HTL_UART7_EXIST
    void UART_7_InterruptHandler();
#endif	
#ifdef HTL_UART8_EXIST
    void UART_8_InterruptHandler();
#endif	

#ifdef __cplusplus
}
#endif


#endif // __STM32_htlUART_IRQ__
