#ifndef __FreeRTOSConfig_H
#define	__FreeRTOSConfig_H


#include "HardwareProfile.h"


#define configUSE_PREEMPTION			1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configTICK_RATE_HZ			((portTickType) 1000)
#define configCPU_CLOCK_HZ			((unsigned long) GetSystemCLock())
#define configPERIPHERAL_CLOCK_HZ		((unsigned long) GetPeripheralClock())
#define configMAX_PRIORITIES			((unsigned portBASE_TYPE) 5)
#define configMINIMAL_STACK_SIZE		(190)
#define configISR_STACK_SIZE			(400)
#define configTOTAL_HEAP_SIZE			((size_t) 28000)
#define configMAX_TASK_NAME_LEN			(8)
#define configUSE_TRACE_FACILITY		0
#define configUSE_16_BIT_TICKS			0
#define configIDLE_SHOULD_YIELD			1
#define configUSE_MUTEXES			1
#define configCHECK_FOR_STACK_OVERFLOW          2
#define configQUEUE_REGISTRY_SIZE		0
#define configTICK_INTERRUPT_VECTOR             _TIMER_5_VECTOR


/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			(0)
#define configMAX_CO_ROUTINE_PRIORITIES         (2)

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete			0
#define INCLUDE_vTaskCleanUpResources		0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay			1
#define INCLUDE_uxTaskGetStackHighWaterMark	1

/* The priority at which the tick interrupt runs.  This should probably be
kept at 1. */
#define configKERNEL_INTERRUPT_PRIORITY		0x01

/* The maximum interrupt priority from which FreeRTOS.org API functions can
be called.  Only API functions that end in ...FromISR() can be used within
interrupts. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY	0x03


#endif	

