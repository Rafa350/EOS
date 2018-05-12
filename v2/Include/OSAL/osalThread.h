#ifndef __osalThread__
#define __osalThread__


// EOS includes
//
#include "eos.h"


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
	uint16_t stackSize;                // -Tamany de la pila
	uint32_t options;                  // -opcions
} TaskInitializeInfo;

typedef void *TaskHandler;

// Prioritat de la tasca
#define OSAL_TASK_PRIORITY_MASK        0x00000003
#define OSAL_TASK_PRIORITY_POS         0
#define OSAL_TASK_PRIORITY_IDLE	       ((uint32_t)0 << OSAL_TASK_PRIORITY_POS)
#define OSAL_TASK_PRIORITY_LOW	       ((uint32_t)1 << OSAL_TASK_PRIORITY_POS)
#define OSAL_TASK_PRIORITY_NORMAL      ((uint32_t)2 << OSAL_TASK_PRIORITY_POS)
#define OSAL_TASK_PRIORITY_HIGH        ((uint32_t)3 << OSAL_TASK_PRIORITY_POS)


TaskHandler osalTaskCreate(const TaskInitializeInfo *info);
void osalTaskDestroy(TaskHandler handler);

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
