module Eos.Controllers.Display.Drivers.ILI9341;

import Eos.System.Core.Task;
import Eos.System.Core.Ticks;


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
    const UInt8 *script,
    UInt32 scriptSize) {

    UInt8 c;
    const UInt8 *p = script;

    while ((c = *p++) != OpCode::OP_END) {
        switch (c) {
            case OpCode::OP_DELAY:
                Task::delay(Ticks::fromMiliseconds(*p++));
                break;

            default:
                writeCommand(*p++);
                while (--c != 0)
                    writeData(*p++);
                break;
        }
    }
}
