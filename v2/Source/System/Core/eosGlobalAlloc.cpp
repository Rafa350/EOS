#include "System/Core/eosMemory.hpp"


/// ----------------------------------------------------------------------
/// \brief Operador new global.
/// \param size: Tamany en bytes de la memoria a reservar.
///
void *operator new(
    size_t size) {
    
    return eosHeapAlloc(nullptr, size);
}


/// ----------------------------------------------------------------------
/// \brief Operador delete global.
/// \param ptr: Punter al bloc de memoria a alliberar.
///
void operator delete(
    void *ptr) {
    
    eosHeapFree(ptr);
}