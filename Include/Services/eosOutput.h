#ifndef __EOS_OUTPUT_H
#define	__EOS_OUTPUT_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


typedef struct __eosOutput *eosOutputHandle;
typedef struct __eosOutputService *eosOutputServiceHandle;

typedef struct {                       // Parametres d'inicialitzacio de les sortides
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    bool inverted;                     // -Inverteix la sortida
} eosOutputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosTickServiceHandle hTickService; // -Servei TICK
} eosOutputServiceParams;


// Gestio del servei
//
extern eosOutputServiceHandle eosOutputServiceInitialize(eosOutputServiceParams *params);
extern bool eosOutputIsReady(eosOutputServiceHandle hService);
extern void eosOutputServiceTask(eosOutputServiceHandle hService);
extern void eosOutputServiceTick(eosOutputServiceHandle hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosOutputHandle eosOutputCreate(eosOutputServiceHandle hService, eosOutputParams *params);
extern void eosOutputDestroy(eosOutputHandle hOutput);

// Operacions amb els objectes
//
extern bool eosOutputGet(eosOutputHandle hOutput);
extern void eosOutputSet(eosOutputHandle hOutput, bool state);
extern void eosOutputToggle(eosOutputHandle hOutput);
extern void eosOutputPulse(eosOutputHandle hOutput, unsigned time);
extern void eosOutputDelayedSet(eosOutputHandle hOutput, unsigned delay, bool state);
extern void eosOutputDelayedToggle(eosOutputHandle hOutput, unsigned delay);
extern void eosOutputDelayedPulse(eosOutputHandle hOutput, unsigned delay, unsigned time);


#endif	

