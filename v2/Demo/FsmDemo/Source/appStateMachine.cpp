#include "eos.h"
#include "appStateMachine.h"
#include "fsmMachine.h"


using namespace eos;
using namespace app;


void Machine::doLED1_ON() {
    
}

void Machine::doLED1_OFF() {
    
}

void Machine::doLED2_ON() {
    
}

void Machine::doLED2_OFF() {
    
}

void Machine::doLED3_ON() {
    
}

void Machine::doLED3_OFF() {
    
}

void Machine::doTMR1_START() {
    
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MyStateMachine::MyStateMachine() :
    machine(nullptr),
    messageQueue(10) {
    
    machine = new Machine(nullptr);
    machine->start();
}


/// ----------------------------------------------------------------------
/// \brief    Accepta un missatge i l'afegeix a la cua.
/// \param    message: El missatge.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool MyStateMachine::acceptMessage(
    Message message,
    unsigned blockTime) {
    
    return messageQueue.put(message, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges pendents en la cua.
///
void MyStateMachine::task() {

    Message message;

    if (messageQueue.get(message, unsigned(-1))) {
       
        switch (message) {
            case Message::pressedSW1:
                machine->onSW1_ON();
                break;
                
            case Message::pressedSW2:
                machine->onSW2_ON();
                break;

            case Message::pressedSW3:
                machine->onSW3_ON();
                break;
        }
    }
    
}