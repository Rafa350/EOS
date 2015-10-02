// EOS HAL
#include "hal/halGPIO.h"

// MPLAB Harmony
#include "peripheral/ports/plib_ports.h"


typedef uint8_t eosDigPinID;           // Identificador del pin

typedef struct {                       // Configuracio dels pins
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;            // -Posicio
} PinInfo;

static PinInfo pinTable[];     

#define PIN_INFO_BEGIN          PinInfo pinInfo[] = {
#define PIN_INFO_END            }
#define PIN_INFO_ENTRY(c, p)    {c, p}

PIN_INFO_BEGIN
    PIN_INFO_ENTRY(PORT_CHANNEL_D, PORTS_BIT_POS_0),
    PIN_INFO_ENTRY(PORT_CHANNEL_D, PORTS_BIT_POS_1),
    PIN_INFO_ENTRY(PORT_CHANNEL_D, PORTS_BIT_POS_2),
    PIN_INFO_ENTRY(PORT_CHANNEL_D, PORTS_BIT_POS_6),
    PIN_INFO_ENTRY(PORT_CHANNEL_D, PORTS_BIT_POS_7),
    PIN_INFO_ENTRY(PORT_CHANNEL_D, PORTS_BIT_POS_13),
PIN_INFO_END;


void halGPIOPinSetModeOutput(uint8_t pin) {

    PLIB_PORTS_PinDirectionOutputSet(
        PORTS_ID_0, 
        pinInfo[pin].channel, 
        pinInfo[pin].position);   
}

void halGPIOPinSetModeInput(uint8_t pin) {

    PLIB_PORTS_PinDirectionInputSet(
        PORTS_ID_0, 
        pinInfo[pin].channel, 
        pinInfo[pin].position);   
}


bool halGPIOPinGetState(uint8_t pin) {

    return PLIB_PORTS_PinGet(
        PORTS_ID_0, 
        pinInfo[pin].channel, 
        pinInfo[pin].position);   
}

void halGPIOPinSetState(uint8_t pin, bool state) {

    PLIB_PORTS_PinWrite(
        PORTS_ID_0, 
        pinInfo[pin].channel, 
        pinInfo[pin].position, state);    
}

void halGPIOPinToggleState(uint8_t pin) {

    PLIB_PORTS_PinToggle(
        PORTS_ID_0, 
        pinInfo[pin].channel, 
        pinInfo[pin].position);    
}
