#ifndef __eosFsmService__
#define	__eosFsmService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosQueue.h"


namespace eos {

    class Application;
	class StateMachine;

    typedef unsigned Event;

    class FsmService final: private Service {
        public:
			struct EventArgs {
			};

        private:
			typedef ICallbackP1<const EventArgs&> IEventCallback;
            typedef Queue<Event> EventQueue;

        private:
            StateMachine* sm;
            EventQueue eventQueue;
            IEventCallback* eventCallback;
            IEventCallback* actionCallback;

        private:
            void processEvent(Event event);

        protected:
            void onTask() override;
            //void onTick() override;

        public:
            FsmService(Application* application, StateMachine* sm);
            bool acceptEvent(Event event, unsigned timeout);
            inline void setEventCallback(IEventCallback* callback) { eventCallback = callback; }
            inline void setActionCallback(IEventCallback* callback) { actionCallback = callback; }
    };

}


#endif	// __eosFsmService__
