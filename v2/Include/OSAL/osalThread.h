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
#define OSAL_TASK_PRIORITY_IDLE	       0x00000000
#define OSAL_TASK_PRIORITY_LOW	       0x00000001
#define OSAL_TASK_PRIORITY_NORMAL      0x00000002
#define OSAL_TASK_PRIORITY_HIGH        0x00000003


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


#ifdef	__cplusplus
}
#endif


#endif
