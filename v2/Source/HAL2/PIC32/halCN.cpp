#include "HAL2/hal.h"
#include "HAL2/PIC32/halCN.h"


using namespace hal;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    line: La linia.
///
CN::CN(
    CNLine line) {

    _lineNumber = static_cast<unsigned>(line);
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
/// \brief    Selecciona el trigger.
/// \param    trigger: El trigger
///
void CN::setTrigger(
    Trigger trigger) {

    // Activa el modul
    //
    CNCONbits.ON = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el pullup.
/// \param    pullUp: True per activar elñ pull-up.
///
void CN::setPullUp(
    bool pullUp) {

    // Activa pullup
    //
    if (pullUp)
        CNPUESET = 1 << _lineNumber;
    else
        CNPUECLR = 1 << _lineNumber;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions.
///
void CN::enableInterrupt() {

    CNENSET = 1 << _lineNumber;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabiklita les interrupcions.
///
void CN::disableInterrupt() {

    CNENCLR = 1 << _lineNumber;
}
