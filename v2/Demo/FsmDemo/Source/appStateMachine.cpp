#include "eos.h"
#include "appStateMachine.h"
#include "MachineContext.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
MyStateMachine::MyStateMachine() :
    context(nullptr),
    messageQueue(10) {
    
    context = new Context(this);
    context->start();
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
                context->transition_SW1Pressed();
                break;
                
            case Message::pressedSW2:
                context->transition_SW2Pressed();
                break;

            case Message::pressedSW3:
                context->transition_SW3Pressed();
                break;
        }
    }
    
}


void  MyStateMachine::doLED1On() {
    
}


void  MyStateMachine::doLED2On() {
    
}


void  MyStateMachine::doLED3On() {
    
}


void  MyStateMachine::doLED1Off() {
    
}


void  MyStateMachine::doLED2Off() {
    
}


void  MyStateMachine::doLED3Off() {
    
}
