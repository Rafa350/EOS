#ifndef __eosPoolAllocator__
#define	__eosPoolAllocator__


#include "eos.h"
#include "System/Core/eosAllocator.h"

#include <stddef.h>
#include <stdint.h>


namespace eos {

    class GenericPoolAllocator: public IAllocator {
        private:
            uint8_t *blocks;
            uint8_t *nextBlock;
            int blockSize;
            int maxBlocks;
            int freeBlocks;
            int initializedBlocks;

        public:
            GenericPoolAllocator(int blockSize, int maxBlocks);
            virtual ~GenericPoolAllocator();

            void *allocate(int size) override;
            void deallocate(void *p) override;

            inline int getBlockSize() const { return blockSize; }
            inline int getUsedBlocks() const { return maxBlocks - freeBlocks; }
            inline int getFreeBlocks() const { return freeBlocks; }

        private:
            uint8_t *addrFromIndex(int i) const;
            int indexFromAddr(const uint8_t *p) const;
    };

    template <class T>
    class PoolAllocator: public GenericPoolAllocator {
        public:
            PoolAllocator(int maxBlocks):
            	GenericPoolAllocator(sizeof(T), maxBlocks) {
            }
            T *allocate(int size) {
            	return (T*) GenericPoolAllocator::allocate(size);
            }
            void deallocate(T *p) {
            	GenericPoolAllocator::deallocate(p);
            }
    };
}


#endif // __eosPoolAllocator__


