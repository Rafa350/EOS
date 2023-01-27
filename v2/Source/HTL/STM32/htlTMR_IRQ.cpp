#include "HTL/htl.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlTMR_IRQ.h"


using namespace htl;


#ifdef HTL_TMR1_EXIST
void TMR_1_InterruptHandler() {

	TMR_1::interruptHandler();
}
#endif


#ifdef HTL_TMR2_EXIST
void TMR_2_InterruptHandler() {

	TMR_2::interruptHandler();
}
#endif


#ifdef HTL_TMR3_EXIST
void TMR_3_InterruptHandler() {

	TMR_3::interruptHandler();
}
#endif


#ifdef HTL_TMR4_EXIST
void TMR_4_InterruptHandler() {

	TMR_4::interruptHandler();
}
#endif


#ifdef HTL_TMR5_EXIST
void TMR_5_InterruptHandler() {

	TMR_5::interruptHandler();
}
#endif


#ifdef HTL_TMR6_EXIST
void TMR_6_InterruptHandler() {

	TMR_6::interruptHandler();
}
#endif


#ifdef HTL_TMR7_EXIST
void TMR_7_InterruptHandler() {

	TMR_7::interruptHandler();
}
#endif


#ifdef HTL_TMR8_EXIST
void TMR_8_InterruptHandler() {

	TMR_8::interruptHandler();
}
#endif


#ifdef HTL_TMR9_EXIST
void TMR_9_InterruptHandler() {

	TMR_9::interruptHandler();
}
#endif


#ifdef HTL_TMR10_EXIST
void TMR_10_InterruptHandler() {

	TMR_10::interruptHandler();
}
#endif


#ifdef HTL_TMR11_EXIST
void TMR_11_InterruptHandler() {

	TMR_11::interruptHandler();
}
#endif


#ifdef HTL_TMR12_EXIST
void TMR_12_InterruptHandler() {

	TMR_12::interruptHandler();
}
#endif


#ifdef HTL_TMR13_EXIST
void TMR_13_InterruptHandler() {

	TMR_13::interruptHandler();
}
#endif


#ifdef HTL_TMR14_EXIST
void TMR_14_InterruptHandler() {

	TMR_14::interruptHandler();
}
#endif
