#ifndef __osalQueue__
#define __osalQueue__


// EOS includes
//
#include "eos.h"


// Stdlib includes
//
#include "stdint.h"
#include "stdbool.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {
    unsigned maxElements;
    unsigned elementSize;
} QueueInitializeInfo;


typedef void *QueueHandler;


QueueHandler osalQueueCreate(const QueueInitializeInfo *info);
void osalQueueDestroy(QueueHandler queue);

void osalQueueClear(QueueHandler queue);

bool osalQueuePut(QueueHandler queue, const void *element, unsigned blockTime);
bool osalQueuePutISR(QueueHandler queue, const void *element);
bool osalQueueGet(QueueHandler queue, void *element, unsigned blockTime);
bool osalQueueGetISR(QueueHandler queue, void *element);


#ifdef	__cplusplus
}
#endif


#endif // __osalQueue___
