#include "eos.h"
#include "HAL/halTMR.h"
#include "HAL/halUART.h"


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void USART6_IRQHandler() {

	extern UARTData uartData;

	halUARTInterruptHandler(&uartData);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM2_IRQn
///
extern "C" void TIM2_IRQHandler() {

	extern TMRData digInputTimerData;

	halTMRInterruptHandler(&digInputTimerData);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void TIM3_IRQHandler() {

	extern TMRData digOutputTimerData;

	halTMRInterruptHandler(&digOutputTimerData);
}
