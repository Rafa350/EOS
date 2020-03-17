#ifndef __eosPoolAllocator__
#define	__eosPoolAllocator__


#include "eos.h"


namespace eos {

    class MemoryPoolAllocator {
        private:
            uint8_t *blocks;
            uint8_t *nextBlock;
            int blockSize;
            int maxBlocks;
            int freeBlocks;
            int initializedBlocks;

        public:
            MemoryPoolAllocator(int blockSize, int maxBlocks);
            ~MemoryPoolAllocator();

            void* allocate();
            void deallocate(void* p);

            inline int getBlockSize() const { return blockSize; }
            inline int getUsedBlocks() const { return maxBlocks - freeBlocks; }
            inline int getFreeBlocks() const { return freeBlocks; }

        private:
            uint8_t* addrFromIndex(int i) const;
            int indexFromAddr(const uint8_t* p) const;
    };


    template <class T, int MAX_BLOCKS>
    class PoolAllocator {

    	private:
    		MemoryPoolAllocator allocator;

    	public:

    		PoolAllocator():
            	allocator(sizeof(T), MAX_BLOCKS) {
            }

    		inline T *allocate() {
            	return static_cast<T*>(allocator.allocate());
            }

    		inline void deallocate(T* p) {
            	allocator.deallocate(p);
            }
    };
}


#endif // __eosPoolAllocator__


