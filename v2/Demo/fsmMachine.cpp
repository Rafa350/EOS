#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


MyMachine::MyMachine(eos::fsm::IContext *context) :
    eos::fsm::StateMachine(context) {

    stateArmUpStart = new ArmUpStartState(this, context);
    stateArmUpMove = new ArmUpMoveState(this, context);
    stateArmUpEnd = new ArmUpEndState(this, context);
    stateArmDownStart = new ArmDownStartState(this, context);
    stateArmDownStop = new ArmDownStopState(this, context);
    statePrintLabelStart = new PrintLabelStartState(this, context);
    statePrintLabelPrint = new PrintLabelPrintState(this, context);
    statePrintLabelEnd = new PrintLabelEndState(this, context);
    stateApplyByContactStart = new ApplyByContactStartState(this, context);
    stateApplyByContactApply = new ApplyByContactApplyState(this, context);
    stateApplyByContactEnd = new ApplyByContactEndState(this, context);
    stateErrorWaitForReset = new ErrorWaitForResetState(this, context);

    start(stateArmUpStart);
}
