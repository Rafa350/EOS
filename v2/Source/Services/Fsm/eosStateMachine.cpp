#include "Services/eosFSM.hpp"


using namespace eos::fsm;


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           StateMachine::StateMachine()
 *
 *************************************************************************/

StateMachine::StateMachine() {
    
    state = nullptr;
}


/*************************************************************************
 *
 *       Inicia la maquina d'estats i es posa en l'estat inicial
 *
 *       Funcio:
 *           void StateMachine::start(
 *               State *initialState) 
 * 
 *       Entrada:
 *           initialState: Estat inicial
 * 
 *************************************************************************/

void StateMachine::start(
    State *initialState) {
    
    state = initialState;
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

    State* newState = state->transition(event);
    if (newState != state) {
        state->exitAction();
        state = newState;
        state->enterAction();
    }
}

