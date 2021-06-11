#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosHeapAllocator.h"
#include "OSAL/osalHeap.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria
/// \param    size: Tamany del bloc de momoria.
/// \return   Punter al bloc de memoria. nullptr en cas d'error.
///
void* MemoryHeapAllocator::allocate(
    unsigned size) {

    eosAssert(size > 0);

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

    eosAssert(p != nullptr);

    osalHeapFree(NULL, p);
}

/// ----------------------------------------------------------------------
/// \brief    Obte l'adresa del bloc de memoria
/// \return   El resultat.
///
uint8_t* MemoryHeapAllocator::getAddr() const {

	return nullptr;
}
