#ifndef __eosSemaphore__
#define	__eosSemaphore__


// EOS includes
//
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
