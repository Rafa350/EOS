#include "Services/eosFSM.hpp"


using namespace eos::fsm;


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           StateMachine::StateMachine(
 *               IContext *context)
 * 
 *       Entrada:
 *           context: Contexte de la maquina
 *
 *************************************************************************/

StateMachine::StateMachine(
    IContext *context) {
    
    this->context = context;
}


/*************************************************************************
 *
 *       Inicia la maquina d'estats i es posa en l'estat inicial
 *
 *       Funcio:
 *           void StateMachine::start(
 *               State *state) 
 * 
 *       Entrada:
 *           initialState: Estat inicial
 * 
 *************************************************************************/

void StateMachine::start(
    State *state) {
    
    states.push(state);
    state->enterAction();
}


/*************************************************************************
 *
 *       Accepta un event
 * 
 *       Funcio:
 *           void StateMachine::acceptEvent(
 *               Event event) 
 * 
 *       Entrada:
 *           event: El event
 *
 *************************************************************************/

void StateMachine::acceptEvent(
    Event event) {

    State *curState = states.top();
    curState->transition(event);
    State *newState = states.top();
    if (newState != curState) {
        curState->exitAction();
        newState->enterAction();
    }
}


void StateMachine::setState(State* state) {
    
    states.pop();
    states.push(state);
}


void StateMachine::pushState(State* state) {
    
    states.push(state);
}


void StateMachine::popState() {

    states.pop();
}
