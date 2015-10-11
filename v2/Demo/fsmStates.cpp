#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


ArmUpStartState::ArmUpStartState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void ArmUpStartState::enterAction() {
    ctl->timStart(TIM_T1, ArmUpPreDelay);
}

eos::fsm::State *ArmUpStartState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getArmUpMoveState();
    }
    return sm->getState();
};

ArmUpMoveState::ArmUpMoveState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void ArmUpMoveState::enterAction() {
    ctl->outClear(OUT_PD);
    ctl->outSet(OUT_PU);
    ctl->timStart(TIM_T1, ArmUpTimeout);
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

ArmUpEndState::ArmUpEndState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void ArmUpEndState::enterAction() {
    ctl->timStart(TIM_T1, ArmUpPostDelay);
}

eos::fsm::State *ArmUpEndState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getErrorWaitForResetState();
    }
    return sm->getState();
};

ArmDownStartState::ArmDownStartState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void ArmDownStartState::enterAction() {
    ctl->timStart(TIM_T1, ArmDownPreDelay);
}

eos::fsm::State *ArmDownStartState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getArmDownStopState();
    }
    return sm->getState();
};

ArmDownStopState::ArmDownStopState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void ArmDownStopState::enterAction() {
    ctl->outClear(OUT_PU);
    ctl->outClear(OUT_PD);
    ctl->timStart(TIM_T1, ArmDownPostDelay);
}

eos::fsm::State *ArmDownStopState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getErrorWaitForResetState();
    }
    return sm->getState();
};

PrintLabelStartState::PrintLabelStartState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void PrintLabelStartState::enterAction() {
    ctl->timStart(TIM_T1, PrintLabelPreDelay);
}

eos::fsm::State *PrintLabelStartState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getPrintLabelPrintState();
    }
    return sm->getState();
};

PrintLabelPrintState::PrintLabelPrintState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void PrintLabelPrintState::enterAction() {
    ctl->timStart(TIM_T1, AirAssistDelay);
    ctl->timStart(TIM_T2, VacuumDelay);
    ctl->timStart(TIM_T3, PrintLabelTimeout);
    ctl->outPulse(OUT_PL, 100);
}

eos::fsm::State *PrintLabelPrintState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            ctl->outSet(OUT_AA);
            return sm->getPrintLabelState();
        case EV_T2:
            if (PrintVacuumModeOnCondition) {
                ctl->outSet(OUT_VC);
                return sm->getPrintLabelState();
            }
            break;
        case EV_T3:
            ctl->outClear(OUT_VC);
            ctl->outClear(OUT_AA);
            return sm->getErrorWaitForResetState();
        case EV_LR:
            ctl->outSet(OUT_VC);
            ctl->outClear(OUT_AA);
            return sm->getPrintLabelEndState();
    }
    return sm->getState();
};

PrintLabelEndState::PrintLabelEndState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void PrintLabelEndState::enterAction() {
    ctl->timStart(TIM_T1, PrintLabelPostDelay);
}

eos::fsm::State *PrintLabelEndState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return sm->getPrintLabelState();
    }
    return sm->getState();
};

ErrorWaitForResetState::ErrorWaitForResetState(MyMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void ErrorWaitForResetState::enterAction() {
    ctl->outSet(OUT_ER);
}

eos::fsm::State *ErrorWaitForResetState::transition(eos::fsm::Event event) {
    switch (event) {
        case INP_ST:
            ctl->outClear(OUT_ER);
            return sm->getErrorWaitForResetState();
    }
    return sm->getState();
};

