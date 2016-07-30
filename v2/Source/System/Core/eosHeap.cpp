#include "System/Core/eosMemory.hpp"
#include "FreeRTOS.h"



unsigned totalAllocations = 0;
unsigned totalDeallocations = 0;
unsigned totalBytesAllocated = 0;


typedef struct __eosHeap {   
} eosHeap;


/// ----------------------------------------------------------------------
/// \brief Crea un heap.
/// \param size: Tamany del heap en bytes
///
eosHeapHandle eosHeapCreate(
    unsigned size) {

    return NULL;
}


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria del heap.
/// \param hHeap: Handler del heap. 
/// \param size: Tamany del bloc de memoria
///
void *eosHeapAlloc(
    eosHeapHandle hHeap,
    unsigned size) {
    
    totalAllocations++;
    totalBytesAllocated += size;
    
    void *p = pvPortMalloc(size);
    
    eosAssert(p != nullptr, 0, "eosHeapAlloc: No memory.");
    
    return p;
}


/// ----------------------------------------------------------------------
/// \brief Allibera un bloc de memoria del heap.
/// \param p: Punter al bloc de memoria
///
void eosHeapFree(
    void *p) {
    
    totalDeallocations++;

    vPortFree(p);
}
