#ifndef __osalQueue__
#define __osalQueue__


// EOS includes
//
#include "eos.h"


// Stdlib includes
//
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {
    
} QueueInitializeInfo;


typedef void *QueueHandler;


QueueHandler osalQueueCreate(const QueueInitializeInfo *info);
void osalQueueDestroy(QueueHandler queue);


#ifdef	__cplusplus
}
#endif


#endif // __osalQueue___