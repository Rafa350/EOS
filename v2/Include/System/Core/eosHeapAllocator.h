#ifndef __eosHeapAllocator__
#define	__eosHeapAllocator__


// EOS includes
//
#include "eos.h"
#include "System/Core/eosAllocator.h"

// Standard includes
//
#include "stddef.h"


namespace eos {

    class HeapAllocator: public IAllocator {
        public:
            void *allocate(size_t size);
            void deallocate(void *p);
    };
}


#endif // __eosHeapAllocator__

