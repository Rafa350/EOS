#ifndef __EOS_TASK_H
#define __EOS_TASK_H


typedef void *eosTaskHandle;
typedef void (*eosTaskFunction)(void *params);

extern eosTaskHandle eosTaskCreate(unsigned priority, unsigned stackSize, 
    eosTaskFunction taskFunction, void *taskParams);
extern void eosTaskRun(void);

extern void eosTaskEnterCriticalSection(void);
extern void eosTaskExitCriticalSection(void);
extern void eosTaskSuspendAll(void);
extern void eosTaskResumeAll(void);

extern void eosTaskDelay(unsigned delay);
extern void eosTaskDelayUntil(unsigned delay, unsigned *lastTick);
extern unsigned eosTaskGetTickCount(void);
    

#endif
