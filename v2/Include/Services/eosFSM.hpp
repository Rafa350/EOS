#ifndef __EOS_FSM_HPP
#define	__EOS_FSM_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosQueue.hpp"


namespace eos {

    typedef unsigned Event;
    
    class StateBase {
        public:
            virtual void enterAction();
            virtual void exitAction();
            virtual StateBase *transition(Event event);
    };
    
    class StateMachine {
        private:
            StateBase *initialState;
            StateBase *state;
        public:
            StateMachine();
            void acceptEvent(Event event);
    };
    
    class StateMachineService: public IRunable {

        private:
            typedef Queue<Event> EventQueue;
        
        private:
            StateMachine *sm;
            EventQueue eventQueue;
        
        public:
            StateMachineService(StateMachine *sm);
            bool acceptEvent(Event event, unsigned timeout);
        private:
            void run();
            void processEvent(Event event);
    };
    
}


#endif	
