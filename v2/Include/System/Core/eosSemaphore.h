#ifndef __eosSemaphore__
#define	__eosSemaphore__


// EOS includes
//
#include "eos.h"
#include "OSAL/osalSemaphore.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Core {
#endif

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

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosSemaphore__
