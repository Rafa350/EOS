#pragma once
#ifndef __rtosSemaphore__
#define __rtosSemaphore__


#include "eos.h"


namespace rtos {

	class Time;

	class Semaphore final {
        private:
			void * const _handler;

        public:
            Semaphore();
            ~Semaphore();

            bool wait(Time blockTime) const;
            void release() const;
            void releaseISR() const;
	};
}


#endif // __rtosSemaphore__
