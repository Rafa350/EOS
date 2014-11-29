#ifndef __EOS_OUTPUTS_H
#define	__EOS_OUTPUTS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


#ifndef __EOS_OUTPUTS_INTERNAL
struct __eosOutput {};
struct __eosOutputService {};
#endif

typedef struct __eosOutput *eosHOutput;
typedef struct __eosOutputService *eosHOutputService;

typedef struct {                       // Parametres d'inicialitzacio de les sortides
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    bool inverted;                     // -Inverteix la sortida
} eosOutputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosHTickService hTickService;      // -Servei TICK
} eosOutputServiceParams;


// Gestio del servei
//
extern eosHOutputService eosOutputServiceInitialize(eosOutputServiceParams *params);
extern void eosOutputServiceTask(eosHOutputService hService);
extern void eosOutputServiceISRTick(eosHOutputService hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosHOutput eosOutputCreate(eosHOutputService hService, eosOutputParams *params);
extern void eosOutputDestroy(eosHOutput hOutput);

// Operacions amb els objectes
//
extern bool eosOutputGet(eosHOutput hOutput);
extern void eosOutputSet(eosHOutput hOutput, bool state);
extern void eosOutputToggle(eosHOutput hOutput);
extern void eosOutputPulse(eosHOutput hOutput, unsigned time);
extern void eosOutputDelayedSet(eosHOutput hOutput, unsigned delay, bool state);
extern void eosOutputDelayedToggle(eosHOutput hOutput, unsigned delay);
extern void eosOutputDelayedPulse(eosHOutput hOutput, unsigned delay, unsigned time);


#endif	

