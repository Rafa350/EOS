#ifndef __EOS_SEMAPHORE_HPP
#define	__EOS_SEMAPHORE_HPP


#include "eos.hpp"


namespace eos {

    class BinarySemaphore {
        private:
            void *handle;

        public:
            BinarySemaphore();
            ~BinarySemaphore();
            bool take(unsigned timeout);
            bool give();
            void giveISR();
    };
}

#endif
