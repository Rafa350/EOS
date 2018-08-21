#ifndef __eosAllocator__
#define	__eosAllocator__


// EOS includes
//
#include "eos.h"

// Standard includes
//
#include "stddef.h"


namespace eos {

    class IAllocator {
        public:
    		virtual ~IAllocator() {}
            virtual void *allocate(size_t size) = 0;
            virtual void deallocate(void *p) = 0;
    };

}


#endif // __eosAllocator__

