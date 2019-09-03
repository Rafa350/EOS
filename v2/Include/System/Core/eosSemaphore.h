#ifndef __eosSemaphore__
#define	__eosSemaphore__


#include "eos.h"
#include "OSAL/osalSemaphore.h"


namespace eos {

    class BinarySemaphore {
        private:
            HSemaphore hSemaphore;
            
        public:
            BinarySemaphore();
            ~BinarySemaphore();
            bool wait(unsigned blockTime);
            void release();
            void releaseISR();
    };
}


#endif // __eosSemaphore__
