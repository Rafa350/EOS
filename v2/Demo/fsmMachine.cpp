#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


MyMachine::MyMachine(eos::fsm::IController *ctl) {
    stateArmUpStart = new ArmUpStartState(this, ctl);
    stateArmUpMove = new ArmUpMoveState(this, ctl);
    stateArmUpEnd = new ArmUpEndState(this, ctl);
    stateArmDownStart = new ArmDownStartState(this, ctl);
    stateArmDownStop = new ArmDownStopState(this, ctl);
    statePrintLabelStart = new PrintLabelStartState(this, ctl);
    statePrintLabelPrint = new PrintLabelPrintState(this, ctl);
    statePrintLabelEnd = new PrintLabelEndState(this, ctl);
    stateErrorWaitForReset = new ErrorWaitForResetState(this, ctl);
    start(stateArmUpStart);
}
