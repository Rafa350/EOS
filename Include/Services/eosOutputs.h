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

typedef struct __eosOutput *eosOutput;
typedef struct __eosOutputService *eosOutputService;

typedef struct {                       // Parametres d'inicialitzacio de les sortides
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Inverteix la sortida
} eosOutputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosTickService tickService;        // -Servei TICK
} eosOutputServiceParams;


// Gestio del servei
//
extern eosResult eosOutputServiceInitialize(eosOutputServiceParams *params, eosOutputService *service);
extern void eosOutputServiceTask(eosOutputService service);
extern void eosOutputServiceISRTick(eosOutputService service);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosOutputCreate(eosOutputService service, eosOutputParams *params, eosOutput *output);
extern eosResult eosOutputDestroy(eosOutput output);

// Operacions amb els objectes
//
extern BOOL eosOutputGet(eosOutput output);
extern void eosOutputSet(eosOutput output, BOOL state);
extern void eosOutputToggle(eosOutput output);
extern void eosOutputPulse(eosOutput output, unsigned time);


#endif	

