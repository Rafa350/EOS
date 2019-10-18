#include "eos.h"
#include "OSAL/osalHeap.h"
#include <stdlib.h>


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria.
/// \param    hHeap: handler del heap.
/// \param    blockSize: Tamany del bloc de memoria.
/// \return Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalHeapAlloc(
	HHeap hHeap,
	int blockSize) {

    return malloc(blockSize);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un bloc de memoria.
/// \param    hHeap: Handler del heap.
/// \param    block: Adressa del bloc de memoria.
///
void osalHeapFree(
	HHeap hHeap,
	void *block) {

	free(block);
}
