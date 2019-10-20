#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"

#include <stdlib.h>


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria.
/// \param    hHeap: handler del heap.
/// \param    size: Tamany del bloc de memoria.
/// \return   Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalHeapAlloc(
	HHeap hHeap,
	int size) {

	eosAssert(size > 0);

    return malloc(size);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un bloc de memoria.
/// \param    hHeap: Handler del heap.
/// \param    block: Adressa del bloc de memoria.
///
void osalHeapFree(
	HHeap hHeap,
	void *block) {

	eosAssert(block != NULL);

	free(block);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de momoria. Version compatible amb stdlib.
/// \param    size. Tamany del bloc.
/// \return   Adressa del bloc obtingut.
///
void *osal_malloc(int size) {

	return osalHeapAlloc(NULL, size);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un bloc de memoria. Version compatible amb stdlib
/// \param    p: Adressa del bloc.
///
void osal_free(void *p) {

	osalHeapFree(NULL, p);
}
