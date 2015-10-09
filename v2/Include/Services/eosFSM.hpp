#ifndef __EOS_FSM_HPP
#define	__EOS_FSM_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosQueue.hpp"


namespace eos {

    typedef unsigned Event;
    
    class IStateMachine {
        public:
            void processEvent(Event event);
    };
    
    class StateMachineService: public IRunable {

        private:
            typedef Queue<Event> EventQueue;
        
        private:
            IStateMachine *sm;
            EventQueue internalEventQueue;
            EventQueue externalEventQueue;
        
        public:
            StateMachineService(IStateMachine *sm);
            ~StateMachineService();
            ExternalEvent(Event event);
        private:
            void run();
            void processEvent(Event event);
            void InternalEvent(Event event);
    };
    
}


#endif	
