#ifndef __EOS_SEMAPHORE_H
#define	__EOS_SEMAPHORE_H


#include "eos.h"


typedef void *eosSemaphoreHandle;

extern eosSemaphoreHandle eosSemaphoreCreate(void);
extern bool eosSemaphoreTake(eosSemaphoreHandle hSemaphore, unsigned timeout);
extern void eosSemaphoreGive(eosSemaphoreHandle hSemaphore);
extern void eosSemaphoreISRGive(eosSemaphoreHandle hSemaphore);


#endif

