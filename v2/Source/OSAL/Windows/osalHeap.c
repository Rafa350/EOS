#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include <stdlib.h>


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria.
/// \param    hHeap: Handler del heap
/// \param    size: Tamany del bloc de memoria.
/// \return Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalHeapAlloc(
	HHeap hHeap,
	int size) {

    return malloc(size);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un bloc de memoria.
/// \param    hHeap: Handler del heap.
/// \param    p: Adressa del bloc de memoria.
///
void osalHeapFree(
	HHeap hHeap,
	void *p) {

	free(p);
}
