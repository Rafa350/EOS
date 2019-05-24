#ifndef __osalTask__
#define __osalTask__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct TASK *HTask;
typedef uint32_t TaskOptions;
typedef void (*TaskFunction)(void *params);

typedef struct {                       // Parametres d'inicialitzacio
	const char *name;                  // -Nom
	TaskFunction function;             // -Funcio a executar
	void *params;                      // -Parametres de la funcio
	unsigned stackSize;                // -Tamany de la pila
	TaskOptions options;               // -Opcions
} TaskInitializeInfo;


// Prioritat de la tasca
#define OSAL_TASK_PRIORITY_POS         0u
#define OSAL_TASK_PRIORITY_MASK        ((TaskOptions)0b11 << OSAL_TASK_PRIORITY_POS)

#define OSAL_TASK_PRIORITY_IDLE	       ((TaskOptions)0 << OSAL_TASK_PRIORITY_POS)
#define OSAL_TASK_PRIORITY_LOW	       ((TaskOptions)1 << OSAL_TASK_PRIORITY_POS)
#define OSAL_TASK_PRIORITY_NORMAL      ((TaskOptions)2 << OSAL_TASK_PRIORITY_POS)
#define OSAL_TASK_PRIORITY_HIGH        ((TaskOptions)3 << OSAL_TASK_PRIORITY_POS)


HTask osalTaskCreate(const TaskInitializeInfo *info);
void osalTaskDestroy(HTask hTask);
void osalTaskYield();


#ifdef	__cplusplus
}
#endif


#endif // __oisalTask__
