#pragma once


#include "eos.h"


namespace rtos {

	class Miliseconds;

	class Semaphore final {
        private:
			void * const _handler;

        public:
            Semaphore();
            ~Semaphore();

            bool wait(Miliseconds blockTime) const;
            void release() const;
            void releaseISR() const;
	};
}
