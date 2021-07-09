#ifndef __eosPoolAllocator__
#define	__eosPoolAllocator__


#include "eos.h"
#include "eosAssert.h"


namespace eos {

	/// \brief Pool de memoria generic
    ///
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

            inline void* getAddr() const { return _blocks; }
            inline unsigned getSize() const { return _blockSize * _maxBlocks; }

            inline int getBlockSize() const { return _blockSize; }
            inline int getUsedBlocks() const { return _maxBlocks - _freeBlocks; }
            inline int getFreeBlocks() const { return _freeBlocks; }

        private:
            uint8_t* addrFromIndex(int i) const;
            int indexFromAddr(const uint8_t* p) const;
    };


    /// \brief Pool de memoria
    ///
    template <typename T, int MAX_BLOCKS>
    class PoolAllocator {

    	private:
    		MemoryPoolAllocator _allocator;

    	public:

    		PoolAllocator():
            	_allocator(sizeof(T), MAX_BLOCKS) {
            }

    		inline T *allocate() {
    			void *p = _allocator.allocate();
    			eosAssert(p != nullptr);
            	return static_cast<T*>(p);
            }

    		inline void deallocate(T *p) {
            	_allocator.deallocate(p);
            }
    };

    /// \brief Base pels objectes del pool de memoria
    ///
    template <typename T, int MAX_BLOCKS>
    class PoolAllocatable {
    	private:
    		inline static PoolAllocator<T, MAX_BLOCKS> _allocator = PoolAllocator<T, MAX_BLOCKS>();

    	public:
        	void* operator new(unsigned size) {
        		return _allocator.allocate();
        	}

        	void operator delete(void *p) {
        		_allocator.deallocate(static_cast<T*>(p));
        	}
    };
}


#endif // __eosPoolAllocator__


