#ifndef __eosContainer__
#define __eosContainer__


#include "eos.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif            
    
            namespace Container {
                void* alloc(unsigned capacity, unsigned elementSize);
                void free(void* container);
                void* resize(void* container, unsigned oldCapacity, unsigned newCapacity, unsigned count, unsigned elementSize);
            }
    
#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosContainer__
