#ifndef __EOS_TIMERS_H
#define __EOS_TIMERS_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Codis d'error
//
#define eos_ERROR_TIMER_UNAVAILABLE    eos_ERROR_FIRST

typedef void (*eosTimerCallback)(void *context);

typedef struct {                       // Parametres d'inicialitzacio
    unsigned timeOut;                  // -Periode
    eosTimerCallback callback;         // -Funcio callback
    void *context;                     // -Parametre de la funcio callback
} eosTimerCreateParams;


extern eosResult eosTimerInitialize(void);
extern eosResult eosTimerTerminate(void);
extern eosResult eosTimerTask(void);

extern void eosTimerISRTick(void *context);

extern eosResult eosTimerCreate(eosTimerCreateParams *params, eosHandle *handle);
extern eosResult eosTimerDestroy(eosHandle handle);

extern eosHandle eosTimerDelayStart(unsigned timeout);
extern BOOL eosTimerDelayGetStatus(eosHandle handle);


#endif

