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


typedef struct __eosInput *eosInputHandle;

typedef void (*eosInputCallback)(eosInputHandle hInput);

typedef struct {                       // Parametres d'inicializacio de les entrades
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    bool inverted;                     // -Inverteix la entrada
    eosInputCallback onPosEdge;        // -Notifica flanc positiu
    eosInputCallback onNegEdge;        // -Notifica flanc negatiu
    eosInputCallback onChange;         // -Notifica canvi
} eosInputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosInputServiceParams;


// Gestio del servei
//
extern bool eosInputServiceInitialize(eosInputServiceParams *params);
extern bool eosInputServiceIsReady(void);
extern void eosInputServiceTask(void);

// Creacio, destruccio i gestio dels objectes
//
extern eosInputHandle eosInputCreate(eosInputParams *params);
extern void eosInputDestroy(eosInputHandle hInput);

// Operacions amb els objectes
//
extern bool eosInputGet(eosInputHandle hInput);
extern bool eosInputPosEdge(eosInputHandle hInput);
extern bool eosInputNegEdge(eosInputHandle hInput);


#endif	

