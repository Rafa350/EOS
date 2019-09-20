#include "Services/Fsm/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


MyMachine::MyMachine(eos::fsm::IContext *context) :
    eos::fsm::StateMachine(context) {

    stateWaitTriggerStart = new WaitTriggerStartState(this);
    stateWaitTriggerDelay = new WaitTriggerDelayState(this);
    stateArmUpStart = new ArmUpStartState(this);
    stateArmUpMove = new ArmUpMoveState(this);
    stateArmUpEnd = new ArmUpEndState(this);
    stateArmDownStart = new ArmDownStartState(this);
    stateArmDownEnd = new ArmDownEndState(this);
    statePrintLabelStart = new PrintLabelStartState(this);
    statePrintLabelPrint = new PrintLabelPrintState(this);
    statePrintLabelEnd = new PrintLabelEndState(this);
    stateApplyByTouchStart = new ApplyByTouchStartState(this);
    stateApplyByTouchApply = new ApplyByTouchApplyState(this);
    stateApplyByTouchEnd = new ApplyByTouchEndState(this);
    stateErrorStart = new ErrorStartState(this);

    start(stateArmUpStart);
}
