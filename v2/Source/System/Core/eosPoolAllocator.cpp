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

    _blockSize(blockSize),
    _maxBlocks(maxBlocks),
    _freeBlocks(maxBlocks),
    _initializedBlocks(0) {

    // Ajusta el tamany minim del block per poder guardar un 'unsigned'
    //
    if (_blockSize < (int) sizeof(unsigned))
        _blockSize = (int) sizeof(unsigned);

    _blocks = static_cast<uint8_t*>(osalHeapAlloc(nullptr, _blockSize * _maxBlocks));
    eosAssert(_blocks != nullptr);

    _nextBlock = _blocks;
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
MemoryPoolAllocator::~MemoryPoolAllocator() {

    osalHeapFree(nullptr, _blocks);
}


/// ----------------------------------------------------------------------
/// \brief    Reserva un bloc de memoria.
/// \return   El punter al block.
///
void *MemoryPoolAllocator::allocate() {

    void *ret = nullptr;

    osalEnterCritical();

    if (_initializedBlocks < _maxBlocks) {
        int *p = (int*) addrFromIndex(_initializedBlocks);
        _initializedBlocks += 1;
        *p = _initializedBlocks;
    }

    if (_freeBlocks > 0) {
        ret = static_cast<void*>(_nextBlock);
        _freeBlocks -= 1;
        if (_freeBlocks > 0)
            _nextBlock = addrFromIndex(*((int*) _nextBlock) );
        else
            _nextBlock = nullptr;
    }

    osalExitCritical();

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

    if (_nextBlock != nullptr)
        *(static_cast<int*>(p)) = indexFromAddr(_nextBlock);
    else
        *(static_cast<int*>(p)) = _maxBlocks;

    _nextBlock = static_cast<uint8_t*>(p);
    _freeBlocks += 1;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'adressa d'un bloc a partir del seu index.
/// \param    i: El index del bloc.
/// \return   L'adressa del bloc.
///
uint8_t *MemoryPoolAllocator::addrFromIndex(
    int i) const {

    return _blocks + (_blockSize * i);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el index d'un bloc a partir de la seva adressa.
/// \param    p: L'adressa del bloc.
/// \return   El index del bloc.
///
int MemoryPoolAllocator::indexFromAddr(
    const uint8_t *p) const {

    return (p - _blocks) / _blockSize;
}
