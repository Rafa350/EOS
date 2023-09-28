#include "HTL/htl.h"
#include "HTL/STM32/htlINT.h"


using namespace htl;


void irq::setInterruptVectorPriority(
	VectorID vectorID,
	Priority priority,
	SubPriority subPriority) {

	uint32_t priorityGroup = NVIC_GetPriorityGrouping();
	NVIC_SetPriority((IRQn_Type)vectorID, NVIC_EncodePriority(priorityGroup, (uint32_t)priority, (uint32_t)subPriority));
}
