#ifndef __FSM_STATES_HPP
#define __FSM_STATES_HPP


#include "Services/eosFSM.hpp"


class LoopSW1State: public eos::fsm::State {
    public:
        void enterAction();
        void transition(eos::fsm::Event event);
};

class LoopSW2State: public eos::fsm::State {
    public:
        void enterAction();
        void transition(eos::fsm::Event event);
};

class LoopSW3State: public eos::fsm::State {
    public:
        void enterAction();
        void transition(eos::fsm::Event event);
};



#endif
