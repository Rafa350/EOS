#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "FreeRTOS.h"


//static HHeap defaultHeap = NULL;


/// ----------------------------------------------------------------------
/// \brief Crea un heap.
/// \return El handler del heap.
///
HHeap osalHeapCreate() {

    return NULL;
}


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria.
/// \param[in] hHeap: Handler del heap.]
/// \param[in] blockSize: Tamany del bloc de memoria.
/// \return Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalHeapAlloc(
    HHeap hHeap,
	unsigned blockSize) {

    eosAssert(hHeap == NULL);
    eosAssert(blockSize > 0);

    void *pBlock = pvPortMalloc(blockSize);
    eosAssert(pBlock != NULL);

    return pBlock;
}


/// ----------------------------------------------------------------------
/// \brief Allivera un bloc de memoria.
/// \param[in] hHeap: Handler del heap.]
/// \param[in] pBlock: Adressa del bloc de memoria.
///
void osalHeapFree(
    HHeap hHeap,
	void *pBlock) {

    eosAssert(hHeap == NULL);
    eosAssert(pBlock != NULL);

	vPortFree(pBlock);
}
