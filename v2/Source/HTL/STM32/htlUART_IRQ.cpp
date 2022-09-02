#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl;


template <typename uart_>
inline void processInterrupt(UARTEvent event) {

	if (uart_::getInterruptFlag(event)) {
		uart_::clearInterruptFlag(event);
		uart_::interruptHandler(event);
	}
}


void UART_1_InterruptHandler() {

	processInterrupt<UART_1>(UARTEvent::txEmpty);
	processInterrupt<UART_1>(UARTEvent::txComplete);
	processInterrupt<UART_1>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_1>(UARTEvent::rxTimeout);
}


void UART_2_InterruptHandler() {

	processInterrupt<UART_2>(UARTEvent::txEmpty);
	processInterrupt<UART_2>(UARTEvent::txComplete);
	processInterrupt<UART_2>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_2>(UARTEvent::rxTimeout);
}


void UART_3_InterruptHandler() {

	processInterrupt<UART_3>(UARTEvent::txEmpty);
	processInterrupt<UART_3>(UARTEvent::txComplete);
	processInterrupt<UART_3>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_3>(UARTEvent::rxTimeout);
}


void UART_4_InterruptHandler() {

	processInterrupt<UART_4>(UARTEvent::txEmpty);
	processInterrupt<UART_4>(UARTEvent::txComplete);
	processInterrupt<UART_4>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_4>(UARTEvent::rxTimeout);
}


void UART_5_InterruptHandler() {

	processInterrupt<UART_5>(UARTEvent::txEmpty);
	processInterrupt<UART_5>(UARTEvent::txComplete);
	processInterrupt<UART_5>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_5>(UARTEvent::rxTimeout);
}


void UART_6_InterruptHandler() {

	processInterrupt<UART_6>(UARTEvent::txEmpty);
	processInterrupt<UART_6>(UARTEvent::txComplete);
	processInterrupt<UART_6>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_6>(UARTEvent::rxTimeout);
}


void UART_7_InterruptHandler() {

	processInterrupt<UART_7>(UARTEvent::txEmpty);
	processInterrupt<UART_7>(UARTEvent::txComplete);
	processInterrupt<UART_7>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_7>(UARTEvent::rxTimeout);
}


void UART_8_InterruptHandler() {

	processInterrupt<UART_8>(UARTEvent::txEmpty);
	processInterrupt<UART_8>(UARTEvent::txComplete);
	processInterrupt<UART_8>(UARTEvent::rxNotEmpty);
	processInterrupt<UART_8>(UARTEvent::rxTimeout);
}
