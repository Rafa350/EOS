#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halINT.h"


/// ----------------------------------------------------------------------
/// \brief    Asigna la prioritat d'una interrupcio.
/// \param    source: Identificador de la interrupcio.
/// \param    priority: La prioritat.
/// \param    subPriority: La sub-prioritat.
///
void halINTSetInterruptVectorPriority(
	uint32_t source,
	uint32_t priority,
	uint32_t subPriority) {

	uint32_t priorityGroup = NVIC_GetPriorityGrouping();
    NVIC_SetPriority((IRQn_Type) source, NVIC_EncodePriority(priorityGroup, priority, subPriority));
}


/// ----------------------------------------------------------------------
/// \brief    Activa la interrupcio IRQ especificada.
/// \param    source: Identificador de la interrupcio.
///
void halINTEnableInterruptVector(
	uint32_t vector) {

	NVIC_EnableIRQ((IRQn_Type) vector);
}


/// ----------------------------------------------------------------------
/// \brief    Activa la interrupcio IRQ especificada.
/// \param    source: Identificador de la interrupcio.
///
void halINTEnableInterruptSource(
	uint32_t source) {

	NVIC_EnableIRQ((IRQn_Type) source);
}


/// ----------------------------------------------------------------------
/// \bried    Desactiva la interrupcio especificada.
/// \param    source: Identificador de la interrupcio.
/// \return   Estat per restaurar la interrupcio.
///
bool halINTDisableInterruptSource(
	uint32_t source) {

	bool state = NVIC_GetEnableIRQ((IRQn_Type) source);
	if (state)
		NVIC_DisableIRQ((IRQn_Type) source);
	return state;
}


/// ----------------------------------------------------------------------
/// \brief    Restaura l'estat de la interrupcio.
/// \param    source: Identificadord e la interrupcio.
/// \param    state: L'estat a restaurar.
///
void halIRQRestoreInterruptSource(
	uint32_t source,
	bool state) {

	if (state)
		NVIC_EnableIRQ((IRQn_Type) source);
}
