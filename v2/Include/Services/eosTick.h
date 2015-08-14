#ifndef __EOS_TICK_H
#define __EOS_TICK_H


#include "eos.h"


typedef struct __eosTickService *eosTickServiceHandle;

typedef void (*eosTickCallback)(void *context);

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosTickServiceParams;


// Inicialitzacio, finalitzacio i gestio del servei
//
extern eosTickServiceHandle eosTickServiceInitialize(eosTickServiceParams *params);
extern bool eosTickServiceIsReady(eosTickServiceHandle hTickService);
extern void eosTickServiceTask(eosTickServiceHandle hTickService);

extern void eosTickRegisterCallback(eosTickServiceHandle hTickService,
    eosTickCallback onTick, void *onTickContext, bool deferred);

extern bool eosTickServiceLock(void);
extern void eosTickServiceUnlock(bool lock);


#endif

