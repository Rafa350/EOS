#include "osal/osalMemory.h"
#include <stdlib.h>


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria.
/// \param size: Tamany del bloc de memoria.
/// \return Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalMemoryAlloc(
	unsigned size) {

    return malloc(size);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un bloc de memoria.
/// \param p: Adressa del bloc de memoria.
///
void osalMemoryFree(
	void *p) {

	free(p);
}
