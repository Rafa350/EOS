#ifndef __eosFsmService__
#define	__eosFsmService__


#include "eos.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosStack.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTask.h"


namespace eos {
    
	typedef unsigned Event;
	
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
	
    class StateMachineService: private IRunable {
        private:
			struct EventArgs {
			};
			typedef ICallbackP1<const EventArgs&> IServiceEventCallback;
            typedef Queue<fsm::Event> EventQueue;

        private:
            fsm::StateMachine* sm;
            EventQueue eventQueue;
            IServiceEventCallback* eventCallback;
            IServiceEventCallback* actionCallback;

        public:
            StateMachineService(fsm::StateMachine *sm);
            bool acceptEvent(fsm::Event event, unsigned timeout);
            inline void setEventCallback(IServiceEventCallback* callback) { eventCallback = callback; }
            inline void setActionCallback(IServiceEventCallback* callback) { actionCallback = callback; }
        private:
            void run();
            void processEvent(fsm::Event event);
    };
   
}


#endif	// __eosFsmService__
