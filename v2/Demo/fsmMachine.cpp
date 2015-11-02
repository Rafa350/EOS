#include "Services/Fsm/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


MyMachine::MyMachine(eos::fsm::IContext *context) :
    eos::fsm::StateMachine(context) {

    stateLoopSW1 = new LoopSW1State(this);
    stateLoopSW2 = new LoopSW2State(this);
    stateLoopSW3 = new LoopSW3State(this);

    start(stateLoopSW1);
}
