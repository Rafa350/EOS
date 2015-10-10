#ifndef __FSM_STATES_HPP
#define __FSM_STATES_HPP


#include "Services/eosFSM.hpp"


class InitialPauseState: public eos::fsm::State {
    private:
        eos::fsm::StateMachine *sm;
        eos::fsm::IController *ctl;
    public:
        InitialPauseState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmUpState: public eos::fsm::State {
    private:
        eos::fsm::StateMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ArmUpState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class FinalPauseState: public eos::fsm::State {
    private:
        eos::fsm::StateMachine *sm;
        eos::fsm::IController *ctl;
    public:
        FinalPauseState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ErrorState: public eos::fsm::State {
    private:
        eos::fsm::StateMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ErrorState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl);
        eos::fsm::State *transition(eos::fsm::Event event);
};

class StopState: public eos::fsm::State {
    private:
        eos::fsm::StateMachine *sm;
        eos::fsm::IController *ctl;
    public:
        StopState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl);
        eos::fsm::State *transition(eos::fsm::Event event);
};



#endif
