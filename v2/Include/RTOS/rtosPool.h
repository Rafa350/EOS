#pragma once
#ifndef __rtosPool__
#define __rtosPool__


#include "eos.h"


namespace rtos {

    class Pool final {
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

            uint32_t getAllocatedSize();
			uint32_t getAvailableSize();

        private:
            uint8_t* addrFromIndex(uint32_t idx) const;
            uint32_t indexFromAddr(const uint8_t* ptr) const;
    };

}


#endif // __rtosPool__
