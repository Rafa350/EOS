#ifndef __eosTimer__
#define	__eosTimer__


// EOS includes
//
#include "eos.h"
#include "osal/osalTimer.h"
#include "System/eosCallbacks.h"


namespace eos {

    class Timer {
        public:
            struct EventArgs {
                Timer* timer;
                void* param;
            };

        private:
            typedef ICallbackP1<const EventArgs&> IEventCallback;

        private:
            HTimer hTimer;
            bool autoreload;
            void *tag;
            IEventCallback *eventCallback;
            void* eventParam;

        public:
            Timer(bool autoreload = false);
            Timer(bool autoreload, IEventCallback* eventCallback, void* eventParam);
            ~Timer();
            void start(unsigned time, unsigned blockTime);
            void stop(unsigned blockTime);

            inline void setEventCallback(IEventCallback* callback) {  eventCallback = callback; }

            inline void setTag(void* tag) { this->tag = tag; }
            inline void* getTag() const { return tag; }
            bool isActive() const;

        private:
            static void timerFunction(HTimer hTimer);
    };

}


#endif

