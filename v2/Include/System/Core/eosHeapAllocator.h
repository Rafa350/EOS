#ifndef __EOS_HEAPALLOCATOR_H
#define	__EOS_HEAPALLOCATOR_H


#include "eos.h"
#include "System/Core/eosAllocator.h"


namespace eos {
    
    class HeapAllocator: public IAllocator {
        public:
            void *allocate(size_t size);
            void deallocate(void *p);
    };
}


#endif

