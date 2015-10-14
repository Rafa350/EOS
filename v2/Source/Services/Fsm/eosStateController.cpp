#include "Services/eosFSM.hpp"


using namespace eos::fsm;


StateController::StateController(unsigned size) {
    
    this->stack = new (State*)[size];
    this->size = size;
    this->level = 0;
}


State *StateController::get() const {
    
    return level > 0 ? stack[level - 1] : nullptr;
}


void StateController::set(State* state) {

    if (level > 0)
        stack[level - 1] = state;
}


void StateController::push(State* state) {
    
    if (level < size) {
        level++;
        stack[level - 1] = state;
    }
}


void StateController::pop() {
    
    if (level > 0)
        level--;
}
