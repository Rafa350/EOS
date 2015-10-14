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
    IContext *context):
    states(10) {
    
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

    State *curState = states.get();
    curState->transition(event);
    State *newState = states.get();
    if (newState != curState) {
        curState->exitAction();
        newState->enterAction();
    }
}

