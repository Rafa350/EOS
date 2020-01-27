#include "eos.h"
#include "appStateMachine.h"
#include "fsmMachine.h"



using namespace eos;
using namespace app;


MyStateMachine::MyStateMachine() :
    machine(new Machine(nullptr)) {
    
}


void MyStateMachine::accept(
    Event event) {
    
    State* state = machine->getState();
    
    switch (event) {
        case Event::prossedSW1:
            state->onSW1_ON(machine);
            break;
    }
}