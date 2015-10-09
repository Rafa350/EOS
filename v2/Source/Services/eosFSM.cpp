#include "Services/eosFSM.hpp"


using namespace eos;


/*************************************************************************
 *
 *      Constructor
 * 
 *      Funcio:
 *          StateMachineService::StateMachineService(
 *              IStateMachine *sm) 
 * 
 *      Entrada:
 *          sm: Implementacio de la maquina d'estats
 *
 *************************************************************************/

StateMachineService::StateMachineService(
    IStateMachine *sm) {
        
    this->sm = sm;
}


/*************************************************************************
 * 
 *      Destructor
 * 
 *      Funcio:
 *          StateMachineService::~StateMachineService() 
 * 
 *************************************************************************/

StateMachineService::~StateMachineService() {
    
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
        
        if (externalEventQueue.get(event)) {
            do {
                sm->processEvent(event);
            } while (internalEventQueue(event));
        }
        
    }
    
}


/*************************************************************************
 *
 *       Envia un event extern a la maquina d'estats
 * 
 *       Funcio:
 *           void StateMachineService::ExternalEvent(
 *               Event event)
 * 
 *       Funcio:
 *           event: El event
 *
 *************************************************************************/

void StateMachineService::ExternalEvent(
    Event event) {
    
    externalEventQueue.put(event, -1);
}


/*************************************************************************
 *
 *       Envia un event intern a la maquina d'estats
 * 
 *       Funcio:
 *           void StateMachineService::InternalEvent(
 *               Event event)
 * 
 *       Funcio:
 *           event: El event
 *
 *************************************************************************/

void StateMachineService::InternalEvent(Event event) {
    
    internalEventQueue.put(event, 0);
}