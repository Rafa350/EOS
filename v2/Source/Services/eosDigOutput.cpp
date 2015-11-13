#include "Services/eosDigOutput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"
#include "System/eosQueue.hpp"


using namespace eos;


const unsigned taskStackSize = 512;
const unsigned commandQueueSize = 10;
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
    task(taskStackSize, taskPriority, this),
    commandQueue(commandQueueSize) {
}


/*************************************************************************
 *
 *       Afegeig una sortida al servei
 *
 *       Funcio:
 *           void DigOutputService::add(
 *               DigOutputHandle output) 
 * 
 *       Entrada:
 *           output: La sortida a afeigit
 *
 *************************************************************************/

void DigOutputService::add(
    DigOutputHandle output) {
    
    outputs.add(output);
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
    
    Command command;

    while (true) {
        while (commandQueue.get(command, (unsigned) -1)) {
            switch (command.action) {
                case Action::clear:
                    doClearAction(command.output);
                    break;
                    
                case Action::set:
                    doSetAction(command.output);
                    break;
                    
                case Action::toggle:
                    doToggleAction(command.output);
                    break;
                    
                case Action::pulse: 
                    doPulseAction(command.output, command.time);
                    break;
            }
        }
    }
}


/*************************************************************************
 *
 *       Procesa l'accio 'clear'
 * 
 *       Funcio:
 *           void DigOutputService::doClearAction(
 *               DigOutputHandle output) 
 * 
 *       Entrada:
 *           output: La sortida
 *
 *************************************************************************/

void DigOutputService::doClearAction(
    DigOutputHandle output) {

    if (output->timer != nullptr) 
        output->timer->stop(1000);
    
    halGPIOPinSetState(output->pin, output->inverted);    
}


/*************************************************************************
 *
 *       Procesa l'accio 'set'
 * 
 *       Funcio:
 *           void DigOutputService::doSetAction(
 *               DigOutputHandle output) 
 * 
 *       Entrada:
 *           output: La sortida
 *
 *************************************************************************/

void DigOutputService::doSetAction(DigOutputHandle output) {

    if (output->timer != nullptr) 
        output->timer->stop(1000);

    halGPIOPinSetState(output->pin, !output->inverted);    
}


/*************************************************************************
 *
 *       Procesa l'accio 'toggle'
 * 
 *       Funcio:
 *           void DigOutputService::doToggleAction(
 *               DigOutputHandle output) 
 * 
 *       Entrada:
 *           output: La sortida
 *
 *************************************************************************/

void DigOutputService::doToggleAction(DigOutputHandle output) {

    if (output->timer != nullptr) 
        output->timer->stop(1000);

    halGPIOPinToggleState(output->pin);    
}


/*************************************************************************
 *
 *       Procesa l'accio 'pulse'
 * 
 *       Funcio:
 *           void DigOutputService::doPulseAction(
 *               DigOutputHandle output,
 *               unsigned time) 
 * 
 *       Entrada:
 *           output: La sortida
 *           time  : La durada del puls
 *
 *************************************************************************/

void DigOutputService::doPulseAction(
    DigOutputHandle output, 
    unsigned time) {

    if (output->timer == nullptr) {
        output->timer = new Timer();
        output->timer->setOnTimeout(EV_Timer_onTimeout(DigOutputService, this, &DigOutputService::onTimeout));
        output->timer->setTag(output);
    }
    if (!output->timer->isActive())
        halGPIOPinToggleState(output->pin);
    output->timer->start(time, 0);   
}


/*************************************************************************
 *
 *       Procesa el timeout del temporitzador pels pulsos
 * 
 *       Funcio:
 *           void DigOutputService::onTimeout(
 *               TimerHandle timer) 
 *
 *       Entrada:
 *           timer: El temporitzador
 *
 *************************************************************************/

void DigOutputService::onTimeout(
    TimerHandle timer) {
    
    DigOutputHandle output = (DigOutputHandle) timer->getTag();
    halGPIOPinToggleState(output->pin);
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           void DigOutputService::outputSet(
 *               DigOutputHandle output,
 *               bool state)
 *
 *       Entrada:
 *           output: La sortida
 *           state : L'estat a signar
 *
 *************************************************************************/

void DigOutputService::outputSet(
    DigOutputHandle output,
    bool state) {
    
    Command command;
    command.action = state ? Action::set : Action::clear;
    command.output = output;
    commandQueue.put(command, 100);
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void DigOutputService::toggle(
 *               DigOutput output)
 * 
 *       Entrada:
 *           output: La sortida
 *
 *************************************************************************/

void DigOutputService::outputToggle(
    DigOutputHandle output) {

    Command command;
    command.action = Action::toggle;
    command.output = output;
    commandQueue.put(command, 100);
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida en un puls
 *
 *       Funcio:
 *           void DigOutputService::pulse(
 *               DigOutput output,
 *               unsigned time)
 * 
 *       Entrada:
 *           output: La sortida
 *           time  : La durada del puls
 *
 *************************************************************************/

void DigOutputService::outputPulse(
    DigOutputHandle output,
    unsigned time) {
    
    Command command;
    command.action = Action::pulse;
    command.output = output;
    command.time = time;
    commandQueue.put(command, 100);
}


/*************************************************************************
 *
 *       Constructor      
 *  
 *       Funcio:
 *           DigOutput::DigOutput(
 *               DigOutputServiceHandle service,
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
    DigOutputServiceHandle service,
    uint8_t pin,
    bool inverted) {

    this->service = service;
    this->pin = pin;
    this->inverted = inverted;
    this->timer = nullptr;

    halGPIOPinSetState(pin, inverted);
    halGPIOPinSetModeOutput(pin, false);    

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

    bool state = halGPIOPinGetState(pin);
    return inverted ? !state : state;
}
