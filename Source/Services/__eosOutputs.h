#ifndef __EOS_OUTPUTS_H__
#define	__EOS_OUTPUTS_H__


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


// Estats del servei
//
#define SS_INITIALIZING    0           // Inicialitzant
#define SS_RUNNING         1           // En execucio


struct __OUTPUT {                      // Dates d'una sortida
    BOOL active;                       // -Indica si esta actiu
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Senyal invertida;
    unsigned time;                     // -Temps restant del puls
    struct __OUTPUT_SERVICE *service;  // -El servei al que pertany
    struct __OUTPUT *nextOutput;       // -Seguent sortida
};

struct __OUTPUT_SERVICE {              // Dades del servei
    unsigned state;                    // -Estat del servei
    struct __OUTPUT *firstOutput;      // -Llista de sortides
    eosHandle hAttach;                 // -Handler del servei TICK
};


typedef struct __OUTPUT eosOutput;
typedef struct __OUTPUT_SERVICE eosOutputService;


#include "Services/eosOutputs.h"


#endif

