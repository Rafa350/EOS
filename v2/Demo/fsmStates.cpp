#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


InitialPauseState::InitialPauseState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void InitialPauseState::enterAction() {
    ctl->timStart(TIM_1, 1000);
}

eos::fsm::State *InitialPauseState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T1:
            return ((MyMachine*) sm)->getArmUpState();
    }
    return sm->getState();
};

ArmUpState::ArmUpState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void ArmUpState::enterAction() {
    ctl->outClear(OUT_PD);
    ctl->outSet(OUT_PU);
    ctl->timStart(TIM_2, 1200);
}

eos::fsm::State *ArmUpState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_PT:
            if (1 == 1) {
                ctl->outClear(OUT_PD);
                return ((MyMachine*) sm)->getFinalPauseState();
            }
            break;
        case EV_T2:
            ctl->outToggle(OUT_PD);
            return ((MyMachine*) sm)->getErrorState();
    }
    return sm->getState();
};

FinalPauseState::FinalPauseState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

void FinalPauseState::enterAction() {
    ctl->timStart(TIM_3, 500);
}

eos::fsm::State *FinalPauseState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_T3:
            return ((MyMachine*) sm)->getStopState();
    }
    return sm->getState();
};

ErrorState::ErrorState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

eos::fsm::State *ErrorState::transition(eos::fsm::Event event) {
    switch (event) {
        case EV_ST:
            return ((MyMachine*) sm)->getStopState();
    }
    return sm->getState();
};

StopState::StopState(eos::fsm::StateMachine *sm, eos::fsm::IController *ctl) {
    this->sm = sm;
    this->ctl = ctl;
}

eos::fsm::State *StopState::transition(eos::fsm::Event event) {
    switch (event) {
    }
    return sm->getState();
};

