#ifndef __EOS_ALLOCATOR_H
#define	__EOS_ALLOCATOR_H


#include "eos.h"

#include <stddef.h>


namespace eos {
    
    class IAllocator {
        public:
            virtual void *allocate(size_t size) = 0;
            virtual void deallocate(void *p) = 0;
    };
    
}


#endif

