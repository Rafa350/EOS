#ifndef __FSM_MACHINE_HPP
#define __FSM_MACHINE_HPP


#include "Services/Fsm/eosFSM.hpp"


class MyMachine: public Machine {
    private:
        eos::fsm::State *stateWaitTriggerStart;
        eos::fsm::State *stateWaitTriggerDelay;
        eos::fsm::State *stateArmUpStart;
        eos::fsm::State *stateArmUpMove;
        eos::fsm::State *stateArmUpEnd;
        eos::fsm::State *stateArmDownStart;
        eos::fsm::State *stateArmDownEnd;
        eos::fsm::State *statePrintLabelStart;
        eos::fsm::State *statePrintLabelPrint;
        eos::fsm::State *statePrintLabelEnd;
        eos::fsm::State *stateApplyByTouchStart;
        eos::fsm::State *stateApplyByTouchApply;
        eos::fsm::State *stateApplyByTouchEnd;
        eos::fsm::State *stateErrorStart;
    public:
        MyMachine(eos::fsm::IContext *context);
        eos::fsm::State *getWaitTriggerStartState() const { return stateWaitTriggerStart; }
        eos::fsm::State *getWaitTriggerDelayState() const { return stateWaitTriggerDelay; }
        eos::fsm::State *getArmUpStartState() const { return stateArmUpStart; }
        eos::fsm::State *getArmUpMoveState() const { return stateArmUpMove; }
        eos::fsm::State *getArmUpEndState() const { return stateArmUpEnd; }
        eos::fsm::State *getArmDownStartState() const { return stateArmDownStart; }
        eos::fsm::State *getArmDownEndState() const { return stateArmDownEnd; }
        eos::fsm::State *getPrintLabelStartState() const { return statePrintLabelStart; }
        eos::fsm::State *getPrintLabelPrintState() const { return statePrintLabelPrint; }
        eos::fsm::State *getPrintLabelEndState() const { return statePrintLabelEnd; }
        eos::fsm::State *getApplyByTouchStartState() const { return stateApplyByTouchStart; }
        eos::fsm::State *getApplyByTouchApplyState() const { return stateApplyByTouchApply; }
        eos::fsm::State *getApplyByTouchEndState() const { return stateApplyByTouchEnd; }
        eos::fsm::State *getErrorStartState() const { return stateErrorStart; }
};


#endif
