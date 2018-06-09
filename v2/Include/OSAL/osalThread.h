#ifndef __osalThread__
#define __osalThread__


// EOS includes
//
#include "eos.h"
#include "osal/osal.h"


// Stdlib includes
//
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef void (*TaskFunction)(void *params);

typedef struct {                       // Parametres d'inicialitzacio
	const char *name;                  // -Nom
	TaskFunction function;             // -Funcio a executar
	void *params;                      // -Parametres de la funcio
	unsigned stackSize;                // -Tamany de la pila
	uint32_t options;                  // -Opcions
} TaskInitializeInfo;

typedef struct TASK *HTask;

// Prioritat de la tasca
#define OSAL_TASK_PRIORITY_OFFSET      0
#define OSAL_TASK_PRIORITY_MASK        ((uint32_t)0b11 << OSAL_TASK_PRIORITY_OFFSET)
#define OSAL_TASK_PRIORITY_IDLE	       ((uint32_t)0 << OSAL_TASK_PRIORITY_OFFSET)
#define OSAL_TASK_PRIORITY_LOW	       ((uint32_t)1 << OSAL_TASK_PRIORITY_OFFSET)
#define OSAL_TASK_PRIORITY_NORMAL      ((uint32_t)2 << OSAL_TASK_PRIORITY_OFFSET)
#define OSAL_TASK_PRIORITY_HIGH        ((uint32_t)3 << OSAL_TASK_PRIORITY_OFFSET)


HTask osalTaskCreate(const TaskInitializeInfo *info);
void osalTaskDestroy(HTask hTask);

void osalEnterCritical();
void osalExitCritical();

void osalStartScheduler();
void osalStopScheduler();

void osalSuspendAll();
void osalResumeAll();
unsigned osalGetTickCount();
void osalDelay(unsigned time);
void osalDelayUntil(unsigned time, unsigned *lastTick);


#ifdef	__cplusplus
}
#endif


#endif
