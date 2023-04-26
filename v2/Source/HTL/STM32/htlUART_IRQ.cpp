#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl::uart;


#ifdef HTL_UART1_EXIST
void UARTDevice1_InterruptHandler() {

	UARTDevice1::interruptHandler();
}
#endif


#ifdef HTL_UART2_EXIST
void UARTDevice2_InterruptHandler() {

	UARTDevice2::interruptHandler();
}
#endif


#ifdef HTL_UART3_EXIST
void UARTDevice3_InterruptHandler() {

	UARTDevice3::interruptHandler();
}
#endif


#ifdef HTL_UART4_EXIST
void UARTDevice4_InterruptHandler() {

	UARTDevice4::interruptHandler();
}
#endif


#ifdef HTL_UART5_EXIST
void UARTDevice5_InterruptHandler() {

	UARTDevice5::interruptHandler();
}
#endif


#ifdef HTL_UART6_EXIST
void UARTDevice6_InterruptHandler() {

	UARTDevice6::interruptHandler();
}
#endif


#ifdef HTL_UART7_EXIST
void UARTDevice7_InterruptHandler() {

	UARTDevice7::getHandler()->interruptService();
}
#endif


#ifdef HTL_UART8_EXIST
void UART_8_InterruptHandler() {

	UARTDevice8::getHandler()->interruptService();
}
#endif

