#ifndef __eosTask__
#define	__eosTask__


// EOS includes
//
#include "eos.h"
#include "OSAL/osalTask.h"
#include "System/eosCallbacks.h"


namespace eos {

	class String;

    /// \brief Clase que implementa una tasca.
    ///
    class Task {
        public:
            struct EventArgs {
                Task* task;
                void* param;
            };

        private:
            typedef ICallbackP1<const EventArgs&> IEventCallback;

        public:
            enum class Priority {
                idle,
                low,
                normal,
                high
            };

            Task(int stackSize, Priority priority, const String& name, IEventCallback* eventCallback, void* eventParam);
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

        private:
            HTask hTask;
            IEventCallback* eventCallback;
            void* eventParam;
            unsigned weakTime;

            static void function(void* params);
    };

}


#endif // __eosTask__
