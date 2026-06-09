// Implementacio basada en:
// Fast Efficient Fixed-Size Memory Pool: No Loops and No Overhead
// Ben Kenwright - School of Computer Science - Newcastle University

#include "eos.h"
#include "RTOS/rtosCriticalSection.h"
#include "RTOS/rtosHeap.h"
#include "RTOS/rtosPool.h"

#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    blockSize: Tamany de cada element en bytes.
/// \param    maxBlocks: Numero maxim d'elements.
///
rtos::Pool::Pool(
    uint32_t blockSize,
    uint32_t maxBlocks):

    _blockSize {blockSize},
    _maxBlocks {maxBlocks},
    _freeBlocks {maxBlocks},
    _initializedBlocks {0} {

    // Ajusta el tamany minim del block per poder guardar un 'uint32_t'
    //
    if (_blockSize < sizeof(uint32_t))
        _blockSize = sizeof(uint32_t);

    // Ajusta el tamany del bloc per que quedi aliniat
    //
#if portBYTE_ALIGNMENT != 1
	if (blockSize & portBYTE_ALIGNMENT_MASK)
		blockSize += portBYTE_ALIGNMENT - (blockSize & portBYTE_ALIGNMENT_MASK);
#endif

    _blocks = static_cast<uint8_t*>(rtos::Heap::allocate(_blockSize * _maxBlocks));
    _nextBlock = _blocks;
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
rtos::Pool::~Pool() {

    rtos::Heap::deallocate(_blocks);
}


/// ----------------------------------------------------------------------
/// \brief    Reserva un bloc de memoria.
/// \return   El punter al block.
///
void *rtos::Pool::allocate() {

    void *ptr = nullptr;

    rtos::CriticalSection::enter();

    if (_initializedBlocks < _maxBlocks) {
        uint32_t *p = reinterpret_cast<uint32_t*>(addrFromIndex(_initializedBlocks));
        _initializedBlocks += 1;
        *p = _initializedBlocks;
    }

    if (_freeBlocks > 0) {
        ptr = static_cast<void*>(_nextBlock);
        _freeBlocks -= 1;
        if (_freeBlocks > 0)
            _nextBlock = addrFromIndex(*(reinterpret_cast<uint32_t*>(_nextBlock)));
        else
            _nextBlock = nullptr;
    }

    rtos::CriticalSection::exit();

    return ptr;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera el bloc de memoria.
/// \param    ptr: El puntern al bloc de memoria.
///
void rtos::Pool::deallocate(
    void *ptr) {

    rtos::CriticalSection::enter();

    if (_nextBlock != nullptr)
        *(static_cast<uint32_t*>(ptr)) = indexFromAddr(_nextBlock);
    else
        *(static_cast<uint32_t*>(ptr)) = _maxBlocks;

    _nextBlock = static_cast<uint8_t*>(ptr);
    _freeBlocks += 1;

    rtos::CriticalSection::exit();
}


uint32_t rtos::Pool::getAllocatedSize() {

	return (_maxBlocks - _freeBlocks) * _blockSize;
}


uint32_t rtos::Pool::getAvailableSize() {

	return _freeBlocks * _blockSize;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'adressa d'un bloc a partir del seu index.
/// \param    i: El index del bloc.
/// \return   L'adressa del bloc.
///
uint8_t *rtos::Pool::addrFromIndex(
    uint32_t idx) const {

    return _blocks + (_blockSize * idx);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el index d'un bloc a partir de la seva adressa.
/// \param    p: L'adressa del bloc.
/// \return   El index del bloc.
///
uint32_t rtos::Pool::indexFromAddr(
    const uint8_t *ptr) const {

    return (ptr - _blocks) / _blockSize;
}
