#include "HTL/htl.h"
#include "HTL/STM32/htlEXTI.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl::exti;


unsigned internal::Activator::_activated = 0;


void ExINT::setPort(
	EXTILine line,
	htl::gpio::PortID portID) {

	#if defined(EOS_PLATFORM_STM32G0)

	/// Asigna el port GPIO a la linia EXTI
	//
    uint32_t tmp = EXTI->EXTICR[(uint32_t)line >> 2u];
    tmp &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * ((uint32_t)line & 0x03u)));
    tmp |= ((uint32_t)portID << (EXTI_EXTICR1_EXTI1_Pos * ((uint32_t)line & 0x03u)));
    EXTI->EXTICR[(uint32_t)line >> 2u] = tmp;


	#else
		#error "Unknown platform"
	#endif
}


void ExINT::setMode(
	EXTILine line,
	EXTIMode mode) {

	#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre IMR (Interrupt Mask Register);
	//
	if ((mode == EXTIMode::interrupt) || (mode == EXTIMode::all))
		EXTI->IMR1 |= 1 << uint32_t(line);
	else
		EXTI->IMR1 &= ~(1 << uint32_t(line));

	// Configura el registre EMR (Event Mask Register);
	//
	if ((mode == EXTIMode::event) || (mode == EXTIMode::all))
		EXTI->EMR1 |= 1 << uint32_t(line);
	else
		EXTI->EMR1 &= ~(1 << uint32_t(line));

	#else
		#error "Unknown platform"
	#endif
}


void ExINT::setTrigger(
	EXTILine line,
	EXTITrigger trigger) {

	#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::rissing) || (trigger == EXTITrigger::all))
		EXTI->RTSR1 |= 1 << uint32_t(line);
	else
		EXTI->RTSR1 &= ~(1 << uint32_t(line));

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::falling) || (trigger == EXTITrigger::all))
		EXTI->FTSR1 |= 1 << uint32_t(line);
	else
		EXTI->FTSR1 &= ~(1 << uint32_t(line));

	#else
		#error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la linia d'interrupcio externa.
/// \param    portID: El port.
/// \param    mode: El modus event/interrupt
/// \param    triger: El flanc.
///
void ExINT::init(htl::gpio::PortID portID, EXTIMode mode, EXTITrigger trigger) {
	activate();
	setPort(_line, portID);
	setMode(_line, mode);
	setTrigger(_line, trigger);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void ExINT::deinitialize() {
	deactivate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void ExINT::interruptService() {

	uint32_t mask = 1 << uint32_t(_line);

	// Procesa la interrupcio del flanc negatiu
	//
	if (EXTI->FPR1 & mask) {
		EXTI->FPR1 = mask;
	}

	// Procesa la interrupcio del flanc positiu
	//
	if (EXTI->RPR1 & mask) {
		EXTI->RPR1 = mask;
	}
}
