#ifndef __EOS_FSM_HPP
#define	__EOS_FSM_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
#endif

#ifndef __EOS_CALLBACKS_HPP
#include "System/Core/eosCallbacks.hpp"
#endif

#ifndef __EOS_TASK_HPP
#include "System/Core/eosTask.hpp"
#endif

#ifndef __EOS_QUEUE_HPP
#include "System/Collections/eosQueue.hpp"
#endif

#ifndef __EOS_STACK_HPP
#include "System/Collections/eosStack.hpp"
#endif


#define EV_Fsm_onEvent(cls, instance, method) \
    new eos::CallbackP1<cls, eos::StateMachine*>(instance, method)
#define EV_Fsm_onAction(cls, instance, method) \
    new eos::CallbackP1<cls, eos::StateMachine*>(instance, method)


namespace eos {
    
    namespace fsm {
        
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
                StateMachine *sm;
            public:
                State(StateMachine *sm);
                virtual void enterAction();
                virtual void exitAction();
                virtual void transition(Event event);
            protected:
                StateMachine *getStateMachine() const { return sm; }
                void setState(State *state);
                void pushState(State *state);
                void popState();
        };

        class StateMachine {
            private:
                IContext *context;
                Stack<State*> states;
            public:
                StateMachine(IContext *context);
                ~StateMachine();
                void start(State *initialState);
                void acceptEvent(Event event);
                void setState(State *state);
                void pushState(State *state);
                void popState();
                IContext *getContext() const { return context; }
        };
        
    }

    class StateMachineService;
    typedef ICallbackP1<StateMachineService*> IStateMachineServiceEvent;

    class StateMachineService: private IRunable {

        private:
            typedef Queue<fsm::Event> EventQueue;

        private:
            fsm::StateMachine *sm;
            EventQueue eventQueue;
            IStateMachineServiceEvent *onEvent;
            IStateMachineServiceEvent *onAction;

        public:
            StateMachineService(fsm::StateMachine *sm);
            bool acceptEvent(fsm::Event event, unsigned timeout);
            inline void setOnEvent(IStateMachineServiceEvent *event) { onEvent = event; }
            inline void setOnAction(IStateMachineServiceEvent *event) { onAction = event; }
        private:
            void run();
            void processEvent(fsm::Event event);
    };
   
}


#endif	
