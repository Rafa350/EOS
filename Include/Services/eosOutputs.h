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
struct __eosOutputService{};
#endif

typedef struct __eosOutput *eosHOutput;
typedef struct __eosOutputService *eosHOutputService;

typedef struct {                       // Parametres d'inicialitzacio de les sortides
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Inverteix la sortida
} eosOutputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosHTickService hTickService;      // -Servei TICK
} eosOutputServiceParams;


// Gestio del servei
//
extern eosResult eosOutputServiceInitialize(eosOutputServiceParams *params, eosHOutputService *hService);
extern void eosOutputServiceTask(eosHOutputService hService);
extern void eosOutputServiceISRTick(eosHOutputService hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosOutputCreate(eosHOutputService hService, eosOutputParams *params, eosHOutput *hOutput);
extern eosResult eosOutputDestroy(eosHOutput hOutput);

// Operacions amb els objectes
//
extern BOOL eosOutputGet(eosHOutput hOutput);
extern void eosOutputSet(eosHOutput hOutput, BOOL state);
extern void eosOutputToggle(eosHOutput hOutput);
extern void eosOutputPulse(eosHOutput hOutput, unsigned time);
extern void eosOutputDelayedSet(eosHOutput hOutput, unsigned delay, BOOL state);
extern void eosOutputDelayedToggle(eosHOutput hOutput, unsigned delay);
extern void eosOutputDelayedPulse(eosHOutput hOutput, unsigned delay, unsigned time);


#endif	
