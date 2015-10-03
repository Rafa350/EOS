#include "Services/eosDigInput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"


const unsigned taskStackSize = 512;
const eos::TaskPriority taskPriority = eos::TaskPriority::normal;


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

eos::DigInputService::DigInputService() :
    task(taskStackSize, taskPriority, this) {
}


void eos::DigInputService::add(eos::DigInput *input) {
    
    inputs.add(input);
}


void eos::DigInputService::run() {
    
    unsigned tc = eos::Task::getTickCount();

    while (true) {
        
        eos::Task::delayUntil(10, &tc);
        
        // Explora les entrades per coneixa el seu estat
        //
        eos::Task::enterCriticalSection();

        for (unsigned i = 0; i < inputs.getCount(); i++) {
            
            DigInput *input = inputs[i];
            
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
        }
        
        eos::Task::exitCriticalSection();
        
        // Crida a les funcions callback corresponents
        //
        for (unsigned i = 0; i < inputs.getCount(); i++) {
            
            DigInput *input = inputs[i];
            
            if (input->onPosEdgeFired) 
                input->onPosEdge->execute(input);
            else if (input->onNegEdgeFired) 
                input->onNegEdge->execute(input);
            else if (input->onChangeFired) 
                input->onChange->execute(input);
        }
        
        // Reseteja flags i variables temporals
        //
        eos::Task::enterCriticalSection();

        for (unsigned i = 0; i < inputs.getCount(); i++) {
            
            DigInput *input = inputs[i];
            
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
        }

        eos::Task::exitCriticalSection();
    }    
}


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           eos::DigInput::DigInput(
 *               uint8_t pin, 
 *               bool inverted)
 * 
 *       Entrada:
 *           pin     : Numero e pin
 *           inverted: Indica si la senyal va invertida
 * 
 *************************************************************************/

eos::DigInput::DigInput(
    uint8_t pin, 
    bool inverted):
    eos::DigInput(nullptr, pin, inverted) {
}


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::DigInput::DigInput(
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

eos::DigInput::DigInput(
    eos::DigInputService *service,
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
 *           bool eos::DigInput::isPosEdge()
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eos::DigInput::isPosEdge() {

    eos::Task::enterCriticalSection();
    
    bool result = posEdge;
    posEdge = false;

    eos::Task::exitCriticalSection();

    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           bool eos::DigInput::isNegEdge()
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eos::DigInput::isNegEdge() {

    eos::Task::enterCriticalSection();
    
    bool result = negEdge;
    negEdge = false;

    eos::Task::exitCriticalSection();

    return result;
}


/*************************************************************************
 *
 *       Inicialitza el port d'una entrada
 *
 *       Funcio:
 *           void eos::DigInput::pinInitialize() const
 *
 *************************************************************************/

void eos::DigInput::pinInitialize() const {

    halGPIOPinSetModeInput(pin);
}


/*************************************************************************
 *
 *       Lectura del port d'una entrada
 *
 *       Funcio:
 *           bool eosDigInput::pinGet() const
 * 
 *       Retorn:
 *           Valor lleigit del port
 *
 *************************************************************************/

bool eos::DigInput::pinGet() const {
    
    bool p = halGPIOPinGetState(pin);
    return inverted ? !p : p;
}
