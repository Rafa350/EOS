#include "xc.h"
#include "hal/halGPIO.h"


typedef struct {                       // Configuracio dels pins
    volatile uint32_t *trisCLR;        // -Adressa TRISxCLR
    volatile uint32_t *trisSET;        // -Adressa TRISxSET
    volatile uint32_t *odcCLR;         // -Addrese ODCxCLR
    volatile uint32_t *odcSET;         // -Addresa ODCxSET
    volatile uint32_t *port;           // -Addresa PORTx
    volatile uint32_t *latCLR;         // -Adressa LATxCLR
    volatile uint32_t *latSET;         // -Adressa LATxSET
    volatile uint32_t *latINV;         // -Adressa LATxINV
    uint32_t mask;                     // -Mascara del pin
    int analog;                        // -Port analogic (-1 cap))
} PinInfo;


#define NUM_PINS   6
PinInfo pinInfoTbl[NUM_PINS] = {
    { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 0, -1 },
    { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 1, -1 },
    { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 2, -1 },
    { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 6, -1 },
    { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 7, -1 },
    { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 13, -1 }
};


void halGPIOPinSetModeOutput(
    uint8_t pin,
    bool openDrain) {
   
    PinInfo *p = &pinInfoTbl[pin];
    *p->trisCLR = p->mask;
    
    if (openDrain)
        *p->odcSET = p->mask;
    else
        *p->odcCLR = p->mask;
    
    if (p->analog != -1) 
        AD1PCFGSET = 1 << p->analog;
}


void halGPIOPinSetModeInput(
    uint8_t pin) {

    PinInfo *p = &pinInfoTbl[pin];
    *p->trisSET = p->mask;

    if (p->analog != -1)
        AD1PCFGSET = 1 << p->analog;
}


bool halGPIOPinGetState(
    uint8_t pin) {

    PinInfo *p = &pinInfoTbl[pin];
    return (*p->port & p->mask) != 0;

}

void halGPIOPinSetState(
    uint8_t pin, 
    bool state) {

    PinInfo *p = &pinInfoTbl[pin];
    if (state)
        *p->latSET = p->mask;
    else
        *p->latCLR = p->mask;
}


void halGPIOPinToggleState(
    uint8_t pin) {

    PinInfo *p = &pinInfoTbl[pin];
    *p->latINV = p->mask;
}
