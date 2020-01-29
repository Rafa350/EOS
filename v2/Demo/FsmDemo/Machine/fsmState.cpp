#include "fsmContext.h"
#include "fsmState.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
State::State() {
}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW1_ON' transition.
/// \param    context: The context.
///
void State::onSW1_ON(Context* context) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW2_ON' transition.
/// \param    context: The context.
///
void State::onSW2_ON(Context* context) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'SW3_ON' transition.
/// \param    context: The context.
///
void State::onSW3_ON(Context* context) {

}


/// ----------------------------------------------------------------------
/// \brief    Perform 'TMR1_TIMEOUT' transition.
/// \param    context: The context.
///
void State::onTMR1_TIMEOUT(Context* context) {

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
/// \param    context: The context.
///
void WaitingSW1::onSW1_ON(Context* context) {

    // Check transition guard.
    //
    if (true) {

        // Exit state action.
        //
        context->doLED1_ON();

        // Transition action.
        //
        context->doLED1_ON();

        // Enter state action.
        //
        context->doLED3_ON();

        // Set the next state.
        //
        context->setState(WaitingSW2::getInstance());

        return;
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
/// \param    context: The context.
///
void WaitingSW2::onSW2_ON(Context* context) {

    // Check transition guard.
    //
    if (true) {

        // Transition action.
        //
        context->doLED1_OFF();
        context->doLED2_ON();

        // Set the next state.
        //
        context->setState(WaitingSW3::getInstance());

        return;
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
/// \param    context: The context.
///
void WaitingSW3::onSW3_ON(Context* context) {

    // Check transition guard.
    //
    if (true) {

        // Transition action.
        //
        context->doLED2_OFF();
        context->doLED3_ON();
        context->doTMR1_START();

        // Set the next state.
        //
        context->setState(WaitingTMR1::getInstance());

        return;
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
/// \param    context: The context.
///
void WaitingTMR1::onTMR1_TIMEOUT(Context* context) {

    // Check transition guard.
    //
    if (true) {

        // Transition action.
        //
        context->doLED3_OFF();

        // Enter state action.
        //
        context->doLED1_OFF();

        // Set the next state.
        //
        context->setState(WaitingSW1::getInstance());

        return;
    }

}


