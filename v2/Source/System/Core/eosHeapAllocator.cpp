#include "eos.h"
#include "System/Core/eosHeapAllocator.h"
#include "RTOS/rtosHeap.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria
/// \param    size: Tamany del bloc de momoria.
/// \return   Punter al bloc de memoria. nullptr en cas d'error.
///
void* MemoryHeapAllocator::allocate(
    uint32_t size) {

    return rtos::Heap::allocate(size);
}


/// ----------------------------------------------------------------------
/// \brief    Allibera un bloc de memoria.
/// \param    p: Punter al bloc de memoria.
///
void MemoryHeapAllocator::deallocate(
    void *ptr) {

	rtos::Heap::deallocate(ptr);
}

