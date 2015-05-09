#ifndef __EOS_DIGINPUT_H
#define	__EOS_DIGINPUT_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif


typedef struct __eosDigInputService *eosDigInputServiceHandle;
typedef struct __eosDigInput *eosDigInputHandle;

typedef void (*eosDigInputCallback)(eosDigInputHandle hInput);

typedef struct {                       // Parametres d'inicializacio de les entrades
    unsigned port;                     // -Port
    unsigned pin;                      // -Pin
    bool inverted;                     // -Inverteix la entrada
    eosDigInputCallback onPosEdge;     // -Notifica flanc positiu
    eosDigInputCallback onNegEdge;     // -Notifica flanc negatiu
    eosDigInputCallback onChange;      // -Notifica canvi
} eosDigInputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosDigInputServiceParams;


// Gestio del servei
//
extern eosDigInputServiceHandle eosDigInputServiceInitialize(
    eosDigInputServiceParams *params);
extern bool eosDigInputServiceIsReady(eosDigInputServiceHandle hService);
extern void eosDigInputServiceTask(eosDigInputServiceHandle hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosDigInputHandle eosDigInputCreate(eosDigInputServiceHandle hService,
    eosDigInputParams *params);
extern void eosDigInputDestroy(eosDigInputHandle hInput);

// Operacions amb els objectes
//
extern bool eosDigInputGet(eosDigInputHandle hInput);
extern bool eosDigInputPosEdge(eosDigInputHandle hInput);
extern bool eosDigInputNegEdge(eosDigInputHandle hInput);


#endif	

