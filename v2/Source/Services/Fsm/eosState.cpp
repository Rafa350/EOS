#include "eos.h"
#include "Services/Fsm/eosStateMachine.h"


using namespace eos;


State::State(
    StateMachine *sm) {

    this->sm = sm;
}


void State::enterAction() {

}

void State::exitAction() {

}


void State::transition(
    Event event) {

}


void State::setState(
    State *state) {

    sm->setState(state);
}


void State::pushState(
    State *state) {

    sm->pushState(state);
}


void State::popState() {

    sm->popState();
}
