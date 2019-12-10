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
/// \param    hHeap: Handler del heap.
/// \param    size: Tamany del bloc de memoria.
/// \return   Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void *osalHeapAlloc(
    HHeap hHeap,
	unsigned size) {

    eosAssert(hHeap == NULL);
    eosAssert(size > 0);

    void* p = pvPortMalloc(size);
    eosAssert(p != NULL);

    return p;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un bloc de memoria.
/// \param    hHeap: Handler del heap.
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
/// \param    hHeap: El handler del heap;
/// \param    info: Adressa on deixar el resultat.
///
void osalHeapGetInformation(
	HHeap hHeap,
	HeapInformation *info) {

	eosAssert(info != NULL);
}


/// ----------------------------------------------------------------------
/// \brief    Compatibilitat malloc per llibreries standard.
/// \param    size: Tamany del bloc de memoria.
///
void* osal_malloc(
    unsigned size) {

    return osalHeapAlloc(NULL, size);
}


/// ----------------------------------------------------------------------
/// \brief    Compatibilitat free per llibreries standard.
/// \param    p: Adressa del bloc de memoria.
///
void osal_free(
    void* p) {

    osalHeapFree(NULL, p);
}
