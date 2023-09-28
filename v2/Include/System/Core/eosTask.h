#ifndef __eosTask__
#define	__eosTask__


// EOS includes
//
#include "eos.h"
#include "OSAL/osalTask.h"
#include "System/eosCallbacks.h"


namespace eos {

    /// \brief Clase que implementa una tasca.
    ///
    class Task {
        public:
            struct EventArgs {
                Task *task;
                void *params;
            };

            typedef ICallbackP1<const EventArgs&> IEventCallback;

        public:
            enum class Priority {
                idle,
                low,
                normal,
                high
            };

            Task(unsigned stackSize, Priority priority, const char *name, IEventCallback *eventCallback, void *eventParams);
            virtual ~Task();

            static void delay(unsigned time);
            static void delay(unsigned time, unsigned& weakTime);
            static unsigned getTickCount();
            static void enterCriticalSection();
            static void exitCriticalSection();
            static void startAll();
            static void suspendAll();
            static void resumeAll();
            static bool notificationTake(unsigned blockTime);
            static bool notificationGive();
            static void notificationGiveISR();
            static void yield();
            static void yieldISR();

        private:
            HTask _hTask;
            IEventCallback *_eventCallback;
            void *_eventParams;
            unsigned _weakTime;

            static void function(void *params);
    };

}


#endif // __eosTask__
