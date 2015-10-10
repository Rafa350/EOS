#ifndef __FSM_MACHINE_HPP
#define __FSM_MACHINE_HPP


#include "Services/eosFSM.hpp"


class MyMachine: public eos::fsm::StateMachine {
    public:
        eos::fsm::State *InitialPauseState;
        eos::fsm::State *ArmUpState;
        eos::fsm::State *FinalPauseState;
        eos::fsm::State *ErrorState;
        eos::fsm::State *StopState;
};


#endif
