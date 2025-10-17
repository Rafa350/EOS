#ifndef __osalTask__
#define __osalTask__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_TASK_DATA* HTask;
typedef uint32_t TaskOptions;
typedef void (*TaskFunction)(void* params);

typedef struct {                  // Parametres d'inicialitzacio
	const char* name;             // -Nom
	TaskFunction function;        // -Funcio a executar
	void* params;                 // -Parametres de la funcio
	unsigned stackSize;           // -Tamany de la pila
	TaskOptions options;          // -Opcions
	void *ptrData;                // -Punter auxiliar per dades de l'aplicacio
} TaskInitializeInfo;


// Prioritat de la tasca
#define OSAL_TASK_PRIORITY_pos         0u
#define OSAL_TASK_PRIORITY_bits        0x111u
#define OSAL_TASK_PRIORITY_mask        (OSAL_TASK_PRIORITY_bits << OSAL_TASK_PRIORITY_pos)

#define OSAL_TASK_PRIORITY_IDLE	       (0u << OSAL_TASK_PRIORITY_pos)
#define OSAL_TASK_PRIORITY_LOW	       (1u << OSAL_TASK_PRIORITY_pos)
#define OSAL_TASK_PRIORITY_NORMAL      (2u << OSAL_TASK_PRIORITY_pos)
#define OSAL_TASK_PRIORITY_HIGH        (3u << OSAL_TASK_PRIORITY_pos)
#define OSAL_TASK_PRIORITY_REALTIME    (4u << OSAL_TASK_PRIORITY_pos)


HTask osalTaskCreate(const TaskInitializeInfo *info);
void osalTaskDestroy(HTask hTask);
void osalTaskSuspend(HTask hTask);
void osalTaskResume(HTask hTask);
void* osalGetPtrData(HTask hTask);
void osalTaskSetPriority(HTask hTask, uint8_t priority);
void osalTaskYield(void);
unsigned osalTaskGetStackHighWaterMark(void);
bool osalTaskWaitNotification(bool clear, unsigned waitTime);
bool osalTaskRaiseNotification(unsigned waitTime);
void osalTaskRaiseNotificationISR(HTask hTask);
HTask osalGetCurrentTask(void);



#ifdef	__cplusplus
}
#endif


#endif // __oisalTask__
