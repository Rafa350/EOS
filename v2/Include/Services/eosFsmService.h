#ifndef __eosFsmService__
#define	__eosFsmService__


#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosStack.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTask.h"


namespace eos {
    
	typedef unsigned Event;
	
    class Application;
	class StateMachine;
	
	class IContext {
		public:
			virtual bool inpGet(unsigned inp) = 0;
			virtual void outSet(unsigned out) = 0;
			virtual void outClear(unsigned out) = 0;
			virtual void outToggle(unsigned out) = 0;
			virtual void outPulse(unsigned out, unsigned timeout) = 0;
			virtual void timStart(unsigned tim, unsigned timeout) = 0;
			virtual unsigned varGet(unsigned var) = 0;
	};
	
	class State {
		private:
			StateMachine* sm;
		public:
			State(StateMachine* sm);
			virtual void enterAction();
			virtual void exitAction();
			virtual void transition(Event event);
		protected:
			inline StateMachine* getStateMachine() const { return sm; }
			void setState(State* state);
			void pushState(State* state);
			void popState();
	};

	class StateMachine {
		private:
			IContext* context;
			Stack<State*> states;
		public:
			StateMachine(IContext* context);
			~StateMachine();
			void start(State* initialState);
			void acceptEvent(Event event);
			void setState(State* state);
			void pushState(State* state);
			void popState();
			IContext* getContext() const { return context; }
	};
	
    class FsmService final: private Service {
        private:
			struct EventArgs {
			};
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
