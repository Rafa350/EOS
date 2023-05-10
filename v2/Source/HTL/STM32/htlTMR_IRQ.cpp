#include "HTL/htl.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlTMR_IRQ.h"


using namespace htl::tmr;


#ifdef HTL_TMR1_EXIST
void TMRDevice1_InterruptHandler() {

	TMRDevice1::interruptHandler();
}
#endif


#ifdef HTL_TMR2_EXIST
void TMRDevice2_InterruptHandler() {

	TMRDevice2::interruptHandler();
}
#endif


#ifdef HTL_TMR3_EXIST
void TMRDevice3_InterruptHandler() {

	TMRDevice3::interruptHandler();
}
#endif


#ifdef HTL_TMR4_EXIST
void TMRDevice4_InterruptHandler() {

	TMRDevice4::interruptHandler();
}
#endif


#ifdef HTL_TMR5_EXIST
void TMRDevice5_InterruptHandler() {

	TMRDevice5::interruptHandler();
}
#endif


#ifdef HTL_TMR6_EXIST
void TMRDevice6_InterruptHandler() {

	TMRDevice6::interruptHandler();
}
#endif


#ifdef HTL_TMR7_EXIST
void TMRDevice7_InterruptHandler() {

	TMRDevice7::interruptHandler();
}
#endif


#ifdef HTL_TMR8_EXIST
void TMRDevice8_InterruptHandler() {

	TMRDevice8::interruptHandler();
}
#endif


#ifdef HTL_TMR9_EXIST
void TMRDevice9_InterruptHandler() {

	TMRDevice9::interruptHandler();
}
#endif


#ifdef HTL_TMR10_EXIST
void TMRDevice10_InterruptHandler() {

	TMRDevice10::interruptHandler();
}
#endif


#ifdef HTL_TMR11_EXIST
void TMRDevice11_InterruptHandler() {

	TMRDevice11::interruptHandler();
}
#endif


#ifdef HTL_TMR12_EXIST
void TMRDevice12_InterruptHandler() {

	TMRDevice12::interruptHandler();
}
#endif


#ifdef HTL_TMR13_EXIST
void TMRDevice13_InterruptHandler() {

	TMRDevice13::interruptHandler();
}
#endif


#ifdef HTL_TMR14_EXIST
void TMRDevice14_InterruptHandler() {

	TMRDevice14::interruptHandler();
}
#endif


#ifdef HTL_TMR15_EXIST
void TMRDevice15_InterruptHandler() {

	TMRDevice15::interruptHandler();
}
#endif


#ifdef HTL_TMR16_EXIST
void TMRDevice16_InterruptHandler() {

	TMRDevice16::interruptHandler();
}
#endif


#ifdef HTL_TMR17_EXIST
void TMRDevice17_InterruptHandler() {

	TMRDevice17::interruptHandler();
}
#endif
