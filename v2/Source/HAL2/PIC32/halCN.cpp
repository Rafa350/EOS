#include "HAL2/hal.h"
#include "HAL2/PIC32/halCN.h"


using namespace hal;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    line: La linia.
///
CN::CN() {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    cn: El objecte a copiar.
///
CN::CN(
    const CN &cn) {
}


/// ----------------------------------------------------------------------
/// \brief    Inivialitza.
/// \param    line: La linia.
/// \param    trigger: El trigger
/// \param    pull: El modus pull
///
void CN::init(
    CNLine line,
    CNTrigger trigger,
    CNPull pull) {

    CNCONbits.ON = 1;

    if (pull == CNPull::up)
        CNPUESET = 1 << static_cast<uint32_t>(line);
    else
        CNPUECLR = 1 << static_cast<uint32_t>(line);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la linia
/// \param    line: La linia.
///
void CN::enableLine(
    CNLine line) {

    CNENSET = 1 << static_cast<uint32_t>(line);
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la linia.
/// \param    line: La linia.
///
void CN::disableLine(
    CNLine line) {

    CNENCLR = 1 << static_cast<uint32_t>(line);
}


void CN::enableInterrupt() {

    IEC1bits.CNIE = 1;
}


bool CN::disableInterrupt() {

    bool state = IEC1bits.CNIE == 1;
    IEC1bits.CNIE = 0;
    return state;
}


bool CN::getInterruptFlag() {

    return IFS1bits.CNIF != 0;
}


void CN::clearInterruptFlags() {

    IFS1bits.CNIF = 0;
}
