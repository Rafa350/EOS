#include "xc.h"
#include "hal/halGPIO.h"


static const PinInfo *pinInfo;
static uint8_t numPins;


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO
/// \param pinInfo: Taula de configuracio de pins.
/// \param numPins: Numero de pins.
///
void halGPIOInitialize(
    const PinInfo *_pinInfo, 
    uint8_t _numPins) {
    
    pinInfo = _pinInfo;
    numPins = _numPins;
}


/// ----------------------------------------------------------------------
/// \brief Configura un port com a sortida digital.
/// \param pin: Numero de pin.
/// \param openDrain: True si la sortida es de tipus OPEN-DRAIN.
///
void halGPIOPinSetModeOutput(
    uint8_t pin,
    bool openDrain) {
   
    const PinInfo *p = &pinInfo[pin];
    *p->trisCLR = p->mask;
    
    if (openDrain)
        *p->odcSET = p->mask;
    else
        *p->odcCLR = p->mask;
    
    if (p->analog != -1) 
        AD1PCFGSET = 1 << p->analog;
}


/// ----------------------------------------------------------------------
/// \brief Configura un port com a entrada digital.
/// \param pin: Numero de pin.
///
void halGPIOPinSetModeInput(
    uint8_t pin) {

    const PinInfo *p = &pinInfo[pin];
    *p->trisSET = p->mask;

    if (p->analog != -1)
        AD1PCFGSET = 1 << p->analog;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'estat d'un port digital.
/// \param pin: Numero del pin.
///
bool halGPIOPinGetState(
    uint8_t pin) {

    const PinInfo *p = &pinInfo[pin];
    return (*p->port & p->mask) != 0;

}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un port de sortida digital.
/// \param pin: Numero de pin.
/// \param state: El nou estat.
///
void halGPIOPinSetState(
    uint8_t pin, 
    bool state) {

    const PinInfo *p = &pinInfo[pin];
    if (state)
        *p->latSET = p->mask;
    else
        *p->latCLR = p->mask;
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'un port de sortida digital.
/// \param pin: Numero de pin.
///
void halGPIOPinToggleState(
    uint8_t pin) {

    const PinInfo *p = &pinInfo[pin];
    *p->latINV = p->mask;
}
