#ifndef __EOS_TIMER_H
#define	__EOS_TIMER_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct __eosTimerService *eosTimerServiceHandle;
typedef struct __eosTimer *eosTimerHandle;
typedef void (*eosTimerCallback)(eosTimerHandle hTimer, void *context);

typedef struct {
} eosTimerServiceParams;

typedef struct {
    unsigned period;
    bool autoreload;
    eosTimerCallback onTimeout;
    void* context;
} eosTimerParams;


extern eosTimerServiceHandle eosTimerServiceInitialize(eosTimerServiceParams *params);
extern eosTimerHandle eosTimerCreate(eosTimerServiceHandle hService, eosTimerParams *params);
extern void eosTimerStart(eosTimerHandle hTimer, unsigned timeout);
extern void eosTimerStop(eosTimerHandle hTimer, unsigned timeout);
extern void eosTimerReStart(eosTimerHandle hTimer, unsigned timeout);


#endif	

