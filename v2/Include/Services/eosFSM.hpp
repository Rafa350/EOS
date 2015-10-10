#ifndef __EOS_FSM_HPP
#define	__EOS_FSM_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosQueue.hpp"


namespace eos {
    
    namespace fsm {
        
        typedef unsigned Event;
        
        class StateMachine;
        
        class IController {
            public:
                virtual void outSet(unsigned out) = 0;
                virtual void outClear(unsigned out) = 0;
                virtual void outToggle(unsigned out) = 0;
                virtual void outPulse(unsigned out) = 0;
                virtual void timStart(unsigned tim, unsigned timeout) = 0;
        };
        
        class State {
            public:
                virtual void enterAction();
                virtual void exitAction();
                virtual State* transition(Event event);
        };

        class StateMachine {
            private:
                State* initialState;
                State* state;
            public:
                StateMachine();
                ~StateMachine();
                void start();
                void acceptEvent(Event event);
        };
        
    }

    class StateMachineService: public IRunable {

        private:
            typedef Queue<fsm::Event> EventQueue;

        private:
            fsm::StateMachine *sm;
            EventQueue eventQueue;

        public:
            StateMachineService(fsm::StateMachine *sm);
            bool acceptEvent(fsm::Event event, unsigned timeout);
        private:
            void run();
            void processEvent(fsm::Event event);
    };
   
}


#endif	
