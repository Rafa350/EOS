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
/// \brief    Obte un bloc de memoria.
/// \param    hHeap: Handler del heap.]
/// \param    size: Tamany del bloc de memoria.
/// \return   Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalHeapAlloc(
    HHeap hHeap,
	int size) {

    eosAssert(hHeap == NULL);
    eosAssert(size > 0);

    void *p = pvPortMalloc(size);
    eosAssert(p != NULL);

    return p;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un bloc de memoria.
/// \param    hHeap: Handler del heap.]
/// \param    p: Adressa del bloc de memoria.
///
void osalHeapFree(
    HHeap hHeap,
	void *p) {

    eosAssert(hHeap == NULL);
    eosAssert(p != NULL);

	vPortFree(p);
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
