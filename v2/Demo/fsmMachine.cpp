#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


MyMachine::MyMachine(eos::fsm::IContext *context) :
    eos::fsm::StateMachine(context) {

    stateWaitTriggerWait = new WaitTriggerWaitState(this);
    stateWaitTriggerDelay = new WaitTriggerDelayState(this);
    stateArmUpStart = new ArmUpStartState(this);
    stateArmUpMove = new ArmUpMoveState(this);
    stateArmUpEnd = new ArmUpEndState(this);
    stateArmDownStart = new ArmDownStartState(this);
    stateArmDownStop = new ArmDownStopState(this);
    statePrintLabelStart = new PrintLabelStartState(this);
    statePrintLabelPrint = new PrintLabelPrintState(this);
    statePrintLabelEnd = new PrintLabelEndState(this);
    stateApplyByContactStart = new ApplyByContactStartState(this);
    stateApplyByContactApply = new ApplyByContactApplyState(this);
    stateApplyByContactEnd = new ApplyByContactEndState(this);
    stateErrorWaitForReset = new ErrorWaitForResetState(this);

    start(stateArmUpStart);
}
