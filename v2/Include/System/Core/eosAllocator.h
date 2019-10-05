#ifndef __eosAllocator__
#define	__eosAllocator__


// EOS includes
//
#include "eos.h"


namespace eos {

    class IAllocator {
        public:
    		virtual ~IAllocator() = default;
            virtual void *allocate(int size) = 0;
            virtual void deallocate(void *p) = 0;
    };

}


#endif // __eosAllocator__

