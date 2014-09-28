#ifndef __EOS_TICK_H
#define __EOS_TICK_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct {                       // Parametres d'inicialitzacio del servei
    unsigned maxAttaches;              // -Numero maxim d'adjunts
} eosTickInitializeParams;


extern eosResult eosTickInitialize(eosTickInitializeParams *params, eosHandle *hService);
extern eosResult eosTickTerminate(eosHandle hService);
extern eosResult eosTickTask(eosHandle hService);

extern eosResult eosTickAttach(eosHandle hService, eosCallback callback, void *context);
extern eosResult eosTickDeattach(eosHandle hService, eosCallback callback);


#endif

