#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Device_SSD1306::Device_SSD1306() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa un script
/// \param    script: EL escript.
/// \param    scriptSize: El tmany del script.
///
void Device_SSD1306::writeScript(
    const uint8_t *script,
    unsigned scriptSize) {

    writeCommand(script, scriptSize);
}
