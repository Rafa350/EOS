#ifndef __EOS_DIGOUTPUT_H
#define	__EOS_DIGOUTPUT_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif

typedef enum {
    eosDigOutputChannel_A = 0,         // Canal de sortida A
    eosDigOutputChannel_B,             // Canal de sortida B
    eosDigOutputChannel_C,             // Canal de sortida C
    eosDigOutputChannel_D,             // Canal de sortida D
    eosDigOutputChannel_E,             // Canal de sortida E
    eosDigOutputChannel_F              // Canal de sortida F
} eosDigOutputChannel;


typedef struct __eosDigOutputService *eosDigOutputServiceHandle;
typedef struct __eosDigOutput *eosDigOutputHandle;

typedef struct {                       // Parametres d'inicialitzacio de les sortides
    eosDigOutputChannel channel;       // -Canal del port
    unsigned position;                 // -Pin del port
    bool inverted;                     // -Inverteix la sortida
} eosDigOutputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosDigOutputServiceParams;


// Gestio del servei
//
extern eosDigOutputServiceHandle eosDigOutputServiceInitialize(
    eosDigOutputServiceParams *params);
extern bool eosDigOutputServiceIsReady(eosDigOutputServiceHandle hService);
extern void eosDigOutputServiceTask(eosDigOutputServiceHandle hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosDigOutputHandle eosDigOutputCreate(eosDigOutputServiceHandle hService,
    eosDigOutputParams *params);
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

