#ifndef __eosPoolAllocator__
#define	__eosPoolAllocator__


#include "eos.h"
#include "eosAssert.h"
#include "System/eosSingleton.h"


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

            inline void* getAddr() const {
            	return _blocks;
            }

            inline unsigned getSize() const {
            	return _blockSize * _maxBlocks;
            }

            inline int getBlockSize() const {
            	return _blockSize;
            }

            inline int getUsedBlocks() const {
            	return _maxBlocks - _freeBlocks;
            }

            inline int getFreeBlocks() const {
            	return _freeBlocks;
            }

        private:
            uint8_t* addrFromIndex(int i) const;
            int indexFromAddr(const uint8_t* p) const;
    };


    /// \brief Pool de memoria
    ///
    template <typename T_, int maxBlocks_>
    class PoolAllocator {

    	private:
    		MemoryPoolAllocator _allocator;

    	public:

    		PoolAllocator():
            	_allocator(sizeof(T_), maxBlocks_) {
            }

    		inline T_* allocate() {
    			void* p = _allocator.allocate();
    			eosAssert(p != nullptr);
            	return static_cast<T_*>(p);
            }

    		inline void deallocate(T_* p) {
    			eosAssert(p != nullptr);
            	_allocator.deallocate(p);
            }
    };

    /// \brief Base pels objectes del pool de memoria
    ///
    template <typename T_, int maxBlocks_>
    class PoolAllocatable {
    	private:
    		typedef Singleton<PoolAllocator<T_, maxBlocks_>> Allocator;

    	public:
        	void* operator new(unsigned size) {

        		eosAssert(size == sizeof(T_));

        		auto &allocator = Allocator::instance();
        		return allocator.allocate();
        	}

        	void operator delete(void *p) {

        		eosAssert(p != nullptr);

        		auto &allocator = Allocator::instance();
        		allocator.deallocate(static_cast<T_*>(p));
        	}
    };
}


#endif // __eosPoolAllocator__


