#ifndef __EOS_TICK_H
#define __EOS_TICK_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct __eosTickService *eosTickServiceHandle;

typedef void (*eosTickCallback)(void *context);

typedef struct {                       // Parametres d'inicialitzacio del servei
} eosTickServiceParams;


// Inicialitzacio, finalitzacio i gestio del servei
//
extern bool eosTickServiceInitialize(eosTickServiceParams *params);
extern void eosTickServiceTask(void);

extern bool eosTickAttachFunction(eosTickCallback onTick, void *onTickContext);


#endif

