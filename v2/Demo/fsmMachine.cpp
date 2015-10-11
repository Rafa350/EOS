#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


MyMachine::MyMachine(eos::fsm::IController *ctl) {
    stateInitialPause = new InitialPauseState(this, ctl);
    stateArmUp = new ArmUpState(this, ctl);
    stateFinalPause = new FinalPauseState(this, ctl);
    stateError = new ErrorState(this, ctl);
    stateStop = new StopState(this, ctl);
}
