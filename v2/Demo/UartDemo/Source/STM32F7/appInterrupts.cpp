#include "eos.h"
#include "HAL/halTMR.h"
#include "HAL/halUART.h"


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void USART6_IRQHandler() {

	extern halUARTData uartData;

	halUARTInterruptHandler(&uartData);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM2_IRQn
///
extern "C" void TIM2_IRQHandler() {

	extern halTMRData digInputTimerData;

	halTMRInterruptHandler(&digInputTimerData);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void TIM3_IRQHandler() {

	extern halTMRData digOutputTimerData;

	halTMRInterruptHandler(&digOutputTimerData);
}
