#ifndef __eosHeapAllocator__
#define	__eosHeapAllocator__


// EOS includes
//
#include "eos.h"


namespace eos {

    class MemoryHeapAllocator {
        public:
    		MemoryHeapAllocator(unsigned size);
    		~MemoryHeapAllocator();

            void* allocate(unsigned size);
            void deallocate(void *p);

            void* getAddr() const;
            unsigned getSize() const;
    };

    template <typename T, unsigned SIZE>
    class HeapAllocator {
        private:
            MemoryHeapAllocator _allocator;

        public:
            HeapAllocator() :
            	_allocator(SIZE) {}

            inline T *allocate() {
                return static_cast<T*>(_allocator.allocate(sizeof(T)));
            }

            inline void deallocate(T *p) {
                _allocator.deallocate(p);
            }
    };

}


#endif // __eosHeapAllocator__

