#ifndef __eosHeapAllocator__
#define	__eosHeapAllocator__


// EOS includes
//
#include "eos.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Core {
#endif

            class MemoryHeapAllocator {
                public:
                    void *allocate(int size);
                    void deallocate(void *p);
            };

            template <class T>
            class HeapAllocator {

                private:
                    MemoryHeapAllocator allocator;

                public:

                    inline T *allocate(int size) {
                        return static_cast<T*>(allocator.allocate(size));
                    }

                    inline void deallocate(T *p) {
                        allocator.deallocate(p);
                    }
            };

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosHeapAllocator__

