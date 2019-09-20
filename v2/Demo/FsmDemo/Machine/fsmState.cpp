#include "Services/Fsm/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


WaitTriggerStartState::WaitTriggerStartState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void WaitTriggerStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case INP_Trigger:
            sm->setState(sm->getWaitTriggerDelayState());
            break;

    }
}

WaitTriggerDelayState::WaitTriggerDelayState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void WaitTriggerDelayState::enterAction() {

    timStart(TIM_T1, varGet(VAR_TriggerDelay));
    
}

void WaitTriggerDelayState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getPrintLabelStartState());
            break;

    }
}

ArmUpStartState::ArmUpStartState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ArmUpStartState::enterAction() {

    notify(SIG_ArmUpStartActivity);
    timStart(TIM_T1, varGet(VAR_ArmUpPreDelay));
    
}

void ArmUpStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getArmUpMoveState());
            break;

    }
}

ArmUpMoveState::ArmUpMoveState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ArmUpMoveState::enterAction() {

    doPistonUp();
    timStart(TIM_T1, varGet(VAR_ArmUpTimeout));
    
}

void ArmUpMoveState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_INP_PistonTop:
            sm->setState(sm->getArmUpEndState());
            break;

        case EV_TIM_T1:
            sm->setState(sm->getErrorStartState());
            break;

    }
}

ArmUpEndState::ArmUpEndState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ArmUpEndState::enterAction() {

    timStart(TIM_T1, varGet(VAR_ArmUpPostDelay));
    
}

void ArmUpEndState::exitAction() {

    notify(SIG_ArmUpEndActivity);
    
}

void ArmUpEndState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getWaitTriggerStartState());
            break;

    }
}

ArmDownStartState::ArmDownStartState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ArmDownStartState::enterAction() {

    notify(SIG_ArmDownStartActivity);
    timStart(TIM_T1, varGet(VAR_ArmDownPreDelay));
    
}

void ArmDownStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getArmDownEndState());
            break;

    }
}

ArmDownEndState::ArmDownEndState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ArmDownEndState::enterAction() {

    doPistonDown();
    timStart(TIM_T1, varGet(VAR_ArmDownPostDelay));
    
}

void ArmDownEndState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getApplyByTouchStartState());
            break;

    }
}

PrintLabelStartState::PrintLabelStartState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void PrintLabelStartState::enterAction() {

    timStart(TIM_T1, varGet(VAR_PrintLabelPreDelay));
    
}

void PrintLabelStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getPrintLabelPrintState());
            break;

    }
}

PrintLabelPrintState::PrintLabelPrintState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void PrintLabelPrintState::enterAction() {

    if (inpGet(INP_PrinterError))
    fsmSetState(ST_ErrorStart);
    else {
    timStart(TIM_T1, varGet(VAR_AirAssistDelay));
    timStart(TIM_T2, varGet(VAR_VacuumDelay));
    timStart(TIM_T3, varGet(VAR_PrintLabelTimeout));
    doPrintLabel();
    }
    
}

void PrintLabelPrintState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            doAirAssistOn();
            
            break;

        case EV_TIM_T2:
            doVacuumOn();
            
            break;

        case EV_TIM_T3:
            doAirAssistOff();
            doVacuumOff();
            
            sm->setState(sm->getErrorStartState());
            break;

        case EV_INP_LabelReady:
            doAirAssistOff();
            doVacuumOn();
            
            sm->setState(sm->getPrintLabelEndState());
            break;

        case EV_INP_PrinterError:
            doAirAssistOff();
            doVacuumOff();
            
            sm->setState(sm->getErrorStartState());
            break;

    }
}

PrintLabelEndState::PrintLabelEndState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void PrintLabelEndState::enterAction() {

    timStart(TIM_T1, varGet(VAR_PrintLabelPostDelay));
    
}

void PrintLabelEndState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getArmDownStartState());
            break;

    }
}

ApplyByTouchStartState::ApplyByTouchStartState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ApplyByTouchStartState::enterAction() {

    timStart(TIM_T1, varGet(VAR_ApplyByContactPreDelay));
    
}

void ApplyByTouchStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getApplyByTouchApplyState());
            break;

    }
}

ApplyByTouchApplyState::ApplyByTouchApplyState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ApplyByTouchApplyState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            doVacuumOff();
            
            sm->setState(sm->getErrorStartState());
            break;

        case EV_INP_PistonBottom:
            doSignalWorkingPulse();
            doVacuumOff();
            doAirJetPulse();
            
            sm->setState(sm->getApplyByTouchEndState());
            break;

    }
}

ApplyByTouchEndState::ApplyByTouchEndState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ApplyByTouchEndState::enterAction() {

    timStart(TIM_T1, varGet(VAR_ApplyByContactPostDelay));
    
}

void ApplyByTouchEndState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_TIM_T1:
            sm->setState(sm->getArmUpStartState());
            break;

    }
}

ErrorStartState::ErrorStartState(eos::fsm::StateMachine *sm):
    State(sm) {
}

void ErrorStartState::enterAction() {

    doSignalErrorOn();
    doSignalWorkingOff();
    
}

void ErrorStartState::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case EV_INP_Restart:
            doSignalErrorOff();
            doPistonUp();
            
            sm->setState(sm->getWaitTriggerStartState());
            break;

    }
}

