#include "eos.h"
#include "eosAssert.h"
#include "osal/osalMemory.h"
#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria.
/// \param size: Tamany del bloc de memoria.
/// \return Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalMemoryAlloc(
	unsigned size) {

    eosAssert(size > 0);

    void *p = pvPortMalloc(size);
    eosAssert(p != NULL);

    return p;
}


/// ----------------------------------------------------------------------
/// \brief Allivera un bloc de memoria.
/// \param p: Adressa del bloc de memoria.
///
void osalMemoryFree(
	void *p) {

    eosAssert(p != NULL);

	vPortFree(p);
}
