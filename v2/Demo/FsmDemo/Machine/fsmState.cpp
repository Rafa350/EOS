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

    WaitingSW1::WaitingSW1() {

    }

    WaitingSW1* WaitingSW1::instance = nullptr;

    WaitingSW1* WaitingSW1::getInstance() {

    }

    void WaitingSW1::onSW1_ON(
        Context* context) {

    }

    WaitingSW2::WaitingSW2() {

    }

    WaitingSW2* WaitingSW2::instance = nullptr;

    WaitingSW2* WaitingSW2::getInstance() {

    }

    void WaitingSW2::onSW2_ON(
        Context* context) {

    }

    WaitingSW3::WaitingSW3() {

    }

    WaitingSW3* WaitingSW3::instance = nullptr;

    WaitingSW3* WaitingSW3::getInstance() {

    }

    void WaitingSW3::onSW3_ON(
        Context* context) {

    }

    WaitingTMR1::WaitingTMR1() {

    }

    WaitingTMR1* WaitingTMR1::instance = nullptr;

    WaitingTMR1* WaitingTMR1::getInstance() {

    }

    void WaitingTMR1::onTMR1_TIMEOUT(
        Context* context) {

    }

}
