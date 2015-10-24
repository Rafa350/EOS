#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


LoopSW1State::LoopSW1State(eos::fsm::StateMachine *sm):
    eos::fsm::State(sm) {
}

void LoopSW1State::enterAction() {

}

void LoopSW1State::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case INP_SW1:
            sm->setState(sm->getLoopSW2State());
            break;

    }
}

LoopSW2State::LoopSW2State(eos::fsm::StateMachine *sm):
    eos::fsm::State(sm) {
}

void LoopSW2State::enterAction() {

}

void LoopSW2State::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case INP_SW2:
            sm->setState(sm->getLoopSW3State());
            break;

    }
}

LoopSW3State::LoopSW3State(eos::fsm::StateMachine *sm):
    eos::fsm::State(sm) {
}

void LoopSW3State::enterAction() {

}

void LoopSW3State::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getStateMachine();

    switch (event) {
        case INP_SW3:
            sm->setState(sm->getLoopSW1State());
            break;

    }
}

