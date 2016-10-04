#ifndef __EOS_POOLALLOCATOR_HPP
#define	__EOS_POOLALLOCATPR_HPP


#include "eos.hpp"
#include "System/Core/eosAllocator.hpp"


namespace eos {
       
    class GenericPoolAllocator: IAllocator {
        private:
            uint8_t *blocks;
            uint8_t *nextBlock;
            unsigned blockSize;
            unsigned maxBlocks;
            unsigned freeBlocks;
            unsigned initializedBlocks;
            
        public:
            GenericPoolAllocator(unsigned blockSize, unsigned maxBlocks);
            ~GenericPoolAllocator();
            
            void *allocate(size_t size);
            void deallocate(void *p);
            
            inline unsigned getBlockSize() const { return blockSize; }
            inline unsigned getUsedBlocks() const { return maxBlocks - freeBlocks; }
            inline unsigned getFreeBlocks() const { return freeBlocks; }
            
        private:
            uint8_t *addrFromIndex(unsigned i) const;
            unsigned indexFromAddr(const uint8_t *p) const;
    };
    
    template <class T>
    class PoolAllocator: public GenericPoolAllocator {
        public:
            inline PoolAllocator(unsigned maxBlocks): GenericPoolAllocator(sizeof(T), maxBlocks) {}
            inline T *allocate(size_t size) { return (T*) GenericPoolAllocator::allocate(size); }
    };
}


#endif	


