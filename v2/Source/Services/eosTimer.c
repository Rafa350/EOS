#include "eos.h"

#include "System/eosMemory.h"
#include "Services/eosTimer.h"
#include "System/eosTask.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "timers.h"


typedef struct __eosTimer {
    TimerHandle_t rtosTimer;
    eosTimerCallback onTimeout;
    void *context;
    eosTimerHandle hNextTimer;
} eosTimer;

typedef struct __eosTimerService {
    eosTimerHandle hFirstTimer;
} eosTimerService;


static void timerCallback(TimerHandle_t rtosTimer);


eosTimerServiceHandle eosTimerServiceInitialize(
    eosTimerServiceParams *params) {
    
    eosDebugVerify(params != NULL);

    eosTimerServiceHandle hService = eosAlloc(sizeof(eosTimerService));
    if (hService != NULL) {
        hService->hFirstTimer = NULL;
    }
    
    return hService;
}


eosTimerHandle eosTimerCreate(
    eosTimerServiceHandle hService, 
        eosTimerParams *params) {
    
    eosDebugVerify(hService != NULL);
    eosDebugVerify(params != NULL);
    
    eosTimerHandle hTimer = eosAlloc(sizeof(eosTimer));
    if (hTimer) {
        hTimer->onTimeout = params->onTimeout;
        hTimer->context = params->context;
        hTimer->rtosTimer = xTimerCreate("", params->period, params->autoreload, 
            (void*) hTimer, timerCallback);
        
        eosCriticalSectionInfo csInfo;
        eosEnterCriticalSection(eosCriticalSectionSeverityLow, &csInfo);
        
        hTimer->hNextTimer = hService->hFirstTimer;
        hService->hFirstTimer = hTimer;
        
        eosLeaveCriticalSection(&csInfo);
    }
    
    return  hTimer;
}


void eosTimerStart(
    eosTimerHandle hTimer, 
    unsigned timeout) {
    
    eosDebugVerify(hTimer != NULL);
    
    xTimerStart(hTimer->rtosTimer, timeout);
}


void eosTimerStop(
    eosTimerHandle hTimer,
    unsigned timeout) {
    
    eosDebugVerify(hTimer != NULL);

    xTimerStop(hTimer->rtosTimer, timeout);
}


void eosTimerRestart(
    eosTimerHandle hTimer,
    unsigned timeout) {
    
    eosDebugVerify(hTimer != NULL);

    xTimerReset(hTimer->rtosTimer, timeout);
}


static void timerCallback(
    TimerHandle_t rtosTimer) {
    
    eosTimerHandle hTimer = pvTimerGetTimerID(rtosTimer);
    if (hTimer->onTimeout != NULL)
        hTimer->onTimeout(hTimer, hTimer->context);
}
