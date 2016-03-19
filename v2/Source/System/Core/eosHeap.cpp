#include "System/Core/eosMemory.hpp"
#include "FreeRTOS.h"


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
/// \param size : Tamany del bloc de memoria
///
void *eosHeapAlloc(
    eosHeapHandle hHeap,
    unsigned size) {
    
    return pvPortMalloc(size);
}


/// ----------------------------------------------------------------------
/// \brief Allibera un bloc de memoria del heap.
/// \param p: Punter al bloc de memoria
///
void eosHeapFree(
    void *p) {

    vPortFree(p);
}
