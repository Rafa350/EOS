#ifndef __EOS_TASK_H
#define __EOS_TASK_H


typedef void *eosTaskHandle;
typedef void (*eosTaskFunction)(void *params);

typedef enum {                         // Nivell de severitat de la seccio critica
    eosCriticalSectionSeverityLow,     // -Desactiva els canvi de tasca
    eosCriticalSectionSeverityHigh,    // -Desactiva el canvi de tasca i les interrupcions
} eosCriticalSectionSeverity;

typedef struct {                       // Informacio de recuperacio de la seccio critica   
    eosCriticalSectionSeverity severity;    // -Nivel de severitat
} eosCriticalSectionInfo;

typedef enum {                         // Estat del planificador de tasques
    eosSchedulerStateNotStarted,       // -No iniciat
    eosSchedulerStateRunning,          // -En execucio
    eosSchedulerStateSuspended         // -En suspensio
} eosSchedulerState;


// Gestio de tasques
//
extern eosTaskHandle eosTaskCreate(unsigned priority, unsigned stackSize, 
    eosTaskFunction taskFunction, void *taskParams);
extern void eosTaskDelay(unsigned delay);
extern void eosTaskDelayUntil(unsigned delay, unsigned *lastTick);

// Gestio del planificador
//
extern void eosStartScheduler();
extern eosSchedulerState eosGetSchedulerState(void);
extern unsigned eosTaskTickCount(void);

// Gestio de les secciona critiques
//
extern void eosEnterCriticalSection(eosCriticalSectionSeverity severity, eosCriticalSectionInfo *info);
extern void eosLeaveCriticalSection(eosCriticalSectionInfo *info);
    

#endif
