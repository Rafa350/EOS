#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


ArmUpStartState::ArmUpStartState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ArmUpStartState::enterAction() {
    ctx->timStart(TIM_T1, ArmUpPreDelay);
}

eos::fsm::State *ArmUpStartState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getArmUpMoveState();
    }
    return sm->getState();
};

ArmUpMoveState::ArmUpMoveState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ArmUpMoveState::enterAction() {
    ctx->outClear(OUT_PD);
    ctx->outSet(OUT_PU);
    ctx->timStart(TIM_T1, ArmUpTimeout);
}

eos::fsm::State *ArmUpMoveState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_PT:
            if (PistonTopCondition) {
                return sm->getArmUpEndState();
            }
            break;
        case EV_T1:
            return sm->getErrorWaitForResetState();
    }
    return sm->getState();
};

ArmUpEndState::ArmUpEndState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ArmUpEndState::enterAction() {
    ctx->timStart(TIM_T1, ArmUpPostDelay);
}

eos::fsm::State *ArmUpEndState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getErrorWaitForResetState();
    }
    return sm->getState();
};

ArmDownStartState::ArmDownStartState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ArmDownStartState::enterAction() {
    ctx->timStart(TIM_T1, ArmDownPreDelay);
}

eos::fsm::State *ArmDownStartState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getArmDownStopState();
    }
    return sm->getState();
};

ArmDownStopState::ArmDownStopState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ArmDownStopState::enterAction() {
    ctx->outClear(OUT_PU);
    ctx->outClear(OUT_PD);
    ctx->timStart(TIM_T1, ArmDownPostDelay);
}

eos::fsm::State *ArmDownStopState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getErrorWaitForResetState();
    }
    return sm->getState();
};

PrintLabelStartState::PrintLabelStartState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void PrintLabelStartState::enterAction() {
    ctx->timStart(TIM_T1, PrintLabelPreDelay);
}

eos::fsm::State *PrintLabelStartState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getPrintLabelPrintState();
    }
    return sm->getState();
};

PrintLabelPrintState::PrintLabelPrintState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void PrintLabelPrintState::enterAction() {
    ctx->timStart(TIM_T1, AirAssistDelay);
    ctx->timStart(TIM_T2, VacuumDelay);
    ctx->timStart(TIM_T3, PrintLabelTimeout);
    ctx->outPulse(OUT_PL, 100);
}

eos::fsm::State *PrintLabelPrintState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            ctx->outSet(OUT_AA);
            return sm->getPrintLabelState();
        case EV_T2:
            if (PrintVacuumModeOnCondition) {
                ctx->outSet(OUT_VC);
                return sm->getPrintLabelState();
            }
            break;
        case EV_T3:
            ctx->outClear(OUT_VC);
            ctx->outClear(OUT_AA);
            return sm->getErrorWaitForResetState();
        case EV_LR:
            ctx->outSet(OUT_VC);
            ctx->outClear(OUT_AA);
            return sm->getPrintLabelEndState();
    }
    return sm->getState();
};

PrintLabelEndState::PrintLabelEndState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void PrintLabelEndState::enterAction() {
    ctx->timStart(TIM_T1, PrintLabelPostDelay);
}

eos::fsm::State *PrintLabelEndState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getPrintLabelState();
    }
    return sm->getState();
};

ApplyByContactStartState::ApplyByContactStartState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ApplyByContactStartState::enterAction() {
    ctx->timStart(TIM_T1, ApplyByContactPreDelay);
}

eos::fsm::State *ApplyByContactStartState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getApplyByContactApplyState();
    }
    return sm->getState();
};

ApplyByContactApplyState::ApplyByContactApplyState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

eos::fsm::State *ApplyByContactApplyState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            ctx->outClear(OUT_VC);
            return sm->getErrorWaitForResetState();
        case EV_PB:
            ctx->outClear(OUT_VC);
            ctx->outPulse(OUT_AJ, );
            return sm->getApplyByContactEndState();
    }
    return sm->getState();
};

ApplyByContactEndState::ApplyByContactEndState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ApplyByContactEndState::enterAction() {
    ctx->timStart(TIM_T1, ApplyByContactPostDelay);
}

eos::fsm::State *ApplyByContactEndState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getApplyByContactPrintState();
    }
    return sm->getState();
};

ErrorWaitForResetState::ErrorWaitForResetState(MyMachine *sm, eos::fsm::IContext *ctx) {
    this->sm = sm;
    this->ctx = ctx;
}

void ErrorWaitForResetState::enterAction() {
    ctx->outSet(OUT_ER);
}

eos::fsm::State *ErrorWaitForResetState::transition(eos::fsm::Event event) {
    switch (event) {
        case INP_ST:
            ctx->outClear(OUT_ER);
            return sm->getErrorWaitForResetState();
    }
    return sm->getState();
};

