#include "eos.h"
#include "Services/Fsm/eosFsmMachine.h"
#include "Services/Fsm/eosFsmState.h"


using namespace eos;


FsmState::FsmState() {

}


void FsmState::enterAction() {

}

void FsmState::exitAction() {

}


void FsmState::acceptEvent(
    FsmMachine *machine,
    const FsmEvent& event) {

}
