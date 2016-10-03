#ifndef __EOS_HEAPALLOCATOR_HPP
#define	__EOS_HEAPALLOCATOR_HPP


#include "eos.hpp"
#include "eosAllocator.hpp"


namespace eos {
    
    class HeapAllocator: public IAllocator {
        public:
            void *allocate(size_t size);
            void deallocate(void *p);
    };
}


#endif

