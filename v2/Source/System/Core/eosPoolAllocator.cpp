// Implementacio basada en:
// Fast Efficient Fixed-Size Memory Pool: No Loops and No Overhead
// Ben Kenwright - School of Computer Science - Newcastle University

#include "System/Core/eosPoolAllocator.hpp"
#include "System/Core/eosTask.hpp"


#define __LOCK()             Task::enterCriticalSection()
#define __UNLOCK()           Task::exitCriticalSection()


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
        
    startBlocks = new uint8_t[blockSize * maxBlocks];
    nextBlock = startBlocks;
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
GenericPoolAllocator::~GenericPoolAllocator() {
    
    delete[] startBlocks;
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
        
    }
    
    eosAssert(
        ret != nullptr, 
        0, "PoolAllocator::allocate: No hi ha memoria disponoble.");
    
    
    return ret;
}


/// ----------------------------------------------------------------------
/// \brief Allivera el bloc de memoria.
/// \param p: El puntern al bloc de memoria.
///
void GenericPoolAllocator::deallocate(
    void *p) {
        
    eosAssert(
        p == nullptr, 
        0, "PoolAllocator::deallocate: El parametre 'p' es nul.");

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
uint8_t *GenericPoolAllocator::addrFromIndex(
    unsigned i) const {
    
    return startBlocks + (blockSize * i);
}


/// ----------------------------------------------------------------------
/// \brief Obje el index d'un bloc a partir de la seva adressa.
/// \param p: L'adressa del bloc.
/// \return El index del bloc.
///
unsigned GenericPoolAllocator::indexFromAddr(
    const uint8_t *p) const {
    
    return (p - startBlocks) / blockSize;
}
