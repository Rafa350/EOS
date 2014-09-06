#ifndef __EOS_TIMERS_H
#define __EOS_TIMERS_H

#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct {                       // Parametres d'inicialitzacio
    unsigned timeOut;                  // -Periode
    void *context;                     // -Parametre de la funcio callback
    void (*callback)(void* context);   // -Funcio callback
} eosTimerCreateParams;


extern eosResult eosTimerInitialize(void);
extern eosResult eosTimerTask(void);

extern eosResult eosTimerCreate(eosTimerCreateParams *params, eosHandle *handle);
extern eosResult eosTimerDestroy(eosHandle handle);

extern eosHandle eosTimerDelayStart(unsigned timeout);
extern BOOL eosTimerDelayGetStatus(eosHandle handle);


#endif

