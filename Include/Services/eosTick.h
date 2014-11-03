#ifndef __EOS_TICK_H
#define __EOS_TICK_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H__
struct __TICK_SERVICE {};
typedef struct __TICK_SERVICE eosTickService;
#endif


typedef struct {                       // Parametres d'inicialitzacio del servei
    unsigned maxAttaches;              // -Numero maxim d'adjunts
} eosTickServiceParams;


// Inicialitzacio, finalitzacio i gestio del servei
//
extern eosTickService* eosTickServiceInitialize(eosTickServiceParams *params);
extern void eosTickServiceTask(eosTickService* service);
extern void eosTickAttach(eosTickService* service, eosCallback callback, void *context);


#endif

