#pragma once
#ifndef __eosTask__
#define	__eosTask__


// EOS includes
//
#include "eos.h"
#include "OSAL/osalTask.h"
#include "System/eosCallbacks.h"


namespace eos {

	class Task;

    struct TaskCallbackArgs {
        Task *task;
        void *params;
    };
    using ITaskCallback = ICallbackP1<const TaskCallbackArgs&>;
    template <typename Instance_> using TaskCallback = CallbackP1<Instance_, const TaskCallbackArgs&>;


    /// \brief Clase que implementa una tasca.
    ///
    class Task {
        public:
            enum class Priority {
                idle,
                low,
                normal,
                high
            };

            struct Info {
            	char * const name;
            	Priority proirity;
            };

            Task(unsigned stackSize, Priority priority, const char *name, ITaskCallback *taskCallback, void *taskParams);
            virtual ~Task();

            void delay(unsigned time);
            void delay(unsigned time, unsigned& weakTime);
            static void enterCriticalSection();
            static void exitCriticalSection();
            static bool waitNotification(unsigned blockTime);
            static bool raiseNotification(unsigned blockTime);
            static void raiseNotificationISR();
            static void yield();
            static void yieldISR();
            void getTaskInfo(Info &info) const;

        private:
            HTask _hTask;
            ITaskCallback *_taskCallback;
            void *_taskParams;
            unsigned _weakTime;

            static void function(void *params);
    };

}


#endif // __eosTask__
