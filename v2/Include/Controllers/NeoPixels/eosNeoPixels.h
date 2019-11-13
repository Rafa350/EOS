#ifndef __eosNeoPixels__
#define __eosNeoPixels__


#include "eos.h"


namespace eos {
    
    class NeoPixels {
        public:
            struct Configuration {
                int t0Lo;
                int t0Hi;
                int t1Lo;
                int t1Hi;
                uint32_t *pixBuffer;
                int pixLength;
            };
            
        public:
            NeoPixels(const Configuration *configuration);
    };
}


#endif // __eosNeoPixels__