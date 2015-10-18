#include "Services/eosDigInput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"
#include "System/eosList.hpp"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = eos::TaskPriority::normal;


#define PATTERN_ON       0x0000007F
#define PATTERN_OFF      0x00000080
#define PATTERN_MASK     0x000000FF


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::DigInputService::DigInputService()
 *
 *************************************************************************/

DigInputService::DigInputService() :
    task(taskStackSize, taskPriority, this) {
}


void DigInputService::add(eos::DigInput *input) {
    
    inputs.add(input);
}


void DigInputService::run() {
    
    unsigned tc = eos::Task::getTickCount();

    while (true) {
        
        Task::delayUntil(10, &tc);
        
        // Explora les entrades per coneixa el seu estat
        //
        Task::enterCriticalSection();

        DigInputListIterator iterator(inputs);
        while (!iterator.isEnd()) {
            
            DigInput *input = iterator.current();
            
            input->pattern <<= 1;
            if (input->pinGet())
                input->pattern |= 1;

            if ((input->pattern & PATTERN_MASK) == PATTERN_ON) {
                input->state = true;
                input->posEdge = true;
                if (input->onPosEdge != nullptr) 
                    input->onPosEdgeFired = true;
                else if (input->onChange != nullptr) 
                    input->onChangeFired = true;
            }
            else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                input->state = false;
                input->negEdge = true;
                if (input->onNegEdge != nullptr) 
                    input->onNegEdgeFired = true;
                else if (input->onChange != nullptr) 
                    input->onChangeFired = true;
            }
            
            ++iterator;
        }
        
        Task::exitCriticalSection();
        
        // Crida a les funcions callback corresponents
        //
        iterator.reset();
        while (!iterator.isEnd()) {
            
            DigInput *input = iterator.current();
            
            if (input->onPosEdgeFired) 
                input->onPosEdge->execute(input);
            else if (input->onNegEdgeFired) 
                input->onNegEdge->execute(input);
            else if (input->onChangeFired) 
                input->onChange->execute(input);
            
            ++iterator;
        }
        
        // Reseteja flags i variables temporals
        //
        Task::enterCriticalSection();

        iterator.reset();
        while (!iterator.isEnd()) {
            
            DigInput *input = iterator.current();
            
            if (input->onPosEdgeFired) {
                input->onPosEdgeFired = false;
                input->posEdge = false;
            }
            if (input->onNegEdgeFired) {
                input->onNegEdgeFired = false;
                input->negEdge = false;
            }
            if (input->onChangeFired) {
                input->onChangeFired = false;
                input->posEdge = false;
            }           
            
            ++iterator;
        }

        eos::Task::exitCriticalSection();
    }    
}


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           DigInput::DigInput(
 *               uint8_t pin, 
 *               bool inverted)
 * 
 *       Entrada:
 *           pin     : Numero e pin
 *           inverted: Indica si la senyal va invertida
 * 
 *************************************************************************/

DigInput::DigInput(
    uint8_t pin, 
    bool inverted):
    DigInput(nullptr, pin, inverted) {
}


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           DigInput::DigInput(
 *               eos::DigInputService *service,
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

    posEdge = false;
    negEdge = false;
    onPosEdgeFired = false;
    onNegEdgeFired = false;
    onChangeFired = false;   
    onPosEdge = nullptr;
    onNegEdge = nullptr;
    onChange = nullptr;

    pinInitialize();
    state = pinGet();
    pattern = state ? 0xFFFFFFFF : 0x00000000;
    
    if (service != nullptr)
        service->add(this);
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           bool DigInput::isPosEdge()
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool DigInput::isPosEdge() {

    Task::enterCriticalSection();
    
    bool result = posEdge;
    posEdge = false;

    Task::exitCriticalSection();

    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           bool DigInput::isNegEdge()
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool DigInput::isNegEdge() {

    Task::enterCriticalSection();
    
    bool result = negEdge;
    negEdge = false;

    Task::exitCriticalSection();

    return result;
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
