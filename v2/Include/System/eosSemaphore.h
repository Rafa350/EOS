#ifndef __EOS_SEMAPHORE_H
#define	__EOS_SEMAPHORE_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef void *eosSemaphoreHandle;      // Handler del semaforo


// Funcions de creacio i destruccio de semaforos
//
extern eosSemaphoreHandle eosSemaphoreCreate(void);
extern eosSemaphoreHandle eosSemaphoreCreateCounting(unsigned startCount, unsigned maxCount);

// Funcions de gestio i control dels semaforos
//
extern bool eosSemaphoreTake(eosSemaphoreHandle hSemaphore, unsigned timeout);
extern void eosSemaphoreGive(eosSemaphoreHandle hSemaphore);
extern void eosSemaphoreISRGive(eosSemaphoreHandle hSemaphore);


#endif

