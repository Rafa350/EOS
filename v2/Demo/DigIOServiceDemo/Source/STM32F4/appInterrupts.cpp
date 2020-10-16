#include "eos.h"
#include "HAL/halTMR.h"


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM2_IRQn
///
extern "C" void TIM2_IRQHandler() {

	extern TMRData digInputTimer;

	halTMRInterruptHandler(&digInputTimer);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector d'interrupcio TIM3_IRQn
///
extern "C" void TIM3_IRQHandler() {

	extern TMRData digOutputTimer;

	halTMRInterruptHandler(&digOutputTimer);
}
