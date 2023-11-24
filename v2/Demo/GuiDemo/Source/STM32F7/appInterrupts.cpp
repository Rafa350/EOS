#include "eos.h"
#include "HTL/htlGPIO.h"


extern "C" void EXTI15_10_IRQHandler(void) {

#if eosGuiService_TouchpadEnabled
	TOUCHPAD_INT_PinInterrupt::pInst->interruptHandler();
#endif
}
