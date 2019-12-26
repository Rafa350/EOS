#include "fsmMachine.h"
#include "fsmState.h"


using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    context: Pointer to context data.
///
Machine::Machine(
    Context* context):

    state(nullptr),
    stateWaitingSW1(new WaitingSW1(this)),
    stateWaitingSW2(new WaitingSW2(this)),
    stateWaitingSW3(new WaitingSW3(this)),
    stateWaitingTMR1(new WaitingTMR1(this)),
    context(context) {
}


/// ----------------------------------------------------------------------
/// \brief    Set to initial state.
///
void Machine::start() {

    state = stateWaitingSW1;
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'pressedSW1' transition.
///
void Machine::pressedSW1() {

    state->pressedSW1();
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'pressedSW2' transition.
///
void Machine::pressedSW2() {

    state->pressedSW2();
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'pressedSW3' transition.
///
void Machine::pressedSW3() {

    state->pressedSW3();
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'timeoutTMR1' transition.
///
void Machine::timeoutTMR1() {

    state->timeoutTMR1();
}


