#ifndef __eosPoolAllocator__
#define	__eosPoolAllocator__


#include "eos.h"


namespace eos {

    class MemoryPoolAllocator {
        private:
            uint8_t *_blocks;
            uint8_t *_nextBlock;
            int _blockSize;
            int _maxBlocks;
            int _freeBlocks;
            int _initializedBlocks;

        public:
            MemoryPoolAllocator(int blockSize, int maxBlocks);
            ~MemoryPoolAllocator();

            void* allocate();
            void deallocate(void* p);

            inline uint8_t* getAddr() const { return _blocks; }
            inline unsigned getSize() const { return _blockSize * _maxBlocks; }

            inline int getBlockSize() const { return _blockSize; }
            inline int getUsedBlocks() const { return _maxBlocks - _freeBlocks; }
            inline int getFreeBlocks() const { return _freeBlocks; }

        private:
            uint8_t* addrFromIndex(int i) const;
            int indexFromAddr(const uint8_t* p) const;
    };


    template <class T, int MAX_BLOCKS>
    class PoolAllocator {

    	private:
    		MemoryPoolAllocator _allocator;

    	public:

    		PoolAllocator():
            	_allocator(sizeof(T), MAX_BLOCKS) {
            }

    		inline T *allocate() {
            	return static_cast<T*>(_allocator.allocate());
            }

    		inline void deallocate(T* p) {
            	_allocator.deallocate(p);
            }
    };
}


#endif // __eosPoolAllocator__


