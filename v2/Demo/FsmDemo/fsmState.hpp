#ifndef __FSM_STATES_HPP
#define __FSM_STATES_HPP


#include "Services/Fsm/eosFSM.hpp"


class WaitTriggerStartState: public State {
    public:
        WaitTriggerStartState(eos::fsm::StateMachine *sm);
        void transition(eos::fsm::Event event);
};

class WaitTriggerDelayState: public State {
    public:
        WaitTriggerDelayState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmUpStartState: public State {
    public:
        ArmUpStartState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmUpMoveState: public State {
    public:
        ArmUpMoveState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmUpEndState: public State {
    public:
        ArmUpEndState(eos::fsm::StateMachine *sm);
        void enterAction();
        void ExitAction();
        void transition(eos::fsm::Event event);
};

class ArmDownStartState: public State {
    public:
        ArmDownStartState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmDownEndState: public State {
    public:
        ArmDownEndState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class PrintLabelStartState: public State {
    public:
        PrintLabelStartState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class PrintLabelPrintState: public State {
    public:
        PrintLabelPrintState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class PrintLabelEndState: public State {
    public:
        PrintLabelEndState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ApplyByTouchStartState: public State {
    public:
        ApplyByTouchStartState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ApplyByTouchApplyState: public State {
    public:
        ApplyByTouchApplyState(eos::fsm::StateMachine *sm);
        void transition(eos::fsm::Event event);
};

class ApplyByTouchEndState: public State {
    public:
        ApplyByTouchEndState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ErrorStartState: public State {
    public:
        ErrorStartState(eos::fsm::StateMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};



#endif
