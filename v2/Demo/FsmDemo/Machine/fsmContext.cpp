#include "fsmContext.h"
#include "fsmState.h"


namespace eos {

    Context::Context() {
    }

    void Context::start() {
        doLED1_OFF();
        doLED2_OFF();
        doLED3_OFF();
        doLED1_OFF();
        setState(WaitingSW1::getInstance());
    }

    void Context::end() {
    }

    void Context::onSW1_ON() {
        static_cast<State*>(getState())->onSW1_ON(this);
    }

    void Context::onSW2_ON() {
        static_cast<State*>(getState())->onSW2_ON(this);
    }

    void Context::onSW3_ON() {
        static_cast<State*>(getState())->onSW3_ON(this);
    }

    void Context::onTMR1_TIMEOUT() {
        static_cast<State*>(getState())->onTMR1_TIMEOUT(this);
    }

    void Context::doLED1_ON() {
    }

    void Context::doLED1_OFF() {
    }

    void Context::doLED2_ON() {
    }

    void Context::doLED3_ON() {
    }

    void Context::doLED2_OFF() {
    }

    void Context::doTMR1_START() {
    }

    void Context::doLED3_OFF() {
    }

}
