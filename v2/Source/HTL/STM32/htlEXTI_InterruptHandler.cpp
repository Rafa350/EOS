#include "eos.h"
#include "HTL/STM32/htlEXTI.h"
#include "HTL/STM32/htlEXTI_InterruptHandler.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI0
///
void EXTI_0_InterruptHandler() {

	if (EXTI_0::getInterruptFlag()) {
		EXTI_0::interruptHandler(EXTIEvent::change);
		EXTI_0::clearInterruptFlag();
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI1
///
void EXTI_1_InterruptHandler() {

	if (EXTI_1::getInterruptFlag()) {
		EXTI_1::interruptHandler(EXTIEvent::change);
		EXTI_1::clearInterruptFlag();
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI2
///
void EXTI_2_InterruptHandler() {

	if (EXTI_2::getInterruptFlag()) {
		EXTI_2::interruptHandler(EXTIEvent::change);
		EXTI_2::clearInterruptFlag();
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI3
///
void EXTI_3_InterruptHandler() {

	if (EXTI_3::getInterruptFlag()) {
		EXTI_3::interruptHandler(EXTIEvent::change);
		EXTI_3::clearInterruptFlag();
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI4
///
void EXTI_4_InterruptHandler() {

	if (EXTI_4::getInterruptFlag()) {
		EXTI_4::interruptHandler(EXTIEvent::change);
		EXTI_4::clearInterruptFlag();
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI5 fins EXTI9
///
void EXTI_5_6_7_8_9_InterruptHandler() {

	// Obte les interrupcions pendents
	//
	uint32_t pending = EXTI->PR & (EXTI_PR_PR5 | EXTI_PR_PR6 | EXTI_PR_PR7 | EXTI_PR_PR8 | EXTI_PR_PR9);
    if (pending != 0) {

		if (EXTI_5::getInterruptFlag())
			EXTI_5::interruptHandler(EXTIEvent::change);

		if (EXTI_6::getInterruptFlag())
			EXTI_6::interruptHandler(EXTIEvent::change);

		if (EXTI_7::getInterruptFlag())
			EXTI_7::interruptHandler(EXTIEvent::change);

		if (EXTI_8::getInterruptFlag())
			EXTI_8::interruptHandler(EXTIEvent::change);

		if (EXTI_9::getInterruptFlag())
			EXTI_9::interruptHandler(EXTIEvent::change);

		// Borra les interrupcions pendents
		//
		EXTI->PR = pending;
    }
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI10 fins EXTI15
///
void EXTI_10_11_12_13_14_15_InterruptHandler() {

	// Obte les interrupcions pendents
	//
	uint32_t pending = EXTI->PR & (EXTI_PR_PR10 | EXTI_PR_PR11 | EXTI_PR_PR12 | EXTI_PR_PR13 | EXTI_PR_PR14 | EXTI_PR_PR15);
    if (pending != 0) {

    	if (EXTI_10::getInterruptFlag())
    		EXTI_10::interruptHandler(EXTIEvent::change);

    	if (EXTI_11::getInterruptFlag())
    		EXTI_11::interruptHandler(EXTIEvent::change);

    	if (EXTI_12::getInterruptFlag())
    		EXTI_12::interruptHandler(EXTIEvent::change);

    	if (EXTI_13::getInterruptFlag())
    		EXTI_13::interruptHandler(EXTIEvent::change);

    	if (EXTI_14::getInterruptFlag())
    		EXTI_14::interruptHandler(EXTIEvent::change);

    	if (EXTI_15::getInterruptFlag())
    		EXTI_15::interruptHandler(EXTIEvent::change);

		// Borra les interrupcions pendents
		//
    	EXTI->PR = pending;
    }
}


