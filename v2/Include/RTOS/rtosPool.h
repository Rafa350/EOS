#pragma once


#include "eos.h"


namespace rtos {

    class Pool {
        private:
            uint8_t *_blocks;
            uint8_t *_nextBlock;
            uint32_t _blockSize;
            uint32_t _maxBlocks;
            uint32_t _freeBlocks;
            uint32_t _initializedBlocks;

        public:
            Pool(uint32_t blockSize, uint32_t maxBlocks);
            ~Pool();

            void* allocate();
            void deallocate(void* ptr);

            inline void* getStoragePtr() const {
            	return _blocks;
            }

            inline uint32_t getStorageSize() const {
            	return _blockSize * _maxBlocks;
            }

            inline uint32_t getBlockSize() const {
            	return _blockSize;
            }

            inline uint32_t getUsedBlocks() const {
            	return _maxBlocks - _freeBlocks;
            }

            inline uint32_t getFreeBlocks() const {
            	return _freeBlocks;
            }

        private:
            uint8_t* addrFromIndex(uint32_t idx) const;
            uint32_t indexFromAddr(const uint8_t* ptr) const;
    };

/*
    /// \brief Pool de memoria
    ///
    template <typename T_, int maxBlocks_>
    class PoolAllocator {

    	private:
    		Pool _pool;

    	public:
    		PoolAllocator():
            	_pool(sizeof(T_), maxBlocks_) {
            }

    		inline T_* allocate() {
            	return static_cast<T_*>(_pool.allocate());
            }

    		inline void deallocate(T_* ptr) {
            	_pool.deallocate(ptr);
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

        		auto &allocator = Allocator::instance();
        		return allocator.allocate();
        	}

        	void operator delete(void *p) {

        		eosAssert(p != nullptr);

        		auto &allocator = Allocator::instance();
        		allocator.deallocate(static_cast<T_*>(p));
        	}
    };

    */
}

