#include "eos.h"
#include "HAL/PIC32/halINT.h"

#include "peripheral/int/plib_int.h"


/// ----------------------------------------------------------------------
/// \brief    Active les interrupcions.
///
void halINTEnable() {
    
    PLIB_INT_Enable(INT_ID_0);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcions.
/// \return   El estat per restaurar lers interrupcions.
///
unsigned halINTDisable() {

    return PLIB_INT_GetStateAndDisable(INT_ID_0);
}


/// ----------------------------------------------------------------------
/// \brief    Restaura les interrupcions.
/// \param    state: L'estat per restaurar.
///
void halINTRestore(unsigned state) {
    
    PLIB_INT_SetState(INT_ID_0, state);
}
