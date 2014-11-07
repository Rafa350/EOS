#ifndef __EOS_TICK_H
#define __EOS_TICK_H


#ifndef __EOS_H
#include "eos.h"
#endif


#ifndef __EOS_TICK_INTERNAL
struct __eosTickService {};
#endif

typedef struct __eosTickService *eosHTickService;

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosTickServiceParams;


// Inicialitzacio, finalitzacio i gestio del servei
//
extern eosResult eosTickServiceInitialize(eosTickServiceParams *params, eosHTickService *hService);
extern void eosTickServiceTask(eosHTickService hService);

extern void eosTickAttach(eosHTickService hService, eosCallback callback, void *context);
extern eosHTickService eosGetTickServiceHandle();

#endif

