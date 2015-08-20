#ifndef __EOS_TIMER_H
#define	__EOS_TIMER_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct __eosTimer *eosTimerHandle;
typedef void (*eosTimerCallback)(eosTimerHandle hTimer, void *params);


extern eosTimerHandle eosTimerCreate(eosTimerCallback timerFunction, void *params);
extern void eosTimerStart(eosTimerHandle hTimer, unsigned timeout);
extern void eosTimerPause(eosTimerHandle hTimer);
extern void eosTimerContinue(eosTimerHandle hTimer);


#endif	

