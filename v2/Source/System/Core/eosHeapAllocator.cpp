#include "System/Core/eosHeapAllocator.h"
#include "eosAssert.h"
#include "osal/osalMemory.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Obte un bloc de memoria
/// \param size: Tamany del bloc de momoria.
/// \return Punter al bloc de memoria. nullptr en cas d'error.
///
void *HeapAllocator::allocate(
    size_t size) {

    eosArgumentIsNotZero(size);

    void *p;
    osalMemoryAlloc(size, &p);
    eosAssert(p != nullptr);

    return p;
}


/// ----------------------------------------------------------------------
/// \brief Allibera un bloc de memoria.
/// \param p: Punter al bloc de memoria.
///
void HeapAllocator::deallocate(
    void *p) {

    eosArgumentIsNotNull(p);

    osalMemoryFree(p);
}
