#pragma once
#ifndef __rtosSemaphore__
#define __rtosSemaphore__


#include "eos.h"


namespace eos {

	class Time;
}


namespace rtos {

	class Semaphore final {
        private:
			void * const _handler;

        public:
            Semaphore();
            ~Semaphore();

            bool wait(eos::Time blockTime) const;
            void release() const;
            void releaseISR() const;
	};
}


#endif // __rtosSemaphore__
