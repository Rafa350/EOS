#include "fsmMachine.h"
#include "fsmState.h"
#include "fsmContext.h"


using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
State::State() {
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW1_ON' transition.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* State::onSW1_ON(Machine* machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW2_ON' transition.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* State::onSW2_ON(Machine* machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW3_ON' transition.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* State::onSW3_ON(Machine* machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'TMR1_TIMEOUT' transition.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* State::onTMR1_TIMEOUT(Machine* machine) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
WaitingSW1::WaitingSW1() {
}


/// ----------------------------------------------------------------------
/// \brief    Get a instance of class.
///
WaitingSW1* WaitingSW1::getInstance() {

    if (instance == nullptr)
        instance = new WaitingSW1();
    
    return instance;
}

WaitingSW1* WaitingSW1::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW1_ON' transition to other state.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* WaitingSW1::onSW1_ON(Machine* machine) {

    // Check transition guard.
    //
    if (true) {

        // Transition actions.
        //
        machine->doLED1_ON();

        // Return the next state.
        //
        return WaitingSW2::getInstance();

    }

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
WaitingSW2::WaitingSW2() {
}


/// ----------------------------------------------------------------------
/// \brief    Get a instance of class.
///
WaitingSW2* WaitingSW2::getInstance() {

    if (instance == nullptr)
        instance = new WaitingSW2();
    
    return instance;
}

WaitingSW2* WaitingSW2::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW2_ON' transition to other state.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* WaitingSW2::onSW2_ON(Machine* machine) {

    // Check transition guard.
    //
    if (true) {

        // Transition actions.
        //
        machine->doLED1_OFF();
        machine->doLED2_ON();

        // Return the next state.
        //
        return WaitingSW3::getInstance();

    }

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
WaitingSW3::WaitingSW3() {
}


/// ----------------------------------------------------------------------
/// \brief    Get a instance of class.
///
WaitingSW3* WaitingSW3::getInstance() {

    if (instance == nullptr)
        instance = new WaitingSW3();
    
    return instance;
}

WaitingSW3* WaitingSW3::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW3_ON' transition to other state.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* WaitingSW3::onSW3_ON(Machine* machine) {

    // Check transition guard.
    //
    if (true) {

        // Transition actions.
        //
        machine->doLED2_OFF();
        machine->doLED3_ON();
        machine->doTMR1_START();

        // Return the next state.
        //
        return WaitingTMR1::getInstance();

    }

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
WaitingTMR1::WaitingTMR1() {
}


/// ----------------------------------------------------------------------
/// \brief    Get a instance of class.
///
WaitingTMR1* WaitingTMR1::getInstance() {

    if (instance == nullptr)
        instance = new WaitingTMR1();
    
    return instance;
}

WaitingTMR1* WaitingTMR1::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Perform 'TMR1_TIMEOUT' transition to other state.
/// \param    machine: The state machine.
/// \return   The next state.
///
State* WaitingTMR1::onTMR1_TIMEOUT(Machine* machine) {

    // Check transition guard.
    //
    if (true) {

        // Transition actions.
        //
        machine->doLED3_OFF();

        // Enter state actions.
        //
        machine->doLED1_OFF();

        // Return the next state.
        //
        return WaitingSW1::getInstance();

    }

}


