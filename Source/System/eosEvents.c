#include "eos.h"


void eosThrowEvent(eosEvent *event, void *params) {

    if (event && event->method)
        event->method(event->target, params);
}
