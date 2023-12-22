#include "eos.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlUART.h"


using namespace htl;
using namespace htl::uart;
using namespace htl::tmr;


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio
///
extern "C" void USART6_IRQHandler() {

	UARTDevice6::interruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio
///
extern "C" void TIM2_IRQHandler() {

	TMRDevice2::interruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio
///
extern "C" void TIM3_IRQHandler() {

	TMRDevice3::interruptHandler();
}
