#ifndef __EOS_ALLOCATOR_HPP
#define	__EOS_ALLOCATOR_HPP


#include "eos.hpp"


namespace eos {
    
    class IAllocator {
        public:
            virtual void *allocate(size_t size) = 0;
            virtual void deallocate(void *p) = 0;
    };
    
}


#endif

