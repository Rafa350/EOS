// Implementacio basada en:
// Fast Efficient Fixed-Size Memory Pool: No Loops and No Overhead
// Ben Kenwright - School of Computer Science - Newcastle University

#include "eos.h"
#include "eosAssert.h"
#include "osal/osalThread.h"
#include "System/Core/eosPoolAllocator.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param blockSize: Tamany de cada element en bytes.
/// \param maxBlocks: Numero maxim d'elements.
///
GenericPoolAllocator::GenericPoolAllocator(
    unsigned _blockSize,
    unsigned _maxBlocks):

    blockSize(_blockSize),
    maxBlocks(_maxBlocks),
    freeBlocks(_maxBlocks),
    initializedBlocks(0) {

    // Ajusta el tamany minim del block per poder guardar un 'unsigned'
    //
    if (blockSize < sizeof(unsigned))
        blockSize = sizeof(unsigned);

    blocks = nextBlock = new uint8_t[blockSize * maxBlocks];
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
GenericPoolAllocator::~GenericPoolAllocator() {

    delete[] blocks;
}


/// ----------------------------------------------------------------------
/// \brief Reserva un bloc de memoria.
/// \param size: El tamany del bloc. Com el tamany es fixe, no s'utilitza.
/// \return El punter al block.
///
void *GenericPoolAllocator::allocate(
    size_t size) {

    void *ret = nullptr;

    if (size <= blockSize) {

        osalEnterCritical();

        if (initializedBlocks < maxBlocks) {
            unsigned *p = (unsigned*) addrFromIndex(initializedBlocks);
            initializedBlocks += 1;
            *p = initializedBlocks;
        }

        if (freeBlocks > 0) {
            ret = (void*) nextBlock;
            freeBlocks -= 1;
            if (freeBlocks > 0)
                nextBlock = addrFromIndex(*((unsigned*) nextBlock) );
            else
                nextBlock = nullptr;
        }

        osalExitCritical();

    }

    eosAssert(ret != nullptr);


    return ret;
}


/// ----------------------------------------------------------------------
/// \brief Allivera el bloc de memoria.
/// \param p: El puntern al bloc de memoria.
///
void GenericPoolAllocator::deallocate(
    void *p) {

    eosAssert(p != nullptr);

    osalEnterCritical();

    if (nextBlock != nullptr)
        *((unsigned*)p) = indexFromAddr(nextBlock);
    else
        *((unsigned*)p) = maxBlocks;

    nextBlock = (uint8_t*) p;
    freeBlocks += 1;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa d'un bloc a partir del seu index.
/// \param i: El index del bloc.
/// \return L'adressa del bloc.
///
uint8_t *GenericPoolAllocator::addrFromIndex(
    unsigned i) const {

    return blocks + (blockSize * i);
}


/// ----------------------------------------------------------------------
/// \brief Obje el index d'un bloc a partir de la seva adressa.
/// \param p: L'adressa del bloc.
/// \return El index del bloc.
///
unsigned GenericPoolAllocator::indexFromAddr(
    const uint8_t *p) const {

    return (p - blocks) / blockSize;
}
