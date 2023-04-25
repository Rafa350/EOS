#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl::uart;


#ifdef HTL_UART1_EXIST
void UART_1_InterruptHandler() {

	UARTDevice1::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART2_EXIST
void UART_2_InterruptHandler() {

	UARTDevice2::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART3_EXIST
void UART_3_InterruptHandler() {

	UARTDevice3::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART4_EXIST
void UART_4_InterruptHandler() {

	UARTDevice4::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART5_EXIST
void UART_5_InterruptHandler() {

	UARTDevice5::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART6_EXIST
void UART_6_InterruptHandler() {

	UARTDevice6::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART7_EXIST
void UART_7_InterruptHandler() {

	UARTDevice7::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART8_EXIST
void UART_8_InterruptHandler() {

	UARTDevice8::getHandler()->interruptService();
}
#endif

