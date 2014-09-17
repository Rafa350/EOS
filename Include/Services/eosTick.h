#ifndef __EOS_TICK_H
#define __EOS_TICK_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef void (*eosTickCallback)(void *context);

typedef struct {                       // Parametres d'inicialitzacio del servei
    unsigned maxAttaches;              // -Numero maxim d'adjunts
} eosTickInitializeParams;


extern eosResult eosTickInitialize(eosTickInitializeParams *params, eosHandle *hService);
extern eosResult eosTickTerminate(eosHandle hService);
extern eosResult eosTickTask(eosHandle hService);

extern eosResult eosTickAttach(eosHandle hService, eosTickCallback callback, void *context);
extern eosResult eosTickUnAttach(eosHandle hService, eosTickCallback callback);


#endif

