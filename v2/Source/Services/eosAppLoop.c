#include "eos.h"
#include "System/eosTask.h"
#include "System/eosMemory.h"
#include "Services/eosAppLoop.h"


typedef struct __eosAppLoopService {    
    eosTaskHandle hTask;
} eosAppLoopService;


extern void appSetup(void);
extern void appLoop(void);


static void task(void *params);


eosAppLoopServiceHandle eosAppLoopServiceInitialize(
    eosAppLoopServiceParams *params) {
    
    eosDebugVerify(params != NULL);
    
    eosAppLoopServiceHandle hService = eosAlloc(sizeof(eosAppLoopService));
    if (hService != NULL) {
        
        hService->hTask = eosTaskCreate(params->appPriority, params->appStackSize, task, hService);
        eosDebugVerify(hService->hTask != NULL);
    }
    
    return hService;
}


static void task(
    void *params) {
    
    appSetup();
    while (true)
        appLoop();
}
