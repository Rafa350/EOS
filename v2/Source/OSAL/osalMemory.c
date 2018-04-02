#include "osal/osalMemory.h"
#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria.
/// \param size: Tamany del bloc de memoria.
/// \return Adressa del bloc, NULL en cas d'error.
///
void *osalMemoryAlloc(
	unsigned size) {

    return pvPortMalloc(size);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un bloc de memoria.
/// \param p: Adressa del bloc de memoria.
///
void osalMemoryFree(
	void *p) {

	vPortFree(p);
}
