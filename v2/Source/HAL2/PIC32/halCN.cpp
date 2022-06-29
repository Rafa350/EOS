#include "HAL2/hal.h"
#include "HAL2/PIC32/halCN.h"


using namespace hal;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    line: La linia.
///
CN::CN(
    CNLine line) :

    _lineNumber(getLineNumber(line)) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    cn: El objecte a copiar.
///
CN::CN(
    const CN &cn):

    _lineNumber(cn._lineNumber) {

}


/// ----------------------------------------------------------------------
/// \brief    IniciaLITZACIO.
///
void CN::initialize(
    CNTrigger trigger,
    bool pullUp) {

    // Activa el modul
    //
    CNCONbits.ON = 1;

    // Activa pullup
    //
    if (pullUp)
        CNPUESET = 1 << _lineNumber;
    else
        CNPUECLR = 1 << _lineNumber;

    // Desactiva interrupcions de la linia
    //
    CNENCLR = 1 << _lineNumber;
}


void CN::enableInterrupt() {

    CNENSET = 1 << _lineNumber;
}


void CN::disableInterrupt() {

    CNENCLR = 1 << _lineNumber;
}