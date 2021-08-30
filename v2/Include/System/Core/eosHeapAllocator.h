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

    template <typename T_, int size_>
    class HeapAllocator {
        private:
            MemoryHeapAllocator _allocator;

        public:
            HeapAllocator() :
            	_allocator(size_) {}

            inline T_* allocate() {
                void* p = _allocator.allocate(sizeof(T_));
                eosAssert(p != nullptr);
                return static_cast<T_*>(p);
            }

            inline void deallocate(T_* p) {
            	eosAssert(p != nullptr);
                _allocator.deallocate(p);
            }
    };

}


#endif // __eosHeapAllocator__

