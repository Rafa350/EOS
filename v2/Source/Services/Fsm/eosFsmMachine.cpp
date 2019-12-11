#include "eos.h"
#include "Services/Fsm/eosFsmMachine.h"
#include "Services/Fsm/eosFsmState.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
FsmMachine::FsmMachine() {
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la maquina.
/// \param    state: EL'estat inicial.
///
void FsmMachine::start(
    FsmState* state) {

    states.push(state);
    state->enterAction();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un event.
/// \param    event: L'event a procesar.
///
void FsmMachine::acceptEvent(
    const FsmEvent& event) {

    FsmState* curState = states.peek();
    curState->acceptEvent(this, event);
    FsmState* newState = states.peek();
    if (newState != curState) {
        curState->exitAction();
        newState->enterAction();
    }
}


void FsmMachine::setState(
    FsmState* state) {

    states.pop();
    states.push(state);
}


void FsmMachine::pushState(
    FsmState* state) {

    states.push(state);
}


void FsmMachine::popState() {

    states.pop();
}
