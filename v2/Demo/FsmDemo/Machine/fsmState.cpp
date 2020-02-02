#include "fsmContext.h"
#include "fsmState.h"


namespace eos {

    State::State() {
    }

    void State::onSW1_ON(
        Context* context) {
    }

    void State::onSW2_ON(
        Context* context) {
    }

    void State::onSW3_ON(
        Context* context) {
    }

    void State::onTMR1_TIMEOUT(
        Context* context) {
    }

    WaitingSW1* WaitingSW1::instance = nullptr;

    WaitingSW1::WaitingSW1() {
    }

    WaitingSW1* WaitingSW1::getInstance() {
        if (instance == nullptr) instance = new WaitingSW1();
        return instance;
    }

    void WaitingSW1::onSW1_ON(
        Context* context) {
        if (true) {
            context->doLED1_ON();
            context->setState(WaitingSW2::getInstance());
        }
    }

    WaitingSW2* WaitingSW2::instance = nullptr;

    WaitingSW2::WaitingSW2() {
    }

    WaitingSW2* WaitingSW2::getInstance() {
        if (instance == nullptr) instance = new WaitingSW2();
        return instance;
    }

    void WaitingSW2::onSW2_ON(
        Context* context) {
        if (true) {
            context->doLED1_OFF();
            context->doLED2_ON();
            context->setState(WaitingSW3::getInstance());
        }
    }

    WaitingSW3* WaitingSW3::instance = nullptr;

    WaitingSW3::WaitingSW3() {
    }

    WaitingSW3* WaitingSW3::getInstance() {
        if (instance == nullptr) instance = new WaitingSW3();
        return instance;
    }

    void WaitingSW3::onSW3_ON(
        Context* context) {
        if (true) {
            context->doLED2_OFF();
            context->doLED3_ON();
            context->doTMR1_START();
            context->setState(WaitingTMR1::getInstance());
        }
    }

    WaitingTMR1* WaitingTMR1::instance = nullptr;

    WaitingTMR1::WaitingTMR1() {
    }

    WaitingTMR1* WaitingTMR1::getInstance() {
        if (instance == nullptr) instance = new WaitingTMR1();
        return instance;
    }

    void WaitingTMR1::onTMR1_TIMEOUT(
        Context* context) {
        if (true) {
            context->doLED3_OFF();
            context->setState(WaitingSW1::getInstance());
        }
    }

}
