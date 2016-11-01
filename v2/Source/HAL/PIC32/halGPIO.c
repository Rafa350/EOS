#include "hal/halGPIO.h"
#include "xc.h"


static const PinInfo *pinInfo;
static uint8_t numPins;

typedef struct {
    volatile uint32_t *trisCLR;        // -Adressa TRISxCLR
    volatile uint32_t *trisSET;        // -Adressa TRISxSET
    volatile uint32_t *odcCLR;         // -Addrese ODCxCLR
    volatile uint32_t *odcSET;         // -Addresa ODCxSET
    volatile uint32_t *port;           // -Addresa PORTx
    volatile uint32_t *latCLR;         // -Adressa LATxCLR
    volatile uint32_t *latSET;         // -Adressa LATxSET
    volatile uint32_t *latINV;         // -Adressa LATxINV    
    uint8_t analogCh[16];
} DigPortDefs;


#if defined(PORTA)
static DigPortDefs portADefs = {
    .trisCLR &TRISACLR,
    .trisSET = &TRISASET,
    .odcCLR = &ODCACLR,
    .odcSET = &ODCBSET,
    .port = &PORTA,
    .latCLR = &LATACLR,
    .latSET = &LATASET,
    .latINV = &LATAINV,
    .analogCh = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};
void *gpioPortA = (void*) &portADefs;
#endif

#if defined(PORTB)
static const DigPortDefs portBDefs = {
    .trisCLR = &TRISBCLR,
    .trisSET = &TRISBSET,
    .odcCLR = &ODCBCLR,
    .odcSET = &ODCBSET,
    .port = &PORTB,
    .latCLR = &LATBCLR,
    .latSET = &LATBSET,
    .latINV = &LATBINV,
    .analogCh = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};
void *gpioPortB = (void*) &portBDefs;
#endif

#if defined(PORTC)
static DigPortDefs portCDefs = {
    .trisCLR = &TRISCCLR,
    .trisSET = &TRISCSET,
    .odcCLR = &ODCCCLR,
    .odcSET = &ODCCSET,
    .port = &PORTC,
    .latCLR = &LATCCLR,
    .latSET = &LATCSET,
    .latINV = &LATCINV,
    .analogCh = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};
void *gpioPortC = (void*) &portCDefs;
#endif

#if defined(PORTD)
static DigPortDefs portDDefs = {
    .trisCLR = &TRISDCLR,
    .trisSET = &TRISDSET,
    .odcCLR = &ODCDCLR,
    .odcSET = &ODCDSET,
    .port = &PORTD,
    .latCLR = &LATDCLR,
    .latSET = &LATDSET,
    .latINV = &LATDINV,
    .analogCh = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};
void *gpioPortD = (void*) &portDDefs;
#endif

#if defined(PORTE)
static DigPortDefs portEDefs = {
    .trisCLR = &TRISECLR,
    .trisSET = &TRISESET,
    .odcCLR = &ODCECLR,
    .odcSET = &ODCESET,
    .port = &PORTE,
    .latCLR = &LATECLR,
    .latSET = &LATESET,
    .latINV = &LATEINV,
    .analogCh = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};
void *gpioPortE = (void*) &portEDefs;
#endif

#if defined(PORTF)
static DigPortDefs portFDefs = {
    .trisCLR = &TRISFCLR,
    .trisSET = &TRISFSET,
    .odcCLR = &ODCFCLR,
    .odcSET = &ODCFSET,
    .port = &PORTF,
    .latCLR = &LATFCLR,
    .latSET = &LATFSET,
    .latINV = &LATFINV,
    .analogCh = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}    
};

void *gPioPortF = (void*) &portFDefs;
#endif

