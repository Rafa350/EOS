#ifndef __EOS_TICK_H
#define __EOS_TICK_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct __eosTickService *eosHTickService;

typedef void (*eosTickCallback)(void *context);

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosTickServiceParams;


// Inicialitzacio, finalitzacio i gestio del servei
//
extern eosHTickService eosTickServiceInitialize(eosTickServiceParams *params);
extern void eosTickServiceTask(eosHTickService hService);

extern void eosTickAttach(eosHTickService hService, eosTickCallback onTick, void *onTickContext);
extern eosHTickService eosGetTickServiceHandle();

#endif

