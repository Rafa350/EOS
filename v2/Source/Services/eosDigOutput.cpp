#include "Services/eosDigOutput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"
#include "FReeRTOS.h"
#include "task.h"


#define TASK_PERIOD     10

const unsigned taskStackSize = 512;
const eos::TaskPriority taskPriority = eos::TaskPriority::normal;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::DigOutputService::DigOutputService()
 *
 *************************************************************************/

eos::DigOutputService::DigOutputService() :
    task(taskStackSize, taskPriority, this) {
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
    
    eos::Task::enterCriticalSection();
    outputs.add(output);
    eos::Task::exitCriticalSection();
}


/*************************************************************************
 *
 *       Executa la tasca de control de servei
 * 
 *       Funcio:
 *           void eos::DigOutputService::run() 
 *
 *************************************************************************/

void eos::DigOutputService::run() {
    
    unsigned tc = eos::Task::getTickCount();

    while (true) {

        eos::Task::delayUntil(TASK_PERIOD, &tc);
        
        eos::Task::enterCriticalSection();
        
        for (unsigned i = 0; i < outputs.getCount(); i++) {          
            
            eos::DigOutput *output = outputs[i];
    
            unsigned t = output->timeout;
            if (t > 0) {
                t -= 1;
                if (t == 0)
                    output->pinToggle();
                output->timeout = t;
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
    uint8_t pin,
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
    uint8_t pin,
    bool inverted) {

    this->pin = pin;
    this->inverted = inverted;
    this->timeout = 0;

    pinInitialize();

    if (service != nullptr)
        service->add(this);
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

bool eos::DigOutput::get() const {

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


void eos::DigOutput::pinInitialize() const {
        
    halGPIOPinSetState(pin, inverted ? true : false);
    halGPIOPinSetModeOutput(pin, false);    
}


bool eos::DigOutput::pinGet() const {
    
    bool p = halGPIOPinGetState(pin);
    return inverted ? !p : p;
}


void eos::DigOutput::pinSet(
    bool state) const {
    
    halGPIOPinSetState(pin, state);
}


void eos::DigOutput::pinToggle() const {

    halGPIOPinToggleState(pin);
}
