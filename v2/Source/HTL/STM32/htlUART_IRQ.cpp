#include "eos.h"
#include "HTL/STM32/htlUART.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl;


void UART_1_InterruptHandler() {

}


void UART_2_InterruptHandler() {

}


void UART_3_InterruptHandler() {

}


void UART_4_InterruptHandler() {

}


void UART_5_InterruptHandler() {

}


void UART_6_InterruptHandler() {

	if (UART_6::getInterruptFlag(UARTEvent::txEmpty)) {
		UART_6::interruptHandler(UARTEvent::txEmpty);
		UART_6::clearInterruptFlag(UARTEvent::txEmpty);
	}
	if (UART_6::getInterruptFlag(UARTEvent::txComplete)) {
		UART_6::interruptHandler(UARTEvent::txComplete);
		UART_6::clearInterruptFlag(UARTEvent::txComplete);
	}
	if (UART_6::getInterruptFlag(UARTEvent::rxNotEmpty)) {
		UART_6::interruptHandler(UARTEvent::rxNotEmpty);
		UART_6::clearInterruptFlag(UARTEvent::rxNotEmpty);
	}
	if (UART_6::getInterruptFlag(UARTEvent::parity)) {
		UART_6::interruptHandler(UARTEvent::parity);
		UART_6::clearInterruptFlag(UARTEvent::parity);
	}
	if (UART_6::getInterruptFlag(UARTEvent::overrun)) {
		UART_6::interruptHandler(UARTEvent::overrun);
		UART_6::clearInterruptFlag(UARTEvent::overrun);
	}
	if (UART_6::getInterruptFlag(UARTEvent::framming)) {
		UART_6::interruptHandler(UARTEvent::framming);
		UART_6::clearInterruptFlag(UARTEvent::framming);
	}
}


void UART_7_InterruptHandler() {

}


void UART_8_InterruptHandler() {

}
