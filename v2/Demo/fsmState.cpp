#include "Services/eosFSM.hpp"
#include "fsmDefines.hpp"
#include "fsmMachine.hpp"
#include "fsmStates.hpp"


void LoopSW1State::enterAction() {

}

void LoopSW1State::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getMachine();

    switch (event) {
        case INP_SW1:
            setState(sm->getLoopSW2State());
            break;

    }
}

void LoopSW2State::enterAction() {

}

void LoopSW2State::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getMachine();

    switch (event) {
        case INP_SW2:
            setState(sm->getLoopSW3State());
            break;

    }
}

void LoopSW3State::enterAction() {

}

void LoopSW3State::transition(eos::fsm::Event event) {

    MyMachine *sm = (MyMachine*) getMachine();

    switch (event) {
        case INP_SW3:
            setState(sm->getLoopSW1State());
            break;

    }
}



#endif
