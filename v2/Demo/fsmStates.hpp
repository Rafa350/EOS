#ifndef __FSM_STATES_HPP
#define __FSM_STATES_HPP


#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"


class ArmUpStartState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ArmUpStartState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmUpMoveState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ArmUpMoveState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmUpEndState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ArmUpEndState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmDownStartState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ArmDownStartState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ArmDownStopState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ArmDownStopState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class PrintLabelStartState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        PrintLabelStartState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class PrintLabelPrintState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        PrintLabelPrintState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class PrintLabelEndState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        PrintLabelEndState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ApplyByContactStartState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ApplyByContactStartState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ApplyByContactApplyState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ApplyByContactApplyState(MyMachine *sm, eos::fsm::IContext *ctx);
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ApplyByContactEndState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ApplyByContactEndState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};

class ErrorWaitForResetState: public eos::fsm::State {
    private:
        MyMachine *sm;
        eos::fsm::IContext *ctx;
    public:
        ErrorWaitForResetState(MyMachine *sm, eos::fsm::IContext *ctx);
        void enterAction();
        eos::fsm::State *transition(eos::fsm::Event event);
};



#endif
