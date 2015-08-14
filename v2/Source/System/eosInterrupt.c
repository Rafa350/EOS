#include "eos.h"
#include "peripheral/int/plib_int.h"


bool eosInterruptDisable(void) {
    
    bool enabled = PLIB_INT_IsEnabled(INT_ID_0);
    if (enabled)
        PLIB_INT_Disable(INT_ID_0);
    return enabled;
}


bool eosInterruptSourceDisable(INT_SOURCE source) {
    
    bool enabled = PLIB_INT_SourceIsEnabled(INT_ID_0, source);
    if (enabled)
        PLIB_INT_SourceDisable(INT_ID_0, source);
    return enabled;
}
