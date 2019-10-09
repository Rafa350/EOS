#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "FreeRTOS.h"


static HHeap defaultHeap = NULL;


/// ----------------------------------------------------------------------
/// \brief Crea un heap.
/// \return El handler del heap.
///
HHeap osalHeapCreate() {

    return defaultHeap;
}


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria.
/// \param[in] hHeap: Handler del heap.]
/// \param[in] blockSize: Tamany del bloc de memoria.
/// \return Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalHeapAlloc(
    HHeap hHeap,
	int blockSize) {

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


/// ----------------------------------------------------------------------
/// \brief    Obte informacio del heap.
/// ºparam    hHeap: El handler del heap;
/// \param    pInfo: Adressa on deixar el resultat.
///
void osalHeapGetInformation(
	HHeap hHeap,
	HeapInformation *pInfo) {

	eosAssert(pInfo != NULL);
}
