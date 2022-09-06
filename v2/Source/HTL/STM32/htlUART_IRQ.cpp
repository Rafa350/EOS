#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl;


void UART_1_InterruptHandler() {

	UART_1::interruptHandler();
}


void UART_2_InterruptHandler() {

	UART_2::interruptHandler();
}


void UART_3_InterruptHandler() {

	UART_3::interruptHandler();
}


void UART_4_InterruptHandler() {

	UART_4::interruptHandler();
}


void UART_5_InterruptHandler() {

	UART_5::interruptHandler();
}


void UART_6_InterruptHandler() {

	UART_6::interruptHandler();
}


void UART_7_InterruptHandler() {

	UART_7::interruptHandler();
}


void UART_8_InterruptHandler() {

	UART_8::interruptHandler();
}
