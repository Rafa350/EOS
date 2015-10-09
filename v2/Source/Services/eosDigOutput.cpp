#include "Services/eosDigOutput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"
#include "FReeRTOS.h"
#include "task.h"


using namespace eos;


#define TASK_PERIOD     10

const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           DigOutputService::DigOutputService()
 *
 *************************************************************************/

DigOutputService::DigOutputService() :
    task(taskStackSize, taskPriority, this) {
}


/*************************************************************************
 *
 *       Afegeig una sortida al servei
 *
 *       Funcio:
 *           void DigOutputService::add(
 *               DigOutput* output) 
 * 
 *       Entrada:
 *           output: La sortida a afeigit
 *
 *************************************************************************/

void DigOutputService::add(
    DigOutput* output) {
    
    Task::enterCriticalSection();
    outputs.add(output);
    Task::exitCriticalSection();
}


/*************************************************************************
 *
 *       Executa la tasca de control de servei
 * 
 *       Funcio:
 *           void DigOutputService::run() 
 *
 *************************************************************************/

void DigOutputService::run() {
    
    unsigned tc = Task::getTickCount();

    while (true) {

        Task::delayUntil(TASK_PERIOD, &tc);
        
        Task::enterCriticalSection();
        
        for (unsigned i = 0; i < outputs.getCount(); i++) {          
            
            DigOutput *output = outputs[i];
    
            unsigned t = output->timeout;
            if (t > 0) {
                t -= 1;
                if (t == 0)
                    output->pinToggle();
                output->timeout = t;
            }       
        }

        Task::exitCriticalSection();
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

DigOutput::DigOutput(
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
 *               DigOutputService *service,
 *               unsigned pin,
 *               bool inverted)
 *
 *       Entrada:
 *           service : El servei
 *           pin     : Numero de pin hardware
 *           inverted: True si treballa amb logica negativa
 *
 *************************************************************************/

DigOutput::DigOutput(
    DigOutputService *service,
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
 *           bool DigOutput::get()
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

bool DigOutput::get() const {

    return pinGet();
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           void DigOutput::set(
 *               bool state)
 *
 *       Entrada:
 *           state  : L'estat a signar
 *
 *************************************************************************/

void DigOutput::set(
    bool state) {

    Task::enterCriticalSection();
    
    pinSet(state);
    timeout = 0;
    
    Task::exitCriticalSection();
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void DigOutput::toggle()
 *
 *************************************************************************/

void DigOutput::toggle() {

    Task::enterCriticalSection();
    
    pinToggle();
    timeout = 0;
    
    Task::exitCriticalSection();
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida. La resolucio
 *       es en multiples de TASK_PERIOD
 *
 *       Funcio:
 *           void DigOutput::pulse(
 *               unsigned time)
 *
 *       Entrada:
 *           time   : Duracio del puls
 * 
 *       Notes:
 *           Si encara esta en un puls, unicament l'allarga
 *
 *************************************************************************/

void DigOutput::pulse(
    unsigned time) {

    if (time >= TASK_PERIOD) {

        Task::enterCriticalSection();
        
        if (timeout == 0)
            pinToggle();
        timeout = time / TASK_PERIOD;
        
        Task::exitCriticalSection();
    }
}


void DigOutput::pinInitialize() const {
        
    halGPIOPinSetState(pin, inverted ? true : false);
    halGPIOPinSetModeOutput(pin, false);    
}


bool DigOutput::pinGet() const {
    
    bool p = halGPIOPinGetState(pin);
    return inverted ? !p : p;
}


void DigOutput::pinSet(
    bool state) const {
    
    halGPIOPinSetState(pin, state);
}


void DigOutput::pinToggle() const {

    halGPIOPinToggleState(pin);
}
