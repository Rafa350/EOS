#ifndef __osalQueue__
#define __osalQueue__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_QUEUE_DATA *HQueue;

typedef struct {
    unsigned maxElements;
    unsigned elementSize;
} QueueInitializeInfo;


HQueue osalQueueCreate(const QueueInitializeInfo* info);
void osalQueueDestroy(HQueue hQueue);

void osalQueueClear(HQueue hQueue);

bool osalQueuePut(HQueue hQueue, const void* element, unsigned blockTime);
bool osalQueuePutISR(HQueue hQueue, const void* element);
bool osalQueueGet(HQueue hQueue, void* element, unsigned blockTime);
bool osalQueueGetISR(HQueue hQueue, void* element);


#ifdef	__cplusplus
}
#endif


#endif // __osalMsgQueue___
