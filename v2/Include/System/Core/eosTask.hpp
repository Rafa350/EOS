#ifndef __EOS_SYSTEM_CORE_TASK_HPP
#define	__EOS_SYSTEM_CORE_TASK_HPP


#include "eos.hpp"


namespace eos {
    
    class IRunable {
        public:
            virtual void run() = 0;
    };
    
    enum class TaskPriority {
        idle = 0,
        low = 1,
        normal = 2,
        high = 3
    };
    
    class Task {
        private:
            void *handle;
            IRunable *runable;

        public:
            Task(unsigned stackSize, TaskPriority priority, IRunable *runable);
            virtual ~Task();
            static void delay(unsigned time);
            static void delayUntil(unsigned time, unsigned *lastTick);
            static unsigned getTickCount();
            static void enterCriticalSection();
            static void exitCriticalSection();
            static void suspendAllThreads();
            static void resumeAllThreads();
        private:     
            static void function(void *params);
    };    
}


#endif
