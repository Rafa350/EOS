#include "fsmMachine.h"
#include "fsmState.h"


State::State(Machine* machine):
    machine(machine) {
}

WaitSW1State::WaitSW1State(Machine* machine):
    State(machine) {
}

void WaitSW1State::enter() {

}

void WaitSW1State::transition(unsigned eventId) {

    switch (eventId) {

        case EV_SW1:
            setState(ST_WaitSW2);
            break;
    }
}

WaitSW2State::WaitSW2State(Machine* machine):
    State(machine) {
}

void WaitSW2State::enter() {

}

void WaitSW2State::exit() {

}

void WaitSW2State::transition(unsigned eventId) {

    switch (eventId) {

        case EV_SW2:
            if (p == 34) {
                setState(ST_WaitSW3);
            }
            break;

        case EV_SW2:
            if (p == 345) {
                setState(ST_WaitSW3);
            }
            break;
    }
}

WaitSW3State::WaitSW3State(Machine* machine):
    State(machine) {
}

void WaitSW3State::transition(unsigned eventId) {

    switch (eventId) {

        case EV_SW3:
            setState(ST_WaitTimer1);
            break;
    }
}

WaitTimer1State::WaitTimer1State(Machine* machine):
    State(machine) {
}

void WaitTimer1State::transition(unsigned eventId) {

    switch (eventId) {

        case EV_TIMER1:
            setState(ST_WaitSW1);
            break;
    }
}

