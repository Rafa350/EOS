#include "eos.h"
#include "osal/osalMemory.h"
#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria.
/// \param size: Tamany del bloc de memoria.
/// \return Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalMemoryAlloc(
	size_t size) {

	// Comprova si els parametres son correctes.
	//
	if (size == 0)
		return NULL;

	// Obte el bloc de memoria
	//
    return pvPortMalloc(size);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un bloc de memoria.
/// \param p: Adressa del bloc de memoria.
///
void osalMemoryFree(
	void *p) {

	// Comprova si els parametres son correctes.
	//
	if (p == NULL)
		return;

	vPortFree(p);
}
