#ifndef __eosDCMICameraDriver__
#define __eosDCMICameraDriver__


#include "eos.h"
#include "Controllers/Camera/eosCameraDriver.h"


namespace eos {
    
    class DCMICameraDriver: public ICameraDriver {
        public:
            void initialize();
            void shutdown();
    };
    
}


#endif // __eosDCMICameraDriver__
