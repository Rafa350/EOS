module;


#include "eos.h"


module Eos.Controllers.Display.Drivers.SSD1306;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::DisplayDevice_SSD1306::DisplayDevice_SSD1306() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa un script
/// \param    script: EL escript.
/// \param    scriptSize: El tmany del script.
///
void eos::DisplayDevice_SSD1306::writeScript(
    const uint8_t *script,
    size_t scriptSize) {

    writeCommand(script, scriptSize);
}
