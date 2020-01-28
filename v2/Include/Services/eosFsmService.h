#ifndef __eosFsmService__
#define	__eosFsmService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"


namespace eos {

    class Application;
    class StateMachine;
    
    typedef unsigned Message;

    class FsmService final: private Service {
        public:
            enum class EventType {
                acceptMessage
            };
			struct EventArgs {
                EventType type;
                FsmService* service;                
			};

        private:
			typedef ICallbackP1<const EventArgs&> IEventCallback;

        private:
            StateMachine* sm;
            IEventCallback* eventCallback;

        protected:
            void onTask() override;

        public:
            FsmService(Application* application, StateMachine* sm);
            inline void setEventCallback(IEventCallback* callback) { eventCallback = callback; }
    };
    
    
    class StateMachine {
        public:
            virtual void task() = 0;
    };

}


#endif	// __eosFsmService__
