#include "fsmMachine.h"
#include "fsmState.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
State::State(Machine* machine):
    machine(machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'sw1_pressed' transition.
///
void State::sw1_pressed() {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'sw2_pressed' transition.
///
void State::sw2_pressed() {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'sw3_pressed' transition.
///
void State::sw3_pressed() {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'timer1_timeout' transition.
///
void State::timer1_timeout() {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
WaitingSW1::WaitingSW1(
    Machine* machine):

    State(machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'enter' action.
///
void WaitingSW1::enter() {

}


void WaitingSW1::transition(unsigned eventId) {

    switch (eventId) {

        case EV_pressedSW1:
            setState(ST_WaitingSW2);
            break;
    }
}

/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
WaitingSW2::WaitingSW2(
    Machine* machine):

    State(machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'enter' action.
///
void WaitingSW2::enter() {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'exit' action.
///
void WaitingSW2::exit() {

}


void WaitingSW2::transition(unsigned eventId) {

    switch (eventId) {

        case EV_pressedSW2:
            if (p == 34) {
                setState(ST_WaitingSW3);
            }
            break;

        case EV_pressedSW2:
            if (p == 345) {
                setState(ST_WaitingSW3);
            }
            break;
    }
}

/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
WaitingSW3::WaitingSW3(
    Machine* machine):

    State(machine) {

}


void WaitingSW3::transition(unsigned eventId) {

    switch (eventId) {

        case EV_pressedSW3:
            setState(ST_WaitingTimer1);
            break;
    }
}

/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
WaitingTimer1::WaitingTimer1(
    Machine* machine):

    State(machine) {

}


void WaitingTimer1::transition(unsigned eventId) {

    switch (eventId) {

        case EV_timeoutTIMER1:
            setState(ST_WaitingSW1);
            break;
    }
}

