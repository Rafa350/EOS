#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"

#include "FreeRTOS.h"

#define SAFE_MODE


static HHeap defaultHeap = NULL;


#ifdef SAFE_MODE
static const char signature[8] = { 0xAA, 'E', 'O', 'S', 0x55, 'E', 'O', 'S'};
#endif



/// ----------------------------------------------------------------------
/// \brief Crea un heap.
/// \return El handler del heap.
///
HHeap osalHeapCreate() {

    return defaultHeap;
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix el heap.
/// \param    hHeam: Handler del heap.
///
void halHeapDestroy(
	HHeap hHeap) {

}


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria del heap.
/// \param    hHeap: Handler del heap.
/// \param    size: Tamany del bloc de memoria.
/// \return   Adressa del bloc de memoria obtingut. NULL en cas d'error.
///
void* osalHeapAlloc(
    HHeap hHeap,
	int size) {

    eosAssert(hHeap == NULL);
    eosAssert(size > 0);

#ifdef SAFE_MODE
    void *block = pvPortMalloc(size + sizeof(signature));
#else
    void *block = pvPortMalloc(size);
#endif
    eosAssert(block != NULL);

#ifdef SAFE_MODE
    memcpy(block, signature, sizeof(signature));
    block = (char*)block + sizeof(signature);
#endif

    return block;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un bloc de memoria del heap.
/// \param    hHeap: Handler del heap.
/// \param    block: Adressa del bloc de memoria.
///
void osalHeapFree(
    HHeap hHeap,
	void *block) {

    eosAssert(hHeap == NULL);
    eosAssert(block != NULL);

#ifdef SAFE_MODE
    block = (char*)block - sizeof(signature);
    eosAssert(memcmp(block, signature, sizeof(signature)) == 0);
    memset(block, 0, sizeof(signature));
#endif

    vPortFree(block);
}


/// ----------------------------------------------------------------------
/// \brief    Verifica un bloc de memoria del heap.
/// \param    hHeap: Handler del heap.
/// \param    block: Adressa del bloc de memoria.
///
bool osalHeapVerify(
	HHeap hHeap,
	void* block) {

#ifdef SAFE_MODE
    block = (char*)block - sizeof(signature);
    return memcmp(block, signature, sizeof(signature)) == 0;
#else
	return true;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Obte informacio del heap.
/// \param    hHeap: El handler del heap;
/// \param    info: Adressa on deixar el resultat.
///
void osalHeapGetInfo(
	HHeap hHeap,
	HeapInformation *info) {

	eosAssert(info != NULL);

	/*HeapStats_t heapStats;
	vPortGetHeapStats(&heapStats);

	info->start = 0;
	info->length = configTOTAL_HEAP_SIZE;
	info->allocated = 0;
	info->available = 0;*/
}


/// ----------------------------------------------------------------------
/// \brief    Compatibilitat malloc per llibreries standard.
/// \param    size: Tamany del bloc de memoria.
///
void* osal_malloc(
    int size) {

    return osalHeapAlloc(NULL, size);
}


/// ----------------------------------------------------------------------
/// \brief    Compatibilitat free per llibreries standard.
/// \param    p: Adressa del bloc de memoria.
///
void osal_free(
    void *p) {

    osalHeapFree(NULL, p);
}
