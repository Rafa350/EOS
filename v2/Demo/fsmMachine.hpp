#ifndef __FSM_MACHINE_HPP
#define __FSM_MACHINE_HPP


#include "Services/eosFSM.hpp"


class MyMachine: eos:fsm:StateMachine {
    private:
        eos::fsm::State *stateLoopSW1;
        eos::fsm::State *stateLoopSW2;
        eos::fsm::State *stateLoopSW3;
    public:
        MyMachine(eos::fsm::IContext *context);
        eos::fsm::State *getLoopSW1State() const { return stateLoopSW1; }
        eos::fsm::State *getLoopSW2State() const { return stateLoopSW2; }
        eos::fsm::State *getLoopSW3State() const { return stateLoopSW3; }
    }


#endif
