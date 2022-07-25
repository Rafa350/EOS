#include "eos.h"
#include "HTL/STM32/htlTMR_InterruptHandler.h"
#include "HTL/STM32/htlUART_InterruptHandler.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void USART6_IRQHandler() {

	if (UART_6::getInterruptFlag(UARTEvent::txEmpty)) {
		UART_6::interruptHandler(UARTEvent::txEmpty);
		UART_6::clearInterruptFlag(UARTEvent::txEmpty);
	}
	if (UART_6::getInterruptFlag(UARTEvent::txComplete)) {
		UART_6::interruptHandler(UARTEvent::txComplete);
		UART_6::clearInterruptFlag(UARTEvent::txComplete);
	}
	if (UART_6::getInterruptFlag(UARTEvent::rxFull)) {
		UART_6::interruptHandler(UARTEvent::rxFull);
		UART_6::clearInterruptFlag(UARTEvent::rxFull);
	}
	if (UART_6::getInterruptFlag(UARTEvent::parity)) {
		UART_6::interruptHandler(UARTEvent::parity);
		UART_6::clearInterruptFlag(UARTEvent::parity);
	}
	if (UART_6::getInterruptFlag(UARTEvent::error)) {
		UART_6::interruptHandler(UARTEvent::error);
		UART_6::clearInterruptFlag(UARTEvent::error);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM2_IRQn
///
extern "C" void TIM2_IRQHandler() {

	if (TMR_2::getInterruptFlag(TMREvent::update)) {
		TMR_2::interruptHandler(TMREvent::update);
		TMR_2::clearInterruptFlag(TMREvent::update);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void TIM3_IRQHandler() {

	if (TMR_3::getInterruptFlag(TMREvent::update)) {
		TMR_3::interruptHandler(TMREvent::update);
		TMR_3::clearInterruptFlag(TMREvent::update);
	}
}
