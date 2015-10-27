#include "Services/eosFSM.hpp"


using namespace eos::fsm;


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           State::State(
 *               StateMachine *sm) 
 * 
 *       Entrada: 
 *           sm: La maquina d'estats a la que pertany
 *
 *************************************************************************/

State::State(
    StateMachine *sm) {
    
    this->sm = sm;
}


/*************************************************************************
 *
 *       Accio a executar al entrar en un estat
 * 
 *       Funcio:
 *           void State::enterAction() 
 *
 *************************************************************************/

void State::enterAction() {
    
}


/*************************************************************************
 *
 *       Accio a executar al sortir d'un estat
 * 
 *       Funcio:
 *           void State::exitAction() 
 * 
 *************************************************************************/

void State::exitAction() {
    
}


/*************************************************************************
 *
 *       Procesa els events
 * 
 *       Funcio:
 *           void State::transition(
 *               Event event) 
 * 
 *       Entrada:
 *           event: L'event a procesar
 *
 *************************************************************************/

void State::transition(
    Event event) {
    
}


/*************************************************************************
 *
 *       Canvia a un nou estat
 * 
 *       Funcio: 
 *           void State::setState(
 *               State *state) 
 * 
 *       Entrada:
 *           state: El nou estat
 *
 *************************************************************************/

void State::setState(
    State *state) {
    
    sm->setState(state);
}
    

/*************************************************************************
 *
 *       Canvia a un nou estat, salvant l'ancual en la pila per
 *       poder ser recuperat posteriorment
 * 
 *       Funcio:
 *           void State::pushState(
 *               State *state) 
 * 
 *       Entrada:
 *           state: El nou estat
 *
 *************************************************************************/

void State::pushState(
    State *state) {
    
    sm->pushState(state);
}
    

/*************************************************************************
 *
 *       Canvia al ultim estat de la pila
 * 
 *       Funcio:
 *           void State::popState() 
 *
 *************************************************************************/

void State::popState() {
    
    sm->popState();    
}
