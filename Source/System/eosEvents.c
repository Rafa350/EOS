#include "eos.h"


void eosCallEvent(eosEvent *event, void *sender, void *params) {

    if (event->method != NULL)
        event->method(event->target, sender, params);

}
