#ifndef __eosSemaphore__
#define	__eosSemaphore__


// EOS includes
//
#include "eos.h"
#include "OSAL/osalSemaphore.h"


namespace eos {

    class Semaphore {
        private:
            HSemaphore hSemaphore;
            
        public:
            Semaphore();
            Semaphore(unsigned count);
            ~Semaphore();
            
            bool wait(unsigned blockTime) const;
            void release() const;
            void releaseISR() const;
    };
}


#endif // __eosSemaphore__
