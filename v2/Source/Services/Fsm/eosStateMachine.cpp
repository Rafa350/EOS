#include "Services/eosFSM.hpp"


using namespace eos;


StateMachine::StateMachine() {
    
    state = nullptr;
}


void StateMachine::acceptEvent(Event event) {
    
    if (state == nullptr) { 
        state = initialState;
        state->enterAction();
    }

    StateBase *newState = state->transition(event);
    if (newState == nullptr)
        newState = state;

    if (newState != state) {
        state->exitAction();
        newState->enterAction();
        state = newState;
    }
    
}

