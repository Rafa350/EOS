#ifndef __eosHeapAllocator__
#define	__eosHeapAllocator__


// EOS includes
//
#include "eos.h"


namespace eos {

    class MemoryHeapAllocator {
        public:
            void* allocate(unsigned size);
            void deallocate(void *p);
    };

    template <class T>
    class HeapAllocator {

        private:
            MemoryHeapAllocator allocator;

        public:

            inline T *allocate(unsigned size) {
                return static_cast<T*>(allocator.allocate(size));
            }

            inline void deallocate(T *p) {
                allocator.deallocate(p);
            }
    };

}


#endif // __eosHeapAllocator__

