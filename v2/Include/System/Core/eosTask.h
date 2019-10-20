#ifndef __eosTask__
#define	__eosTask__


// EOS includes
//
#include "eos.h"
#include "osal/osalTask.h"


namespace eos {

	class String;
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
            int weakTime;

        private:
            static void function(void *params);

        public:
            Task(unsigned stackSize, TaskPriority priority, const String &name, IRunable *runable);
            virtual ~Task();

            static void delay(int time);
            static void delay(int time, int &weakTime);
            static unsigned getTickCount();
            static void enterCriticalSection();
            static void exitCriticalSection();
            static void startAll();
            static void suspendAll();
            static void resumeAll();
            static bool notificationTake(int blockTime);
            static bool notificationGive();
            static void notificationGiveISR();
    };
}


#endif // __eosTask__
