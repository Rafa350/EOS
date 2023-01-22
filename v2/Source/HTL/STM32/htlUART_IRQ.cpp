#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl;


#ifdef HTL_UART1_EXIST
void UART_1_InterruptHandler() {

	UART_1::interruptHandler();
}
#endif


#ifdef HTL_UART2_EXIST
void UART_2_InterruptHandler() {

	UART_2::interruptHandler();
}
#endif


#ifdef HTL_UART3_EXIST
void UART_3_InterruptHandler() {

	UART_3::interruptHandler();
}
#endif


#ifdef HTL_UART4_EXIST
void UART_4_InterruptHandler() {

	UART_4::interruptHandler();
}
#endif


#ifdef HTL_UART5_EXIST
void UART_5_InterruptHandler() {

	UART_5::interruptHandler();
}
#endif


#ifdef HTL_UART6_EXIST
void UART_6_InterruptHandler() {

	UART_6::interruptHandler();
}
#endif


#ifdef HTL_UART7_EXIST
void UART_7_InterruptHandler() {

	UART_7::interruptHandler();
}
#endif


#ifdef HTL_UART8_EXIST
void UART_8_InterruptHandler() {

	UART_8::interruptHandler();
}
#endif

