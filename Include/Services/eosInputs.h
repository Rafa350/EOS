#ifndef __EOS_INPUTS_H
#define	__EOS_INPUTS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


#ifndef __EOS_INPUTS_INTERNAL
struct __eosInput {};
struct __eosInputService {};
#endif

typedef struct __eosInput *eosHInput;
typedef struct __eosInputService *eosHInputService;

typedef struct {                       // Parametres d'inicializacio de les entrades
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Inverteix la entrada
    eosCallback onPosEdge;             // -Event POS_EDGE
    eosCallback onNegEdge;             // -EVENT NEG_EDGE
    eosCallback onChange;              // -EVENT CHANGE
    void *context;                     // -Parametres del event
} eosInputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosHTickService hTickService;      // -Servei TICK
} eosInputServiceParams;


// Gestio del servei
//
extern eosResult eosInputServiceInitialize(eosInputServiceParams *params, eosHInputService *hService);
extern void eosInputServiceTask(eosHInputService hService);
extern void eosInputServiceISRTick(eosHInputService hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosInputCreate(eosHInputService hService, eosInputParams *params, eosHInput *hInput);
extern eosResult eosInputDestroy(eosHInput hInput);

// Operacions amb els objectes
//
extern BOOL eosInputGet(eosHInput hInput);
extern BOOL eosInputPosEdge(eosHInput hInput);
extern BOOL eosInputNegEdge(eosHInput hInput);


#endif	

