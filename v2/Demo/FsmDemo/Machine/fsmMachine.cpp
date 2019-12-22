#include "fsmMachine.h"
#include "fsmState.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    context: Pointer to context data.
///
Machine::Machine(
    IContext* context):

    state(nullptr),
    stateWaitingSW1(new WaitingSW1(this)),
    stateWaitingSW2(new WaitingSW2(this)),
    stateWaitingSW3(new WaitingSW3(this)),
    stateWaitingTimer1(new WaitingTimer1(this)),
    context(context) {

}


/// ----------------------------------------------------------------------
/// \brief    Set to initial state.
///
void Machine::start() {

    state = stateWaitingSW1;
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'sw1_pressed' transition.
///
void Machine::sw1_pressed() {

    state->sw1_pressed();
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'sw2_pressed' transition.
///
void Machine::sw2_pressed() {

    state->sw2_pressed();
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'sw3_pressed' transition.
///
void Machine::sw3_pressed() {

    state->sw3_pressed();
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'timer1_timeout' transition.
///
void Machine::timer1_timeout() {

    state->timer1_timeout();
}


