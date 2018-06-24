#ifndef __eosTask__
#define	__eosTask__


#include "eos.h"
#include "osal/osalTask.h"


namespace eos {


    class Task;

    /// \brief Interficie que cal que implementin les clases que poden
    ///        ser procesades dins d'una tasca.
    ///
    class IRunable {
        public:
    		virtual ~IRunable() {}
            virtual void run(Task *task) = 0;
    };

    enum class TaskPriority {
        idle = OSAL_TASK_PRIORITY_IDLE,
        low = OSAL_TASK_PRIORITY_LOW,
        normal = OSAL_TASK_PRIORITY_NORMAL,
        high = OSAL_TASK_PRIORITY_HIGH
    };

    /// \brief Clase que implementa una tasca.
    ///
    class Task {
        private:
            HTask hTask;
            IRunable *runable;
            unsigned weakTime;

        public:
            Task(unsigned stackSize, TaskPriority priority, const char *name, IRunable *runable);
            virtual ~Task();

            static void delay(unsigned time);
            static void delay(unsigned time, unsigned &weakTime);
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


#endif // __eosTask__
