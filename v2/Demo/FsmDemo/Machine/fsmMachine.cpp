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
    context(context) {
}


/// ----------------------------------------------------------------------
/// \brief    Set to initial state.
///
void Machine::start() {

    // Machine initialization actions.
    //
    doLED1_OFF();
    doLED2_OFF();
    doLED3_OFF();

    // Enter state actions.
    //
    doLED1_OFF();

    // Select initial state.
    //
    state = WaitingSW1::getInstance();
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW1_ON' transition.
///
void Machine::onSW1_ON() {

    state = state->onSW1_ON(this);
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW2_ON' transition.
///
void Machine::onSW2_ON() {

    state = state->onSW2_ON(this);
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW3_ON' transition.
///
void Machine::onSW3_ON() {

    state = state->onSW3_ON(this);
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'TMR1_TIMEOUT' transition.
///
void Machine::onTMR1_TIMEOUT() {

    state = state->onTMR1_TIMEOUT(this);
}


