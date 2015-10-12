#ifndef __FSM_MACHINE_HPP
#define __FSM_MACHINE_HPP


#include "Services/eosFSM.hpp"


class MyMachine: public eos::fsm::StateMachine {
    private:
        eos::fsm::State *stateWaitTriggerWait;
        eos::fsm::State *stateWaitTriggerDelay;
        eos::fsm::State *stateArmUpStart;
        eos::fsm::State *stateArmUpMove;
        eos::fsm::State *stateArmUpEnd;
        eos::fsm::State *stateArmDownStart;
        eos::fsm::State *stateArmDownStop;
        eos::fsm::State *statePrintLabelStart;
        eos::fsm::State *statePrintLabelPrint;
        eos::fsm::State *statePrintLabelEnd;
        eos::fsm::State *stateApplyByContactStart;
        eos::fsm::State *stateApplyByContactApply;
        eos::fsm::State *stateApplyByContactEnd;
        eos::fsm::State *stateErrorWaitForReset;
    public:
        MyMachine(eos::fsm::IContext *context);
        eos::fsm::State *getWaitTriggerWaitState() const { return stateWaitTriggerWait; }
        eos::fsm::State *getWaitTriggerDelayState() const { return stateWaitTriggerDelay; }
        eos::fsm::State *getArmUpStartState() const { return stateArmUpStart; }
        eos::fsm::State *getArmUpMoveState() const { return stateArmUpMove; }
        eos::fsm::State *getArmUpEndState() const { return stateArmUpEnd; }
        eos::fsm::State *getArmDownStartState() const { return stateArmDownStart; }
        eos::fsm::State *getArmDownStopState() const { return stateArmDownStop; }
        eos::fsm::State *getPrintLabelStartState() const { return statePrintLabelStart; }
        eos::fsm::State *getPrintLabelPrintState() const { return statePrintLabelPrint; }
        eos::fsm::State *getPrintLabelEndState() const { return statePrintLabelEnd; }
        eos::fsm::State *getApplyByContactStartState() const { return stateApplyByContactStart; }
        eos::fsm::State *getApplyByContactApplyState() const { return stateApplyByContactApply; }
        eos::fsm::State *getApplyByContactEndState() const { return stateApplyByContactEnd; }
        eos::fsm::State *getErrorWaitForResetState() const { return stateErrorWaitForReset; }
};


#endif
