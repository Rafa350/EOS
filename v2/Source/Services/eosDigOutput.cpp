// EOS
#include "eos.hpp"

#if eosOPTIONS_UseDigOutputService == 1
#include "Services/eosDigOutput.hpp"
#include "System/eosTask.hpp"

// FreeRTOS
#include "FReeRTOS.h"
#include "task.h"


#define TASK_PERIOD 10


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::DigOutputService::DigOutputService()
 *
 *************************************************************************/

eos::DigOutputService::DigOutputService() {
}


/*************************************************************************
 *
 *       Afegeig una sortida al servei
 *
 *       Funcio:
 *           void eos::DigOutputService::add(
 *               eos::DigOutput* output) 
 * 
 *       Entrada:
 *           output: La sortida a afeigit
 *
 *************************************************************************/

void eos::DigOutputService::add(
    eos::DigOutput* output) {
    
    outputs.add(output);
}


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           eos::DigOutputService::ServiceTask::ServiceTask(
 *               eos::DigOutputService *service)
 * 
 *       Entrada:
 *           service: El servei
 *
 *************************************************************************/

eos::DigOutputService::ServiceTask::ServiceTask(
    eos::DigOutputService *service) :
    Task(512, 5) {
    
    this->service = service;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eos::DigOutputService::ServiceTask::run() 
 *
 *************************************************************************/

void eos::DigOutputService::ServiceTask::run() {

    unsigned tc = eosGetTickCount();

    while (true) {

        delayUntil(TASK_PERIOD, &tc);
        
        eos::Task::enterCriticalSection();
        
        for (unsigned i = 0; i < service->outputs.getSize(); i++) {            
            eos::DigOutput *output = service->outputs[i];
            unsigned timeout = output->timeout;
            if (timeout > 0) {
                timeout -= 1;
                if (timeout == 0)
                    output->portToggle();
                output->timeout = timeout;
            }        
        }

        eos::Task::exitCriticalSection();
    }
}


/*************************************************************************
 *
 *       Constructor      
 *  
 *       Funcio:
 *           eos:DigOutput::DigOutputs(
 *               unsigned pin,
 *               bool inverted)
 *
 *       Entrada:
 *           pin     : Numero de pin hardware
 *           inverted: True si treballa amb logica negativa
 *
 *************************************************************************/

eos::DigOutput::DigOutput(
    unsigned pin,
    bool inverted): 
    DigOutput(nullptr, pin, inverted) {    
}


/*************************************************************************
 *
 *       Constructor      
 *  
 *       Funcio:
 *           eos:DigOutput::DigOutputs(
 *               eos::DigOutputService *service,
 *               unsigned pin,
 *               bool inverted)
 *
 *       Entrada:
 *           service : El servei
 *           pin     : Numero de pin hardware
 *           inverted: True si treballa amb logica negativa
 *
 *************************************************************************/

eos::DigOutput::DigOutput(
    eos::DigOutputService *service,
    unsigned pin,
    bool inverted) {
    
    if (service != nullptr)
        service->add(this);

    this->pin = pin;
    this->inverted = inverted;
    this->timeout = 0;

    pinInitialize();
}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           bool eos::DigOutput::get()
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

bool eos::DigOutput::get() {

    return pinGet();
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           void eos::DigOutput::set(
 *               bool state)
 *
 *       Entrada:
 *           state  : L'estat a signar
 *
 *************************************************************************/

void eos::DigOutput::set(
    bool state) {

    eos::Task::enterCriticalSection();
    
    pinSet(state);
    timeout = 0;
    
    eos::Task::exitCriticalSection();
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void eos::DigOutput::toggle()
 *
 *************************************************************************/

void eos::DigOutput::toggle() {

    eos::Task::enterCriticalSection();
    
    pinToggle();
    timeout = 0;
    
    eos::Task::exitCriticalSection();
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida. La resolucio
 *       es en multiples de TASK_PERIOD
 *
 *       Funcio:
 *           void eos::DigOutput::pulse(
 *               unsigned time)
 *
 *       Entrada:
 *           time   : Duracio del puls
 * 
 *       Notes:
 *           Si encara esta en un puls, unicament l'allarga
 *
 *************************************************************************/

void eos::DigOutput::pulse(
    unsigned time) {

    if (time >= TASK_PERIOD) {

        eos::Task::enterCriticalSection();
        
        if (timeout == 0)
            pinToggle();
        timeout = time / TASK_PERIOD;
        
        eos::Task::exitCriticalSection();
    }
}


void eos::DigOutput::pinInitialize() {
        
    eosDigPinSet(pin, inverted ? true : false);
    eosDigPinOutputMode(pin);    
}


bool eos::DigOutput::pinGet() {
    
    bool p = eosDigPinGet(pin);
    return inverted ? !p : p;
}


void eos::DigOutput::pinSet(
    bool state) {
    
    eosDigPinSet(pin, state);
}


void eos::DigOutput::pinToggle() {

    eosDigPinToggle(pin);
}


#endif
