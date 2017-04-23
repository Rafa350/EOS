#ifndef __EOS_TASK_H
#define	__EOS_TASK_H


#include "eos.h"


namespace eos {
    
    
    class Task;
    
    /// \brief Interficie que cal que implementin les clases que poden
    ///        ser procesades dins d'una tasca.
    ///
    class IRunable {
        public:
            virtual void run(Task *task) = 0;
    };
    
    enum class TaskPriority {
        idle = 0,
        low = 1,
        normal = 2,
        high = 3
    };
    
    /// \brief Clase que implementa una tasca.
    ///
    class Task {
        private:
            void *handle;
            IRunable *runable;

        public:
            Task(unsigned stackSize, TaskPriority priority, const char *name, IRunable *runable);
            virtual ~Task();
            static void delay(unsigned time);
            static void delayUntil(unsigned time, unsigned *lastTick);
            static unsigned getTickCount();
            static void enterCriticalSection();
            static void exitCriticalSection();
            static void startAll();
            static void suspendAll();
            static void resumeAll();
            static bool notificationTake(unsigned blockTime);
            static bool notificationGive();
            static void notificationGiveISR();
        private:     
            static void function(void *params);
    };    
}


#endif
