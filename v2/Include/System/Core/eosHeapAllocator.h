#pragma once
#ifndef __eosHeapAllocator__
#define	__eosHeapAllocator__


// EOS includes
//
#include "eos.h"


namespace eos {

    class MemoryHeapAllocator {
        public:
            void * allocate(uint32_t size);
            void deallocate(void *ptr);
    };

    template <typename T_, int size_>
    class HeapAllocator {
        private:
            MemoryHeapAllocator _allocator;

        public:
            HeapAllocator() :
            	_allocator(size_) {}

            inline T_* allocate() {
                return static_cast<T_*>(_allocator.allocate(sizeof(T_)));
            }

            inline void deallocate(T_* ptr) {
                _allocator.deallocate(ptr);
            }
    };

}


#endif // __eosHeapAllocator__

