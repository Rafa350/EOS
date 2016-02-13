#ifndef __EOS_SYSTEM_CORE_SEMAPHORE_HPP
#define	__EOS_SYSTEM_CORE_SEMAPHORE_HPP


#include "eos.hpp"


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

