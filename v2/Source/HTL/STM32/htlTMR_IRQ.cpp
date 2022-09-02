#include "HTL/htl.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlTMR_IRQ.h"


using namespace htl;


template <typename timer_>
inline void processInterrupt(TMREvent event) {

	if (timer_::getInterruptFlag(event)) {
		timer_::clearInterruptFlag(event);
		timer_::interruptHandler(event);
	}
}


void TMR_1_InterruptHandler() {

	processInterrupt<TMR_1>(TMREvent::update);
}


void TMR_2_InterruptHandler() {

	processInterrupt<TMR_2>(TMREvent::update);
}


void TMR_3_InterruptHandler() {

	processInterrupt<TMR_3>(TMREvent::update);
}


void TMR_4_InterruptHandler() {

	processInterrupt<TMR_4>(TMREvent::update);
}


void TMR_5_InterruptHandler() {

	processInterrupt<TMR_5>(TMREvent::update);
}


void TMR_6_InterruptHandler() {

	processInterrupt<TMR_6>(TMREvent::update);
}


void TMR_7_InterruptHandler() {

	processInterrupt<TMR_7>(TMREvent::update);
}


void TMR_8_InterruptHandler() {

	processInterrupt<TMR_8>(TMREvent::update);
}


void TMR_9_InterruptHandler() {

	processInterrupt<TMR_9>(TMREvent::update);
}


void TMR_10_InterruptHandler() {

	processInterrupt<TMR_10>(TMREvent::update);
}


void TMR_11_InterruptHandler() {

	processInterrupt<TMR_11>(TMREvent::update);
}


void TMR_12_InterruptHandler() {

	processInterrupt<TMR_12>(TMREvent::update);
}


void TMR_13_InterruptHandler() {

	processInterrupt<TMR_13>(TMREvent::update);
}


void TMR_14_InterruptHandler() {

	processInterrupt<TMR_14>(TMREvent::update);
}
