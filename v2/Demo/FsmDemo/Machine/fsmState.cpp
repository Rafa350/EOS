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

    WaitingSW1* WaitingSW1::getInstance() {
        if (instance == null) instance = new WaitingSW1();
        return instance;
    }

    void WaitingSW1::onSW1_ON(
        Context* context) {
    }

    WaitingSW2::WaitingSW2() {
    }

    WaitingSW2* WaitingSW2::getInstance() {
        if (instance == null) instance = new WaitingSW2();
        return instance;
    }

    void WaitingSW2::onSW2_ON(
        Context* context) {
    }

    WaitingSW3::WaitingSW3() {
    }

    WaitingSW3* WaitingSW3::getInstance() {
        if (instance == null) instance = new WaitingSW3();
        return instance;
    }

    void WaitingSW3::onSW3_ON(
        Context* context) {
    }

    WaitingTMR1::WaitingTMR1() {
    }

    WaitingTMR1* WaitingTMR1::getInstance() {
        if (instance == null) instance = new WaitingTMR1();
        return instance;
    }

    void WaitingTMR1::onTMR1_TIMEOUT(
        Context* context) {
    }

}
