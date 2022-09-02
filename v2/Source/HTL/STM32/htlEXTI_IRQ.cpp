#include "eos.h"
#include "HTL/STM32/htlEXTI.h"
#include "HTL/STM32/htlEXTI_IRQ.h"


using namespace htl;


template <typename exti_>
inline void processInterrupt(EXTIEvent event) {

	if (exti_::getInterruptFlag()) {
		exti_::clearInterruptFlag();
		exti_::interruptHandler(event);
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI0
///
void EXTI_0_InterruptHandler() {

	processInterrupt<EXTI_0>(EXTIEvent::change);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI1
///
void EXTI_1_InterruptHandler() {

	processInterrupt<EXTI_1>(EXTIEvent::change);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI2
///
void EXTI_2_InterruptHandler() {

	processInterrupt<EXTI_2>(EXTIEvent::change);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI3
///
void EXTI_3_InterruptHandler() {

	processInterrupt<EXTI_3>(EXTIEvent::change);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI4
///
void EXTI_4_InterruptHandler() {

	processInterrupt<EXTI_4>(EXTIEvent::change);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI5 fins EXTI9
///
void EXTI_5_6_7_8_9_InterruptHandler() {

	processInterrupt<EXTI_5>(EXTIEvent::change);
	processInterrupt<EXTI_6>(EXTIEvent::change);
	processInterrupt<EXTI_7>(EXTIEvent::change);
	processInterrupt<EXTI_8>(EXTIEvent::change);
	processInterrupt<EXTI_9>(EXTIEvent::change);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI10 fins EXTI15
///
void EXTI_10_11_12_13_14_15_InterruptHandler() {

	processInterrupt<EXTI_10>(EXTIEvent::change);
	processInterrupt<EXTI_11>(EXTIEvent::change);
	processInterrupt<EXTI_12>(EXTIEvent::change);
	processInterrupt<EXTI_13>(EXTIEvent::change);
	processInterrupt<EXTI_14>(EXTIEvent::change);
	processInterrupt<EXTI_15>(EXTIEvent::change);
}