#if defined(PORTG)
static DigPortDefs portGDefs = {
    .trisCLR = &TRISGCLR,
    .trisSET = &TRISGSET,
    .odcCLR = &ODCGCLR,
    .odcSET = &ODCGSET,
    .port = &PORTG,
    .latCLR = &LATGCLR,
    .latSET = &LATGSET,
    .latINV = &LATGINV,
    .analogCh = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}    
};            
void *gpioPortG = (void*) &portGDefs;
#endif


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


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: El handler del port.
/// \param pin: Numero de pin.
/// \param mode: Modus de configuracio del pin.
///
void halGPIOInitializePin(
    GPIOPort port,
    GPIOPin pin,
    GPIOPinMode mode) {
   
    const DigPortDefs *p = (DigPortDefs*) port;
    unsigned mask = 1 << pin;
    
    switch (mode) {
        case pinOutput:
            *p->odcCLR = mask;
            *p->trisCLR = mask;
            break;
            
        case pinOpenDrainOutput:
            *p->odcSET = mask;
            *p->trisCLR = mask;
            break;
            
        default:
            *p->trisSET = mask;
            break;
    }
    
    if (p->analogCh[pin] != -1) {
        switch (mode) {
            case pinAnalogInput:
                AD1PCFGSET = 1 << p->analogCh[pin];
                break;
                
            default:
                AD1PCFGCLR = 1 << p->analogCh[pin];
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param port: El handler del port.
/// \param mode: Modus de configuracio del pin.
///
void halGPIOInitializePort(
    GPIOPort port,
    GPIOPortMode mode) {
    
    const DigPortDefs *p = (DigPortDefs*) port;
    
    switch (mode) {
        case portInput:
            *p->trisSET = 0x000000FF;
            break;
            
        case portOutput:
            *p->trisCLR = 0x000000FF;
            break;
    }    
}

/// ----------------------------------------------------------------------
/// \brief Obte l'estat d'un pin digital.
/// \param port: El handler del port.
/// \param pin: Numero del pin.
///
bool halGPIOReadPin(
    GPIOPort port,
    GPIOPin pin) {

    const DigPortDefs *p = (DigPortDefs*) port;
    unsigned mask = 1 << pin;

    return (*p->port & mask) != 0;
}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un pin de sortida digital.
/// \param port: El handler del port.
/// \param pin: Numero de pin.
/// \param data: El nou estat.
///
void halGPIOWritePin(
    GPIOPort port,
    GPIOPin pin, 
    bool data) {

    const DigPortDefs *p = (DigPortDefs*) port;
    unsigned mask = 1 << pin;

    if (data)
        *p->latSET = mask;
    else
        *p->latCLR = mask;
}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un pin de sortida digital a true.
/// \param port: El handler del port.
/// \param pin: Numero de pin.
///
void halGPIOSetPin(
    GPIOPort port,
    GPIOPin pin) {

    const DigPortDefs *p = (DigPortDefs*) port;
    unsigned mask = 1 << pin;

    *p->latSET = mask;
}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un pin de sortida digital a false.
/// \param port: El handler del port.
/// \param pin: Numero de pin.
///
void halGPIOClearPin(
    GPIOPort port,
    GPIOPin pin) {

    const DigPortDefs *p = (DigPortDefs*) port;
    unsigned mask = 1 << pin;

    *p->latCLR = mask;
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'un pin de sortida digital.
/// \param port: El handler del port.
/// \param pin: Numero de pin.
///
void halGPIOTogglePin(
    GPIOPort port,
    GPIOPin pin) {

    const DigPortDefs *p = (DigPortDefs*) port;
    unsigned mask = 1 << pin;

    *p->latINV = mask;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'estat d'un port digital.
/// \param port: El handler del port.
///
unsigned halGPIOReadPort(
    GPIOPort port) {

    const DigPortDefs *p = (DigPortDefs*) port;

    return *p->port;
}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un port de sortida digital.
/// \param port: El handler del port.
/// \param state: Estat del port.
///
void halGPIOWritePort(
    GPIOPort port,
    unsigned data) {

    const DigPortDefs *p = (DigPortDefs*) port;

    *p->port = data;
}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un port de sortida digital a true.
/// \param port: El handler del port.
/// \param data: La mascara de pins.
///
void halGPIOSetPort(
    GPIOPort port,
    unsigned mask) {

    const DigPortDefs *p = (DigPortDefs*) port;

    *p->latSET = mask;
}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un port de sortida digital a false.
/// \param port: El handler del port.
/// \param mask: La mascara de pin2.
///
void halGPIOClrPort(
    GPIOPort port,
    unsigned mask) {

    const DigPortDefs *p = (DigPortDefs*) port;

    *p->latCLR = mask;
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'un pin de sortida digital.
/// \param port: El handler del port.
/// \param pin: Numero de pin.
///
void halGPIOTogglePort(
    GPIOPort port,
    unsigned mask) {

    const DigPortDefs *p = (DigPortDefs*) port;

    *p->latINV = mask;
}
