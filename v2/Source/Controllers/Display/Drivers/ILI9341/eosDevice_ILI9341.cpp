#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Device_ILI9341::Device_ILI9341() {

}


/// ----------------------------------------------------------------------
/// \brief    Execute el script d'inicialitzacio.
/// \param    script: L'script.
/// \param    scriptSize: El tamany del script en bytes.
///
void Device_ILI9341::writeScript(
    const uint8_t *script,
    unsigned scriptSize) {

    eosAssert(script != nullptr);
    eosAssert(scriptSize > 0);
}

