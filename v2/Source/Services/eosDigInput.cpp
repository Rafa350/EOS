#include "Services/eosDigInput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"



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
    task(512, eos::TaskPriority::normal, this) {
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
                //if (input->onPosEdge != NULL) 
                //    input->onPosEdgeFired = true;
                //else if (input->onChange != NULL) 
                //    input->onChangeFired = true;
            }
            else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                input->state = false;
                input->negEdge = true;
                //if (input->onNegEdge != NULL) 
                //    input->onNegEdgeFired = true;
                //else if (input->onChange != NULL) 
                //    input->onChangeFired = true;
            }
        }
        
        eos::Task::exitCriticalSection();
        
        // Crida a les funcions callback corresponents
        //
        for (unsigned i = 0; i < inputs.getCount(); i++) {
            
            DigInput *input = inputs[i];
            
            /*if (input->onPosEdgeFired) 
                input->onPosEdge(input, input->context);
            else if (input->onNegEdgeFired) 
                input->onNegEdge(input, input->context);
            else if (input->onChangeFired) 
                input->onChange(input, input->context);*/
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
    /*    hInput->onPosEdge = params->onPosEdge;
        hInput->onNegEdge = params->onNegEdge;
        hInput->onChange = params->onChange;*/
    onPosEdgeFired = false;
    onNegEdgeFired = false;
    onChangeFired = false;   

    pinInitialize();
    state = pinGet();
    pattern = state ? 0xFFFFFFFF : 0x00000000;
    
    if (service != nullptr)
        service->add(this);
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           bool eos::DigInput::get()
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

bool eos::DigInput::get() {
    
    return state;
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
 *           void eos::DigInput::pinInitialize()
 *
 *************************************************************************/

void eos::DigInput::pinInitialize() {

    halGPIOPinSetModeInput(pin);
}


/*************************************************************************
 *
 *       Lectura del port d'una entrada
 *
 *       Funcio:
 *           bool eosDigInput::pinGet()
 * 
 *       Retorn:
 *           Valor lleigit del port
 *
 *************************************************************************/

bool eos::DigInput::pinGet() {
    
    bool p = halGPIOPinGetState(pin);
    return inverted ? !p : p;
}
