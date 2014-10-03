#ifndef __EOS_OUTPUTS_H
#define	__EOS_OUTPUTS_H

#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


typedef struct {                  // Paramstres de creacio d'entrades
    PORTS_CHANNEL channel;        // -Canal del port
    PORTS_BIT_POS position;       // -Pin del port
    BOOL inverted;                // -Inverteix la sortida
} eosOutputsCreateParams;

typedef struct {                  // Parametres d'inicialitzacio del servei
    unsigned maxOutputs;          // -Numero maxim de sortides a procesar
    eosHandle hTickService;       // -Servei TICK
} eosOutputsInitializeParams;


// Inicialitzacio, finalitzacio i gestio del servei
//
extern eosResult eosOutputsInitialize(eosOutputsInitializeParams *params, eosHandle *hService);
extern eosResult eosOutputsTerminate(eosHandle hService);
extern eosResult eosOutputsTask(eosHandle hService);
extern void eosOutputsISRTick(void *context);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosOutputsCreate(eosHandle hService, eosOutputsCreateParams *params, eosHandle *hOutput);
extern eosResult eosOutputsDestroy(eosHandle hOutput);

// Operacions amb els objectes
//
extern BOOL eosOutputsGet(eosHandle hOutput);
extern BOOL eosOutputsSet(eosHandle hOutput, BOOL state);
extern BOOL eosOutputsToggle(eosHandle hOutput);
extern BOOL eosOutputsPulse(eosHandle hOutput, unsigned time);


#endif	

