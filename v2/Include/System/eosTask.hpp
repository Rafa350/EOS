#ifndef __EOS_TASK_HPP
#define	__EOS_TASK_HPP


#include "eos.hpp"


namespace eos {
    
    class Task {
        public:
            Task(unsigned stackSize, unsigned priority);
            virtual ~Task();
            static void delay(unsigned time);
            static void delayUntil(unsigned time, unsigned *lastTick);
            static unsigned getTickCount();
            static void enterCriticalSection();
            static void exitCriticalSection();
            static void suspendAllThreads();
            static void resumeAllThreads();
        protected:
            virtual void run() = 0;
        private:     
            void *handle;
            static void function(void *params);
    };    
}


#endif
