#include "eos.h"
#include "HTL/STM32/htlUART.h"



/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio
///
extern "C" void USART1_IRQHandler() {

	htl::uart::UARTDevice1::interruptHandler();
}
