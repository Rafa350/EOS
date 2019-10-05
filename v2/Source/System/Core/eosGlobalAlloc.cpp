#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosHeapAllocator.h"


static eos::HeapAllocator defaultAllocator;


/// ----------------------------------------------------------------------
/// \brief Operador new global.
/// \param size: Tamany en bytes de la memoria a reservar.
///
void *operator new(
    size_t size) {

    // Precondicions
    //
    eosAssert(size > 0);

    void *p = defaultAllocator.allocate(size);
    eosAssert(p != nullptr);
    
    return p;
}


/// ----------------------------------------------------------------------
/// \brief Operador delete global.
/// \param p: Punter al bloc de memoria a alliberar.
///
void operator delete(
    void *p) {

    // Precondicions
    //
    eosAssert(p != NULL);

    defaultAllocator.deallocate(p);
}
