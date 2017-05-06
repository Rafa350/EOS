#ifndef __EOS_SEMAPHORE_H
#define	__EOS_SEMAPHORE_H


#include "eos.h"


namespace eos {

    class BinarySemaphore {
        private:
            void *handle;
            
        public:
            BinarySemaphore();
            ~BinarySemaphore();
            bool take(unsigned blockTime);
            bool give();
            void giveISR();
    };
}


#endif

