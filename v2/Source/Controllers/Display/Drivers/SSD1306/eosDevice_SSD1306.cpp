#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Procesa un script
/// \param    script: EL escript.
/// \param    scriptSize: El tmany del script.
///
void SSD1306_Device::writeScript(
    const uint8_t *script,
    uint16_t scriptSize) {

    for (decltype(scriptSize) i = 0; i < scriptSize; i++)
        writeCommand(script[i]);
}
