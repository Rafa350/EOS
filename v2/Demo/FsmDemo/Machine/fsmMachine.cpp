#include "fsmMachine.h"
#include "fsmState.h"


Machine::Machine(IContext* context) {

    states[ST_WaitSW1] = new WaitSW1State(this);
    states[ST_WaitSW2] = new WaitSW2State(this);
    states[ST_WaitSW3] = new WaitSW3State(this);
    states[ST_WaitTimer1] = new WaitTimer1State(this);

    start(states[ST_WaitSW1]);
}
