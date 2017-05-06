#include "eos.h"

// Harmony
#include "peripheral/int/plib_int.h"


bool eosInterruptDisable(void) {
    
    bool enabled = PLIB_INT_IsEnabled(INT_ID_0);
    if (enabled)
        PLIB_INT_Disable(INT_ID_0);
    return enabled;
}


bool eosInterruptSourceDisable(INT_SOURCE source) {
    
    INT_STATE_GLOBAL state = PLIB_INT_GetStateAndDisable(INT_ID_0);
    
    bool enabled = PLIB_INT_SourceIsEnabled(INT_ID_0, source);
    if (enabled)
        PLIB_INT_SourceDisable(INT_ID_0, source);
    
    PLIB_INT_SetState(INT_ID_0, state);
    
    return enabled;
}
