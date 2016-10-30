#include "eosAssert.hpp"
#include "System/Core/eosHeapAllocator.hpp"


static eos::HeapAllocator defaultAllocator;


/// ----------------------------------------------------------------------
/// \brief Operador new global.
/// \param size: Tamany en bytes de la memoria a reservar.
///
void *operator new(
    size_t size) {
    
    eosArgumentIsNotZero("size", size);
    
    return defaultAllocator.allocate(size);
}


/// ----------------------------------------------------------------------
/// \brief Operador delete global.
/// \param p: Punter al bloc de memoria a alliberar.
///
void operator delete(
    void *p) {
    
    eosArgumentIsNotNull("p", p);

    defaultAllocator.deallocate(p);
}
