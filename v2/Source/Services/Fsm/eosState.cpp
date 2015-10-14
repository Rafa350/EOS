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
 *           State *State::transition(
 *               Event event) 
 * 
 *       Entrada:
 *           event: L'event a procesar
 *
 *************************************************************************/

State *State::transition(
    Event event) {
    
}
