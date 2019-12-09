#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"


/// ----------------------------------------------------------------------
/// \brief Operador new global.
/// \param size: Tamany en bytes de la memoria a reservar.
///
void* operator new(
    size_t size) {

    eosAssert(size > 0);

    void *p = osalHeapAlloc(nullptr, size);
    eosAssert(p != nullptr);
    
    return p;
}


/// ----------------------------------------------------------------------
/// \brief Operador delete global.
/// \param p: Punter al bloc de memoria a alliberar.
///
void operator delete(
    void* p) {

    eosAssert(p != nullptr);

    osalHeapFree(nullptr, p);
}
