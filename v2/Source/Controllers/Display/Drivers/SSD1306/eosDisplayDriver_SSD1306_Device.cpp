module;


#include "eos.h"


module Eos.Controllers.Display.Drivers.SSD1306;


using namespace eos;


/// ---------------------------------------------------------------------------
/// \brief    Constructor.
///
DisplayDevice_SSD1306::DisplayDevice_SSD1306() {

}


/// ---------------------------------------------------------------------------
/// \brief    Procesa un script
/// \param    script: EL escript.
/// \param    scriptSize: El tmany del script.
///
void DisplayDevice_SSD1306::writeScript(
    const UInt8 *script,
    UInt32 scriptSize) {

    writeCommand(script, scriptSize);
}
