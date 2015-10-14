#ifndef __FSM_STATES_HPP
#define __FSM_STATES_HPP


#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"


class WaitTriggerWaitState: public eos::fsm::State {
    public:
        WaitTriggerWaitState(MyMachine *sm);
        void transition(eos::fsm::Event event);
};

class WaitTriggerDelayState: public eos::fsm::State {
    public:
        WaitTriggerDelayState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmUpStartState: public eos::fsm::State {
    public:
        ArmUpStartState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmUpMoveState: public eos::fsm::State {
    public:
        ArmUpMoveState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmUpEndState: public eos::fsm::State {
    public:
        ArmUpEndState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmDownStartState: public eos::fsm::State {
    public:
        ArmDownStartState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ArmDownStopState: public eos::fsm::State {
    public:
        ArmDownStopState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class PrintLabelStartState: public eos::fsm::State {
    public:
        PrintLabelStartState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class PrintLabelPrintState: public eos::fsm::State {
    public:
        PrintLabelPrintState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class PrintLabelEndState: public eos::fsm::State {
    public:
        PrintLabelEndState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ApplyByContactStartState: public eos::fsm::State {
    public:
        ApplyByContactStartState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ApplyByContactApplyState: public eos::fsm::State {
    public:
        ApplyByContactApplyState(MyMachine *sm);
        void transition(eos::fsm::Event event);
};

class ApplyByContactEndState: public eos::fsm::State {
    public:
        ApplyByContactEndState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};

class ErrorWaitForResetState: public eos::fsm::State {
    public:
        ErrorWaitForResetState(MyMachine *sm);
        void enterAction();
        void transition(eos::fsm::Event event);
};



#endif
