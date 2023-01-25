#pragma once
#ifndef __STM32_htlUART_IRQ__
#define __STM32_htlUART_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef HTL_USART1_EXIST
    void UART_1_InterruptHandler();
#endif	
#ifdef HTL_USART2_EXIST
    void UART_2_InterruptHandler();
#endif	
#ifdef HTL_USART3_EXIST
    void UART_3_InterruptHandler();
#endif	
#ifdef HTL_USART4_EXIST
    void UART_4_InterruptHandler();
#endif	
#ifdef HTL_USART5_EXIST
    void UART_5_InterruptHandler();
#endif	
#ifdef HTL_USART6_EXIST
    void UART_6_InterruptHandler();
#endif	
#ifdef HTL_USART7_EXIST
    void UART_7_InterruptHandler();
#endif	
#ifdef HTL_USART8_EXIST
    void UART_8_InterruptHandler();
#endif	

#ifdef __cplusplus
}
#endif


#endif // __STM32_htlUART_IRQ__
