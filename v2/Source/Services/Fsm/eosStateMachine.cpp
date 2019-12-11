#include "eos.h"
#include "Services/Fsm/eosStateMachine.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    context: Dades de context.
///
StateMachine::StateMachine(
    IContext* context) {

    this->context = context;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la maquina.
/// \param    state: EL'estat inicial.
///
void StateMachine::start(
    State* state) {

    states.push(state);
    state->enterAction();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un event.
/// \param    event: L'event a procesar.
///
void StateMachine::acceptEvent(
    Event event) {

    State* curState = states.peek();
    curState->transition(event);
    State* newState = states.peek();
    if (newState != curState) {
        curState->exitAction();
        newState->enterAction();
    }
}


void StateMachine::setState(
    State* state) {

    states.pop();
    states.push(state);
}


void StateMachine::pushState(
    State* state) {

    states.push(state);
}


void StateMachine::popState() {

    states.pop();
}
