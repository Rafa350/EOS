#include "eos.h"
#include "HTL/STM32/htlTMR_IRQ.h"
#include "HTL/STM32/htlUART_IRQ.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void USART6_IRQHandler() {

	UART_6_InterruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM2_IRQn
///
extern "C" void TIM2_IRQHandler() {

	TMR_2_InterruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void TIM3_IRQHandler() {

	TMR_3_InterruptHandler();
}
