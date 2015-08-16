#ifndef __EOS_DIGOUTPUT_H
#define	__EOS_DIGOUTPUT_H


#include "eos.h"
#include "peripheral/ports/plib_ports.h"


typedef struct __eosDigOutputService *eosDigOutputServiceHandle;
typedef struct __eosDigOutput *eosDigOutputHandle;

typedef struct {                       // Parametres d'inicialitzacio de les sortides
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;            // -Posicio
    bool inverted;                     // -Inverteix la sortida
} eosDigOutputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosDigOutputServiceParams;


// Gestio del servei
//
extern eosDigOutputServiceHandle eosDigOutputServiceInitialize(eosDigOutputServiceParams *params);

// Creacio, destruccio i gestio dels objectes
//
extern eosDigOutputHandle eosDigOutputCreate(eosDigOutputServiceHandle hService, eosDigOutputParams *params);
extern void eosDigOutputDestroy(eosDigOutputHandle hOutput);

// Operacions amb els objectes
//
extern bool eosDigOutputGet(eosDigOutputHandle hOutput);
extern void eosDigOutputSet(eosDigOutputHandle hOutput, bool state);
extern void eosDigOutputToggle(eosDigOutputHandle hOutput);
extern void eosDigOutputPulse(eosDigOutputHandle hOutput, unsigned time);
extern void eosDigOutputDelayedSet(eosDigOutputHandle hOutput, unsigned delay, bool state);
extern void eosDigOutputDelayedToggle(eosDigOutputHandle hOutput, unsigned delay);
extern void eosDigOutputDelayedPulse(eosDigOutputHandle hOutput, unsigned delay, unsigned time);


#endif	

