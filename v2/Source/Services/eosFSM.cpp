#include "Services/eosFSM.hpp"


using namespace eos;


/*************************************************************************
 *
 *      Constructor
 * 
 *      Funcio:
 *          StateMachineService::StateMachineService(
 *              StateMachine *sm) 
 * 
 *      Entrada:
 *          sm: Implementacio de la maquina d'estats
 *
 *************************************************************************/

StateMachineService::StateMachineService(
    StateMachine *sm): 
    eventQueue(10) {
        
    this->sm = sm;
}


/*************************************************************************
 *
 *       Executa la tasca de control del servei
 * 
 *       Funcio:
 *           void StateMachineService::run() 
 *
 *************************************************************************/

void StateMachineService::run() {
    
    while (true) {
        
        Event event;
        
        if (eventQueue.get(event, 1000)) 
            sm->acceptEvent(event);
    }
}


/*************************************************************************
 *
 *       Envia un event extern a la maquina d'estats
 * 
 *       Funcio:
 *           bool StateMachineService::acceptEvent(
 *               Event event,
 *               unsigned timeout)
 * 
 *       Funcio:
 *           event: El event
 *           timeout: Temos mkaxim d'espera
 * 
 *       Retorn:
 *           TRue si ha acceptat l'event. False en cas contari
 *
 *************************************************************************/

bool StateMachineService::acceptEvent(
    Event event,
    unsigned timeout) {
    
    return eventQueue.put(event, timeout);
}
