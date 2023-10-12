#include "eos.h"
#include "HTL/htlGPIO.h"


extern "C" void EXTI15_10_IRQHandler() {

	auto hPinInterrupt = TOUCHPAD_INT_PinInterrupt::getHandler();
	hPinInterrupt->interruptHandler();
}
