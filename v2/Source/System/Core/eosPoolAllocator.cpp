// Implementacio basada en:
// Fast Efficient Fixed-Size Memory Pool: No Loops and No Overhead
// Ben Kenwright - School of Computer Science - Newcastle University

#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "OSAL/osalKernel.h"
#include "System/Core/eosPoolAllocator.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    blockSize: Tamany de cada element en bytes.
/// \param    maxBlocks: Numero maxim d'elements.
///
MemoryPoolAllocator::MemoryPoolAllocator(
    int blockSize,
    int maxBlocks):

    blockSize(blockSize),
    maxBlocks(maxBlocks),
    freeBlocks(maxBlocks),
    initializedBlocks(0) {

    // Ajusta el tamany minim del block per poder guardar un 'unsigned'
    //
    if (blockSize < (int) sizeof(unsigned))
        blockSize = (int) sizeof(unsigned);

    blocks = (uint8_t*) osalHeapAlloc(nullptr, blockSize * maxBlocks);
    eosAssert(blocks != nullptr);

    nextBlock = blocks;
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
MemoryPoolAllocator::~MemoryPoolAllocator() {

    osalHeapFree(NULL, blocks);
}


/// ----------------------------------------------------------------------
/// \brief    Reserva un bloc de memoria.
/// \param    size: El tamany del bloc. Com el tamany es fixe, no s'utilitza.
/// \return   El punter al block.
///
void *MemoryPoolAllocator::allocate(
    int size) {

	eosAssert(size > 0);

    void *ret = nullptr;

    if (size <= blockSize) {

        osalEnterCritical();

        if (initializedBlocks < maxBlocks) {
            int *p = (int*) addrFromIndex(initializedBlocks);
            initializedBlocks += 1;
            *p = initializedBlocks;
        }

        if (freeBlocks > 0) {
            ret = static_cast<void*>(nextBlock);
            freeBlocks -= 1;
            if (freeBlocks > 0)
                nextBlock = addrFromIndex(*((int*) nextBlock) );
            else
                nextBlock = nullptr;
        }

        osalExitCritical();

    }

    eosAssert(ret != nullptr);

    return ret;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera el bloc de memoria.
/// \param    p: El puntern al bloc de memoria.
///
void MemoryPoolAllocator::deallocate(
    void *p) {

    eosAssert(p != nullptr);

    osalEnterCritical();

    if (nextBlock != nullptr)
        *(static_cast<int*>(p)) = indexFromAddr(nextBlock);
    else
        *(static_cast<int*>(p)) = maxBlocks;

    nextBlock = static_cast<uint8_t*>(p);
    freeBlocks += 1;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'adressa d'un bloc a partir del seu index.
/// \param    i: El index del bloc.
/// \return   L'adressa del bloc.
///
uint8_t *MemoryPoolAllocator::addrFromIndex(
    int i) const {

    return blocks + (blockSize * i);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el index d'un bloc a partir de la seva adressa.
/// \param    p: L'adressa del bloc.
/// \return   El index del bloc.
///
int MemoryPoolAllocator::indexFromAddr(
    const uint8_t *p) const {

    return (p - blocks) / blockSize;
}
