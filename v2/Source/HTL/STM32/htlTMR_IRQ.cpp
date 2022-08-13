#include "HTL/htl.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlTMR_IRQ.h"


using namespace htl;


void TMR_1_InterruptHandler() {

	if (TMR_1::getInterruptFlag(TMREvent::update)) {
		TMR_1::interruptHandler(TMREvent::update);
		TMR_1::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_2_InterruptHandler() {

	if (TMR_2::getInterruptFlag(TMREvent::update)) {
		TMR_2::interruptHandler(TMREvent::update);
		TMR_2::clearInterruptFlag(TMREvent::update);
	}
	if (TMR_2::getInterruptFlag(TMREvent::trigger)) {
		TMR_2::interruptHandler(TMREvent::trigger);
		TMR_2::clearInterruptFlag(TMREvent::trigger);
	}
	if (TMR_2::getInterruptFlag(TMREvent::com)) {
		TMR_2::interruptHandler(TMREvent::com);
		TMR_2::clearInterruptFlag(TMREvent::com);
	}
}


void TMR_3_InterruptHandler() {

	if (TMR_3::getInterruptFlag(TMREvent::update)) {
		TMR_3::interruptHandler(TMREvent::update);
		TMR_3::clearInterruptFlag(TMREvent::update);
	}
	if (TMR_3::getInterruptFlag(TMREvent::trigger)) {
		TMR_3::interruptHandler(TMREvent::trigger);
		TMR_3::clearInterruptFlag(TMREvent::trigger);
	}
	if (TMR_3::getInterruptFlag(TMREvent::com)) {
		TMR_3::interruptHandler(TMREvent::com);
		TMR_3::clearInterruptFlag(TMREvent::com);
	}
}


void TMR_4_InterruptHandler() {

	if (TMR_4::getInterruptFlag(TMREvent::update)) {
		TMR_5::interruptHandler(TMREvent::update);
		TMR_6::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_5_InterruptHandler() {

	if (TMR_5::getInterruptFlag(TMREvent::update)) {
		TMR_5::interruptHandler(TMREvent::update);
		TMR_5::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_6_InterruptHandler() {

	if (TMR_6::getInterruptFlag(TMREvent::update)) {
		TMR_6::interruptHandler(TMREvent::update);
		TMR_6::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_7_InterruptHandler() {

	if (TMR_7::getInterruptFlag(TMREvent::update)) {
		TMR_7::interruptHandler(TMREvent::update);
		TMR_7::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_8_InterruptHandler() {

	if (TMR_8::getInterruptFlag(TMREvent::update)) {
		TMR_8::interruptHandler(TMREvent::update);
		TMR_8::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_9_InterruptHandler() {

	if (TMR_9::getInterruptFlag(TMREvent::update)) {
		TMR_9::interruptHandler(TMREvent::update);
		TMR_9::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_10_InterruptHandler() {

	if (TMR_10::getInterruptFlag(TMREvent::update)) {
		TMR_10::interruptHandler(TMREvent::update);
		TMR_10::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_11_InterruptHandler() {

	if (TMR_11::getInterruptFlag(TMREvent::update)) {
		TMR_11::interruptHandler(TMREvent::update);
		TMR_11::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_12_InterruptHandler() {

	if (TMR_12::getInterruptFlag(TMREvent::update)) {
		TMR_12::interruptHandler(TMREvent::update);
		TMR_12::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_13_InterruptHandler() {

	if (TMR_13::getInterruptFlag(TMREvent::update)) {
		TMR_13::interruptHandler(TMREvent::update);
		TMR_13::clearInterruptFlag(TMREvent::update);
	}
}


void TMR_14_InterruptHandler() {

	if (TMR_14::getInterruptFlag(TMREvent::update)) {
		TMR_14::interruptHandler(TMREvent::update);
		TMR_14::clearInterruptFlag(TMREvent::update);
	}
}
