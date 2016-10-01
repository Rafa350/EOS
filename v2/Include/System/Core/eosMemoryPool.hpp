#ifndef __EOS_MEMORYPOOL_HPP
#define	__EOS_MEMORYPOOL_HPP


#include "eos.hpp"


namespace eos {
    
    class GenericMemoryPool {
        private:
            uint8_t *startBlocks;
            uint8_t *nextBlock;
            unsigned blockSize;
            unsigned maxBlocks;
            unsigned freeBlocks;
            unsigned initializedBlocks;
            
        public:
            GenericMemoryPool(unsigned blocktSize, unsigned maxBlocks);
            ~GenericMemoryPool();
            
            void *allocate();
            void deallocate(void *p);
            
            template <class T> inline T *allocate() { return (T*) allocate(); }
            
            inline unsigned getBlockSize() const { return blockSize; }
            inline unsigned getUsedBlocks() const { return maxBlocks - freeBlocks; }
            inline unsigned getFreeBlocks() const { return freeBlocks; }
            
        private:
            uint8_t *addrFromIndex(unsigned i) const;
            unsigned indexFromAddr(const uint8_t *p) const;
    };
    
    template <class T>
    class MemoryPool: public GenericMemoryPool {
        public:
            inline MemoryPool(unsigned maxBlocks) : GenericMemoryPool(sizeof(T), maxBlocks) {}
            inline T* allocate() { return (T*) GenericMemoryPool::allocate(); }
    };
    
}


#endif	


