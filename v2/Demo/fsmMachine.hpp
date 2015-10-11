#ifndef __FSM_MACHINE_HPP
#define __FSM_MACHINE_HPP


#include "Services/eosFSM.hpp"


class MyMachine: public eos::fsm::StateMachine {
    private:
        eos::fsm::State *stateInitialPause;
        eos::fsm::State *stateArmUp;
        eos::fsm::State *stateFinalPause;
        eos::fsm::State *stateError;
        eos::fsm::State *stateStop;
    public:
        MyMachine(eos::fsm::IController *ctl);
        eos::fsm::State *getInitialPauseState() const { return stateInitialPause; }
        eos::fsm::State *getArmUpState() const { return stateArmUp; }
        eos::fsm::State *getFinalPauseState() const { return stateFinalPause; }
        eos::fsm::State *getErrorState() const { return stateError; }
        eos::fsm::State *getStopState() const { return stateStop; }
};


#endif
