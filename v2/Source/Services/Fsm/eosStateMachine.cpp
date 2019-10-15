#include "eos.h"
#include "Services/Fsm/eosFSM.h"


using namespace eos;


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


/*************************************************************************
 *
 *       Cabvia a un nou estat
 * 
 *       Funcio:
 *           void StateMachine::setState(
 *               State* state) 
 * 
 *       Entrada:
 *           state: El nou estat
 *
 *************************************************************************/

void StateMachine::setState(
    State* state) {
    
    states.pop();
    states.push(state);
}


/*************************************************************************
 *
 *       Canvia a un nou estat, salvant en la pila el actual
 * 
 *       Funcio:
 *           void StateMachine::pushState(
 *               State* state)
 *
 *       Entrada:
 *           state: El nou estat
 *
 *************************************************************************/

void StateMachine::pushState(State* state) {
    
    states.push(state);
}


/*************************************************************************
 *
 *       Canvia a l'ultim estat recuperat de la pila
 *
 *       Funcio:
 *           void StateMachine::popState() 
 *
 *************************************************************************/

void StateMachine::popState() {

    states.pop();
}
