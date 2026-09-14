#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"
#include "RTOS\rtosTask.h"


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

    uint8_t c;
    const uint8_t *p = script;

    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                rtos::Task::delay(eos::Time::fromMiliseconds(*p++));
                break;

            default:
                writeCommand(*p++);
                while (--c != 0)
                    writeData(*p++);
                break;
        }
    }
}

