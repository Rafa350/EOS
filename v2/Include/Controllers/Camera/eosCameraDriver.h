#ifndef __eosCameraDriver__
#define __eosCameraDriver__


#include "eos.h"


namespace eos {
   
    class ICameraDriver {
        public:
            virtual ~ICameraDriver() {}
            
            virtual void initialize() = 0;
            virtual void shutdown() = 0;
    };
    
}


#endif // __eosCameraDriver__