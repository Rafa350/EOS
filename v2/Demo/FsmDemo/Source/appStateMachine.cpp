#include "eos.h"
#include "appStateMachine.h"



using namespace eos;
using namespace app;


MyStateMachine::MyStateMachine() :
    machine(nullptr) {
    
    machine.start();
}


void MyStateMachine::accept(
    Event event) {
    
    switch (event) {
        case Event::prossedSW1:
            machine.pressedSW1();
            break;
    }
}