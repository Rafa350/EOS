#ifndef __osalMsgQueue__
#define __osalMsqQueue__


// EOS/OSAL includes
//
#include "osal/osal.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct MSGQUEUE *HMsgQueue;

typedef struct {
    unsigned maxElements;
    unsigned elementSize;
} MsgQueueInitializeInfo;


HMsgQueue osalMsgQueueCreate(const MsgQueueInitializeInfo *info);
void osalMsgQueueDestroy(HMsgQueue hMsgQueue);

void osalMsgQueueClear(HMsgQueue hMsgQueue);

bool osalMsgQueuePut(HMsgQueue hMsgQueue, const void *element, unsigned waitTime);
bool osalMsgQueuePutISR(HMsgQueue hMsgQueue, const void *element);
bool osalMsgQueueGet(HMsgQueue hMsgQueue, void *element, unsigned waitTime);
bool osalMsgQueueGetISR(HMsgQueue hMsgQueue, void *element);


#ifdef	__cplusplus
}
#endif


#endif // __osalMsgQueue___
