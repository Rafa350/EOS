#include "fsmMachine.h"
#include "fsmState.h"
#include "fsmContext.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
State::State(Machine* machine):
    machine(machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'pressedSW1' transition.
///
void State::pressedSW1() {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'pressedSW2' transition.
///
void State::pressedSW2() {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'pressedSW3' transition.
///
void State::pressedSW3() {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'timeoutTMR1' transition.
///
void State::timeoutTMR1() {

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
/// \brief    Perform 'pressedSW1' transition.
///
void WaitingSW1::pressedSW1() {

    IContext* ctx = getContext();
    ctx->setLED1();

    setState(getMachine()->WaitingSW2);
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
/// \brief    Perform 'pressedSW2' transition.
///
void WaitingSW2::pressedSW2() {

    IContext* ctx = getContext();
    ctx->setLED2();

    setState(getMachine()->WaitingSW3);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
WaitingSW3::WaitingSW3(
    Machine* machine):

    State(machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'pressedSW3' transition.
///
void WaitingSW3::pressedSW3() {

    IContext* ctx = getContext();
    ctx->setLED3();
    ctx->startTIMER1(1000);

    setState(getMachine()->WaitingTMR1);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    machine: Pointer the machine.
///
WaitingTMR1::WaitingTMR1(
    Machine* machine):

    State(machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'timeoutTMR1' transition.
///
void WaitingTMR1::timeoutTMR1() {

    IContext* ctx = getContext();
    ctx->clearLED1();
    ctx->clearLED2();
    ctx->clearLED3();

    setState(getMachine()->WaitingSW1);
}


