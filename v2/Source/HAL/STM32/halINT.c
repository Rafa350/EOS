#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halINT.h"



/// ----------------------------------------------------------------------
/// \brief Asigna la prioruitat d'una interrupcio.
/// \param priority: La prioritat.
/// \param subPriority: La sub-prioritat.
///
void halINTSetPriority(
	IRQn_Type irq,
	uint32_t priority,
	uint32_t subPriority) {

	HAL_NVIC_SetPriority(irq, priority, subPriority);
}



/// ----------------------------------------------------------------------
/// \brief Activa la interrupcio IRQ especificada.
/// \param irq: identificador de la interrupcio.
///
void halINTEnableIRQ(
	IRQn_Type irq) {

	NVIC_EnableIRQ(irq);
}


/// ----------------------------------------------------------------------
/// \bried Desactiva la interrupcio especificada.
/// \param irq: identificador de la interrupcio.
///
void halINTDisableIRQ(
	IRQn_Type irq) {

	NVIC_DisableIRQ(irq);
}
