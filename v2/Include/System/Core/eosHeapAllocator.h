#ifndef __eosHeapAllocator__
#define	__eosHeapAllocator__


// EOS includes
//
#include "eos.h"
#include "System/Core/eosAllocator.h"


namespace eos {

    class HeapAllocator: public IAllocator {
        public:
            void *allocate(int size);
            void deallocate(void *p);
    };
}


#endif // __eosHeapAllocator__

