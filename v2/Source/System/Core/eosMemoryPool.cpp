// Implementacio basada en:
// Fast Efficient Fixed-Size Memory Pool: No Loops and No Overhead
// Ben Kenwright - School of Computer Science - Newcastle University

#include "System/Core/eosTask.hpp"
#include "System/Core/eosMemoryPool.hpp"
#include "System/core/eosMemory.hpp"


#define __LOCK()             Task::enterCriticalSection()
#define __UNLOCK()           Task::exitCriticalSection()


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param blockSize: Tamany de cada element en bytes.
/// \param maxBlocks: Numero maxim d'elements.
///
GenericMemoryPool::GenericMemoryPool(
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
        
    startBlocks = new uint8_t[blockSize * maxBlocks];
    nextBlock = startBlocks;
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
GenericMemoryPool::~GenericMemoryPool() {
    
    delete[] startBlocks;
}


/// ----------------------------------------------------------------------
/// \brief Reserva un bloc de memoria.
/// \return El punter al block.
///
void *GenericMemoryPool::allocate() {
    
    void *ret = nullptr;

    __LOCK();
    
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
    
    __UNLOCK();
    
    return ret;
}


/// ----------------------------------------------------------------------
/// \brief Allivera el bloc de memoria.
/// \param p: El puntern al bloc de memoria.
///
void GenericMemoryPool::deallocate(
    void *p) {
    
    __LOCK();
    
    if (nextBlock != nullptr) 
        *((unsigned*)p) = indexFromAddr(nextBlock);   
    else 
        *((unsigned*)p) = maxBlocks;
    
    nextBlock = (uint8_t*) p;
    freeBlocks += 1;
    
    __UNLOCK();
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa d'un bloc a partir del seu index.
/// \param i: El index del bloc.
/// \return L'adressa del bloc.
///
uint8_t *GenericMemoryPool::addrFromIndex(
    unsigned i) const {
    
    return startBlocks + (blockSize * i);
}


/// ----------------------------------------------------------------------
/// \brief Obje el index d'un bloc a partir de la seva adressa.
/// \param p: L'adressa del bloc.
/// \return El index del bloc.
///
unsigned GenericMemoryPool::indexFromAddr(
    const uint8_t *p) const {
    
    return (p - startBlocks) / blockSize;
}