#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


WaitTriggerWaitState::WaitTriggerWaitState(MyMachine *sm):
    State(sm) { 
}

void WaitTriggerWaitState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case INP_TR:
            sm->setState(sm->getWaitTriggerDelayState());
            break;
    }
};

WaitTriggerDelayState::WaitTriggerDelayState(MyMachine *sm):
    State(sm) { 
}

void WaitTriggerDelayState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, 100);
}

void WaitTriggerDelayState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getWaitTriggerState());
            break;
    }
};

ArmUpStartState::ArmUpStartState(MyMachine *sm):
    State(sm) { 
}

void ArmUpStartState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, ArmUpPreDelay);
}

void ArmUpStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getArmUpMoveState());
            break;
    }
};

ArmUpMoveState::ArmUpMoveState(MyMachine *sm):
    State(sm) { 
}

void ArmUpMoveState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->outClear(OUT_PD);
    ctx->outSet(OUT_PU);
    ctx->timStart(TIM_T1, ArmUpTimeout);
}

void ArmUpMoveState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_PT:
            if (PistonTopCondition) {
                sm->setState(sm->getArmUpEndState());
            }
            break;
        case EV_T1:
            sm->setState(sm->getErrorWaitForResetState());
            break;
    }
};

ArmUpEndState::ArmUpEndState(MyMachine *sm):
    State(sm) { 
}

void ArmUpEndState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, ArmUpPostDelay);
}

void ArmUpEndState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getErrorWaitForResetState());
            break;
    }
};

ArmDownStartState::ArmDownStartState(MyMachine *sm):
    State(sm) { 
}

void ArmDownStartState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, ArmDownPreDelay);
}

void ArmDownStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getArmDownStopState());
            break;
    }
};

ArmDownStopState::ArmDownStopState(MyMachine *sm):
    State(sm) { 
}

void ArmDownStopState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->outClear(OUT_PU);
    ctx->outClear(OUT_PD);
    ctx->timStart(TIM_T1, ArmDownPostDelay);
}

void ArmDownStopState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getErrorWaitForResetState());
            break;
    }
};

PrintLabelStartState::PrintLabelStartState(MyMachine *sm):
    State(sm) { 
}

void PrintLabelStartState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, PrintLabelPreDelay);
}

void PrintLabelStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getPrintLabelPrintState());
            break;
    }
};

PrintLabelPrintState::PrintLabelPrintState(MyMachine *sm):
    State(sm) { 
}

void PrintLabelPrintState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, AirAssistDelay);
    ctx->timStart(TIM_T2, VacuumDelay);
    ctx->timStart(TIM_T3, PrintLabelTimeout);
    ctx->outPulse(OUT_PL, 100);
}

void PrintLabelPrintState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            ctx->outSet(OUT_AA);
            sm->setState(sm->getPrintLabelState());
            break;
        case EV_T2:
            if (PrintVacuumModeOnCondition) {
                ctx->outSet(OUT_VC);
                sm->setState(sm->getPrintLabelState());
            }
            break;
        case EV_T3:
            ctx->outClear(OUT_VC);
            ctx->outClear(OUT_AA);
            sm->setState(sm->getErrorWaitForResetState());
            break;
        case EV_LR:
            ctx->outSet(OUT_VC);
            ctx->outClear(OUT_AA);
            sm->setState(sm->getPrintLabelEndState());
            break;
    }
};

PrintLabelEndState::PrintLabelEndState(MyMachine *sm):
    State(sm) { 
}

void PrintLabelEndState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, PrintLabelPostDelay);
}

void PrintLabelEndState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getPrintLabelState());
            break;
    }
};

ApplyByContactStartState::ApplyByContactStartState(MyMachine *sm):
    State(sm) { 
}

void ApplyByContactStartState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, ApplyByContactPreDelay);
}

void ApplyByContactStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getApplyByContactApplyState());
            break;
    }
};

ApplyByContactApplyState::ApplyByContactApplyState(MyMachine *sm):
    State(sm) { 
}

void ApplyByContactApplyState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            ctx->outClear(OUT_VC);
            sm->setState(sm->getErrorWaitForResetState());
            break;
        case EV_PB:
            ctx->outClear(OUT_VC);
            ctx->outPulse(OUT_AJ, );
            sm->setState(sm->getApplyByContactEndState());
            break;
    }
};

ApplyByContactEndState::ApplyByContactEndState(MyMachine *sm):
    State(sm) { 
}

void ApplyByContactEndState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->timStart(TIM_T1, ApplyByContactPostDelay);
}

void ApplyByContactEndState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case EV_T1:
            sm->setState(sm->getApplyByContactPrintState());
            break;
    }
};

ErrorWaitForResetState::ErrorWaitForResetState(MyMachine *sm):
    State(sm) { 
}

void ErrorWaitForResetState::enterAction() {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    ctx->outSet(OUT_ER);
}

void ErrorWaitForResetState::transition(eos::fsm::Event event) {

    MyMachine *sm = getStateMachine();
    eos::fsm::IContext *ctx = sm->getContext();

    switch (event) {
        case INP_ST:
            ctx->outClear(OUT_ER);
            sm->setState(sm->getErrorWaitForResetState());
            break;
    }
};

