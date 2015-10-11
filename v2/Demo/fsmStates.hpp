#ifndef __FSM_STATES_HPP
#define __FSM_STATES_HPP


#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"


class ArmUpStartState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ArmUpStartState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmUpMoveState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ArmUpMoveState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmUpEndState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ArmUpEndState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmDownStartState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ArmDownStartState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmDownStopState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ArmDownStopState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class PrintLabelStartState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        PrintLabelStartState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class PrintLabelPrintState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        PrintLabelPrintState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class PrintLabelEndState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        PrintLabelEndState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ErrorWaitForResetState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IController *ctl;
    public:
        ErrorWaitForResetState(MyMachine *sm, eos::fsm::IController *ctl);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};



#endif
