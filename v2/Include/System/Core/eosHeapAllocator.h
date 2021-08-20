#ifndef __eosHeapAllocator__
#define	__eosHeapAllocator__


// EOS includes
//
#include "eos.h"


namespace eos {

    class MemoryHeapAllocator {
        public:
    		MemoryHeapAllocator(int size);
    		~MemoryHeapAllocator();

            void* allocate(int size);
            void deallocate(void* p);

            void* getAddr() const;
            int getSize() const;
    };

    template <typename T, int size>
    class HeapAllocator {
        private:
            MemoryHeapAllocator _allocator;

        public:
            HeapAllocator() :
            	_allocator(size) {}

            inline T* allocate() {
                void* p = _allocator.allocate(sizeof(T));
                eosAssert(p != nullptr);
                return static_cast<T*>(p);
            }

            inline void deallocate(T* p) {
            	eosAssert(p != nullptr);
                _allocator.deallocate(p);
            }
    };

}


#endif // __eosHeapAllocator__

