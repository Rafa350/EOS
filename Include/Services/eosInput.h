#ifndef __EOS_INPUT_H
#define	__EOS_INPUT_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


typedef struct __eosInput *eosHInput;
typedef struct __eosInputService *eosHInputService;

typedef void (*eosInputCallback)(eosHInput hInput);

typedef struct {                       // Parametres d'inicializacio de les entrades
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    bool inverted;                     // -Inverteix la entrada
    eosInputCallback onPosEdge;        // -Notifica flanc positiu
    eosInputCallback onNegEdge;        // -Notifica flanc negatiu
    eosInputCallback onChange;         // -Notifica canvi
} eosInputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosHTickService hTickService;      // -Servei TICK
} eosInputServiceParams;


// Gestio del servei
//
extern eosHInputService eosInputServiceInitialize(eosInputServiceParams *params);
extern bool eosInputServiceIsReady(eosHInputService hService);
extern void eosInputServiceTask(eosHInputService hService);
extern void eosInputServiceTick(eosHInputService hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosHInput eosInputCreate(eosHInputService hService, eosInputParams *params);
extern void eosInputDestroy(eosHInput hInput);

// Operacions amb els objectes
//
extern bool eosInputGet(eosHInput hInput);
extern bool eosInputPosEdge(eosHInput hInput);
extern bool eosInputNegEdge(eosHInput hInput);


typedef struct {
    SYS_MODULE_INIT moduleInit;
} DRV_INPUT_INIT;

extern SYS_MODULE_OBJ DRV_INPUT_Initialize(const SYS_MODULE_INDEX, const DRV_INPUT_INIT * const init);

#endif	

