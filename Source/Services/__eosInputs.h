#ifndef __EOS_INPUTS_H__
#define	__EOS_INPUTS_H__


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


#define SS_INITIALIZING           0
#define SS_RUNNING                1

#define PATTERN_ON                0x00007FFF
#define PATTERN_OFF               0x00008000
#define PATTERN_MASK              0x0000FFFF


struct __INPUT {                  // Dades d'una entrada
    PORTS_CHANNEL channel;        // -Canal del port
    PORTS_BIT_POS position;       // -Pin del port
    BOOL inverted;                // -Senyal invertida;
    unsigned when;                // -Quant hi ha que executar la funcio callback
    eosCallback callback;         // -Funcio callback
    void *context;                // -Parametre de la funcio callback
    UINT32 pattern;               // -Patro de filtratge
    BOOL state;                   // -Indicador ON/OFF
    BOOL posEdge;                 // -Indica si s'ha rebut un falc positiu
    BOOL negEdge;                 // -Indica si s'ha rebut un flanc negatiu
    struct __INPUT_SERVICE *service;   // -El servei al que pertany
    struct __INPUT *nextInput;    // -Seguent entrada
};
typedef struct __INPUT eosInput;

struct __INPUT_SERVICE {          // Dades del servei
    unsigned state;               // -Estat del servei
    struct __INPUT* firstInput;   // -Primera entrada de la llista
    eosHandle hAttach;            // -Handler del servei TICK
};
typedef struct __INPUT_SERVICE eosInputService;


#include "Services/eosInputs.h"


#endif

