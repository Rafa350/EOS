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

            uint8_t* getAddr() const;
            unsigned getSize() const;
    };

    template <class T>
    class HeapAllocator {

        private:
            MemoryHeapAllocator _allocator;

        public:

            inline T *allocate(unsigned size) {
                return static_cast<T*>(_allocator.allocate(size));
            }

            inline void deallocate(T *p) {
                _allocator.deallocate(p);
            }
    };

}


#endif // __eosHeapAllocator__

