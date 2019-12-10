#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosHeapAllocator.h"
#include "osal/osalHeap.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria
/// \param    size: Tamany del bloc de momoria.
/// \return   Punter al bloc de memoria. nullptr en cas d'error.
///
void* MemoryHeapAllocator::allocate(
    unsigned size) {

    // Precondicions
    //
    eosAssert(size > 0);

    // Obte el bloc de memoria
    //
    void* p = osalHeapAlloc(NULL, size);
    eosAssert(p != nullptr);

    return p;
}


/// ----------------------------------------------------------------------
/// \brief    Allibera un bloc de memoria.
/// \param    p: Punter al bloc de memoria.
///
void MemoryHeapAllocator::deallocate(
    void* p) {

    // Precondicions
    //
    eosAssert(p != nullptr);

    // Allivera el bloc de memoria
    //
    osalHeapFree(NULL, p);
}
