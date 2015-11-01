#include "Services/eosDigInput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


#define PATTERN_ON       0x0000007F
#define PATTERN_OFF      0x00000080
#define PATTERN_MASK     0x000000FF


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           DigInputService::DigInputService()
 *
 *************************************************************************/

DigInputService::DigInputService() :
    task(taskStackSize, taskPriority, this) {
}


/*************************************************************************
 *
 *       Afegeix una entrada
 * 
 *       Funcio:
 *           void DigInputService::add(
 *              DigInput *input) 
 * 
 *       Entrada:
 *           input: L'entrada a afeigir
 *
 *************************************************************************/

void DigInputService::add(
    DigInput *input) {

    inputs.add(input);
}


/*************************************************************************
 *
 *       Tasca de control del servei
 * 
 *       Funcio:
 *           void DigInputService::run() 
 *
 *************************************************************************/

void DigInputService::run() {
    
    unsigned tc = Task::getTickCount();

    while (true) {
        
        Task::delayUntil(10, &tc);
        
        DigInputListIterator iterator(inputs);
        while (!iterator.isEnd()) {
            
            DigInput *input = iterator.current();
            bool changed = false;
            
            input->pattern <<= 1;
            if (input->pinGet())
                input->pattern |= 1;

            if ((input->pattern & PATTERN_MASK) == PATTERN_ON) {
                changed = true;
                input->state = true;
            }
            else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                changed = true;
                input->state = false;
            }
            
            if (changed && (input->onChange != nullptr)) 
                input->onChange->execute(input);
            
            ++iterator;
        }
    }    
}


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           DigInput::DigInput(
 *               DigInputService *service,
 *               uint8_t pin, 
 *               bool inverted)
 *
 *       Entrada:
 *           service : El servei
 *           pin     : El numero de pin
 *           inverted: Indica si la senyal va invertida
 *
 *************************************************************************/

DigInput::DigInput(
    DigInputService *service,
    uint8_t pin, 
    bool inverted) {
    
    this->pin = pin;
    this->inverted = inverted;

    onChange = nullptr;

    pinInitialize();
    state = pinGet();
    pattern = state ? 0xFFFFFFFF : 0x00000000;
    
    service->add(this);
}


/*************************************************************************
 *
 *       Inicialitza el port d'una entrada
 *
 *       Funcio:
 *           void DigInput::pinInitialize() const
 *
 *************************************************************************/

void DigInput::pinInitialize() const {

    halGPIOPinSetModeInput(pin);
}


/*************************************************************************
 *
 *       Lectura del port d'una entrada
 *
 *       Funcio:
 *           bool DigInput::pinGet() const
 * 
 *       Retorn:
 *           Valor lleigit del port
 *
 *************************************************************************/

bool DigInput::pinGet() const {
    
    bool p = halGPIOPinGetState(pin);
    return inverted ? !p : p;
}
