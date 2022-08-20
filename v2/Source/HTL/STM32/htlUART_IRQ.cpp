#include "HTL/htl.h"
#include "HTL/STM32/htlUART.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl;


void UART_1_InterruptHandler() {

	uint32_t isr = USART1->ISR;

	if (isr != 0) {

		if (isr & USART_ISR_TXE)
			UART_1::interruptHandler(UARTEvent::txEmpty);

		if (isr & USART_ISR_TC)
			UART_1::interruptHandler(UARTEvent::txComplete);

		if (isr & USART_ISR_RXNE)
			UART_1::interruptHandler(UARTEvent::rxNotEmpty);

		if (isr & USART_ISR_PE)
			UART_1::interruptHandler(UARTEvent::parity);

		if (isr & USART_ISR_ORE)
			UART_1::interruptHandler(UARTEvent::overrun);

		if (isr & USART_ISR_FE)
			UART_1::interruptHandler(UARTEvent::framming);

		USART1->ICR = isr;
	}
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

	uint32_t isr = USART6->ISR;

	if (isr != 0) {

		if (isr & USART_ISR_TXE)
			UART_6::interruptHandler(UARTEvent::txEmpty);

		if (isr & USART_ISR_TC)
			UART_6::interruptHandler(UARTEvent::txComplete);

		if (isr & USART_ISR_RXNE)
			UART_6::interruptHandler(UARTEvent::rxNotEmpty);

		if (isr & USART_ISR_PE)
			UART_6::interruptHandler(UARTEvent::parity);

		if (isr & USART_ISR_ORE)
			UART_6::interruptHandler(UARTEvent::overrun);

		if (isr & USART_ISR_FE)
			UART_6::interruptHandler(UARTEvent::framming);

		USART6->ICR = isr;
	}
}


void UART_7_InterruptHandler() {

}


void UART_8_InterruptHandler() {

}
