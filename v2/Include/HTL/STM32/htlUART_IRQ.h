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
    void UARTDevice1_InterruptHandler();
#endif	
#ifdef HTL_UART2_EXIST
    void UARTDevice2_InterruptHandler();
#endif	
#ifdef HTL_UART3_EXIST
    void UARTDevice3_InterruptHandler();
#endif	
#ifdef HTL_UART4_EXIST
    void UARTDevice4_InterruptHandler();
#endif	
#ifdef HTL_UART5_EXIST
    void UARTDevice5_InterruptHandler();
#endif	
#ifdef HTL_UART6_EXIST
    void UARTDevice6_InterruptHandler();
#endif	
#ifdef HTL_UART7_EXIST
    void UARTDevice7_InterruptHandler();
#endif	
#ifdef HTL_UART8_EXIST
    void UARTDevice8_InterruptHandler();
#endif	

#ifdef __cplusplus
}
#endif


#endif // __STM32_htlUART_IRQ__
