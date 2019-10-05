#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosHeapAllocator.h"
#include "osal/osalHeap.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Obte un bloc de memoria
/// \param    blockSize: Tamany del bloc de momoria.
/// \return   Punter al bloc de memoria. nullptr en cas d'error.
///
void *HeapAllocator::allocate(
    int blockSize) {

    // Precondicions
    //
    eosAssert(blockSize > 0);

    // Obte el bloc de memoria
    //
    void *pBlock = osalHeapAlloc(NULL, blockSize);
    eosAssert(pBlock != nullptr);

    return pBlock;
}


/// ----------------------------------------------------------------------
/// \brief    Allibera un bloc de memoria.
/// \param    pBlock: Punter al bloc de memoria.
///
void HeapAllocator::deallocate(
    void *pBlock) {

    // Precondicions
    //
    eosAssert(pBlock != nullptr);

    // Allivera el bloc de memoria
    //
    osalHeapFree(NULL, pBlock);
}
