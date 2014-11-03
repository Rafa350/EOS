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


#ifndef __EOS_OUTPUTS_H__
typedef struct {} eosOutput;
typedef struct {} eosOutputService;
#endif


typedef struct {                       // Paramstres de creacio d'entrades
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Inverteix la sortida
} eosOutputParams;

typedef struct {                  // Parametres d'inicialitzacio del servei
    eosTickService *tickService;  // -Servei TICK
} eosOutputServiceParams;


// Gestio del servei
//
extern eosOutputService* eosOutputServiceInitialize(eosOutputServiceParams *params);
extern void eosOutputServiceTask(eosOutputService* service);
extern void eosOutputServiceISRTick(eosOutputService *service);

// Creacio, destruccio i gestio dels objectes
//
extern eosOutput* eosOutputCreate(eosOutputService *service, eosOutputParams *params);
extern void eosOutputDestroy(eosOutput *output);

// Operacions amb els objectes
//
extern BOOL eosOutputGet(eosOutput* output);
extern void eosOutputSet(eosOutput* output, BOOL state);
extern void eosOutputToggle(eosOutput* output);
extern void eosOutputPulse(eosOutput* output, unsigned time);


#endif	

