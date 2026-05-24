#pragma once
#ifndef __eosSemaphore__
#define	__eosSemaphore__


// EOS includes
//
#include "eos.h"
#include "RTOS/rtosMiliseconds.h"
#include "RTOS/rtosSemaphore.h"


namespace eos {

    class Semaphore {
        private:
    		rtos::Semaphore _semaphore;

        public:
            inline bool wait(uint32_t blockTime) const {
            	return _semaphore.wait(rtos::Miliseconds(blockTime));
            }

            inline void release() const {
            	_semaphore.release();
            }

            inline void releaseISR() const {
            	_semaphore.releaseISR();
            }
    };
}


#endif // __eosSemaphore__
