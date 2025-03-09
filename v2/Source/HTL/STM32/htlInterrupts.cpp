module;


#include "HTL/htl.h"


#if defined(EOS_PLATFORM_STM32G0)
export import htl.interrupts.stm32g0;
#elif defined(EOS_PLATFORM_STM32F0)
export import htl.interrupts.stm32f0;
#elif defined(EOS_PLATFORM_STM32F4)
export import htl.interrupts.stm32f4;
#elif defined(EOS_PLATFORM_STM32F7)
export import htl.interrupts.stm32f7;
#else
	#error "Unsuported platform."
#endif
export module htl.interrupts;


export namespace htl::interrupts {

	enum class Priority {
		p0,
		p1,
		p2,
		p3,
		p4,
		p5,
		p6,
		p7,
		p8,
		p9,
		p10,
		p11,
		p12,
		p13,
		p14,
		p15
	};

	enum class SubPriority {
		sp0,
		sp1,
		sp2,
		sp3
	};


	void setInterruptVectorPriority(VectorID vectorID, Priority priority, SubPriority subPriority = SubPriority::sp0);

	void enableInterruptVector(VectorID vectorID);
	void disableInterruptVector(VectorID vectorID);

	bool getInterruptState();
	void enableInterrupts();
	void disableInterrupts();
	void restoreInterrupts(	bool state);

}



/// --------------------------------------------------------------------
/// \brief    Configura la prioritat d'un vector d'interrupcio.
/// \param    vectorID: El identificador del vector.
/// \param    priority: La prioritat.
/// \param    subPriority: La sub-prioritat.
///
void htl::interrupts::setInterruptVectorPriority(
	VectorID vectorID,
	Priority priority,
	SubPriority subPriority) {

	uint32_t priorityGroup = NVIC_GetPriorityGrouping();

	NVIC_SetPriority((IRQn_Type) vectorID,
		NVIC_EncodePriority(priorityGroup, (uint32_t) priority, (uint32_t) subPriority));
}


/// --------------------------------------------------------------------
/// \brief   Habilita un vector d'interrupcio.
/// \param   vectorID: El identificador del vector.
///
void htl::interrupts::enableInterruptVector(
	VectorID vectorID) {

	NVIC_EnableIRQ((IRQn_Type) vectorID);
}


/// --------------------------------------------------------------------
/// \brief   Desabilita un vector d'interrupcio.
/// \param   vectorID: El identificador del vector.
///
void htl::interrupts::disableInterruptVector(
	VectorID vectorID) {

	NVIC_DisableIRQ((IRQn_Type) vectorID);
}


bool htl::interrupts::getInterruptState() {
	return __get_PRIMASK() == 0;
}


void htl::interrupts::enableInterrupts() {
	__enable_irq();
}


void htl::interrupts::disableInterrupts() {
	__disable_irq();
}


void htl::interrupts::restoreInterrupts(
	bool state) {
	if (state)
		__enable_irq();
}
