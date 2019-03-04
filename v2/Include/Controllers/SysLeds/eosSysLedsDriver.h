#ifndef __eosSysLedsDriver__
#define __eosSysLedsDriver__


#include "eos.h"


namespace eos {
    
    class SysLedsDriver {
        public:
            void LedOn(int numLed);
            void LedOff(int numLed);
            int getNumLeds() const;
    }
    
}


#endif