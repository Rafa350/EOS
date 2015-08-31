#ifndef __EOS_APPLOOP_H
#define	__EOS_APPLOOP_H


typedef struct __eosAppLoopService *eosAppLoopServiceHandle;

typedef struct {
    unsigned appStackSize;
    unsigned appPriority;
} eosAppLoopServiceParams;


extern eosAppLoopServiceHandle eosAppLoopServiceInitialize(eosAppLoopServiceParams *params);


#endif	

