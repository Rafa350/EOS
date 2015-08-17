#ifndef __EOS_DIGINPUT_H
#define	__EOS_DIGINPUT_H


#include "eos.h"
#include "peripheral/ports/plib_ports.h"


typedef struct __eosDigInputService *eosDigInputServiceHandle;
typedef struct __eosDigInput *eosDigInputHandle;

typedef void (*eosDigInputCallback)(eosDigInputHandle hInput);

typedef struct {                       // Parametres d'inicializacio de les entrades
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;            // -Posicio
    bool inverted;                     // -Inverteix la entrada
    eosDigInputCallback onPosEdge;     // -Notifica flanc positiu
    eosDigInputCallback onNegEdge;     // -Notifica flanc negatiu
    eosDigInputCallback onChange;      // -Notifica canvi
} eosDigInputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosDigInputServiceParams;


// Gestio del servei
//
extern eosDigInputServiceHandle eosDigInputServiceInitialize(eosDigInputServiceParams *params);

// Creacio, destruccio i gestio dels objectes
//
extern eosDigInputHandle eosDigInputCreate(eosDigInputServiceHandle hService, eosDigInputParams *params);

// Operacions amb els objectes
//
extern bool eosDigInputGet(eosDigInputHandle hInput);
extern bool eosDigInputPosEdge(eosDigInputHandle hInput);
extern bool eosDigInputNegEdge(eosDigInputHandle hInput);


#endif	

