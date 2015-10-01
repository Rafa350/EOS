#ifndef __EOS_DIGPIN_H
#define	__EOS_DIGPIN_H


extern "C" {
    

#include "peripheral/ports/plib_ports.h"


typedef uint8_t eosDigPinID;           // Identificador del pin

typedef struct {                       // Configuracio dels pins
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;            // -Posicio
} eosDigPinInfo;


extern eosDigPinInfo eosDigPins[];     

#define eosDigPins_BEGIN          eosDigPinInfo eosDigPins[] = {
#define eosDigPins_END            }
#define eosDigPins_ENTRY(c, p)    {c, p}

#define eosDigPinOutputMode(pin) \
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, eosDigPins[pin].channel, eosDigPins[pin].position);

#define eosDigPinInputMode(pin) \
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, eosDigPins[pin].channel, eosDigPins[pin].position);

#define eosDigPinGet(pin) \
    PLIB_PORTS_PinGet(PORTS_ID_0, eosDigPins[pin].channel, eosDigPins[pin].position);

#define eosDigPinSet(pin, state) \
    PLIB_PORTS_PinWrite(PORTS_ID_0, eosDigPins[pin].channel, eosDigPins[pin].position, state)

#define eosDigPinToggle(pin) \
    PLIB_PORTS_PinToggle(PORTS_ID_0, eosDigPins[pin].channel, eosDigPins[pin].position)


}


#endif	

