#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosCollection.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


#if defined(eosTickServiceConfig_UseTMR4)
#define __timerId                  TMR_ID_4
#define __intVector                INT_VECTOR_T4  
#define __intSource                INT_SOURCE_TIMER_4 
#define __isrAttributes            __ISR(_TIMER_4_VECTOR, IPL2SOFT)
#else
//#error "No se definio eosTickConfig_UseTMRx"
#endif
#define __intPriority              INT_PRIORITY_LEVEL2
#define __intSubPriority           INT_SUBPRIORITY_LEVEL0


typedef struct __eosTick *eosTickHandle;

typedef enum  {                        // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -Execucio
} eosTickServiceState;

typedef struct __eosTick {             // Dades del callback
    eosTickServiceHandle hService;     // -Handler del servei
    eosTickHandle hNextItem;           // -Seguent item
    eosTickCallback onTick;            // -Event TICK
    void *onTickContext;               // -Parametres del event TICK
} eosTick;

typedef struct __eosTickService {      // Dades del servei
    eosTickServiceState state;         // -Estat
    eosTickHandle hFirstItem;          // -Primer item
} eosTickService;


static eosTickServiceHandle __hService = NULL;


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosTickServiceHandle eosTickServiceInitialize(
 *               eosTickServiceParams *params)
 *
 *       Entrada:
 *           params : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosTickServiceHandle eosTickServiceInitialize(
    eosTickServiceParams *params) {

    if (__hService == NULL) {
        eosTickServiceHandle hService = eosAlloc(sizeof(eosTickService));
        if (hService != NULL) {
            hService->state = serviceInitializing;
            hService->hFirstItem = NULL;
            
            __hService = hService;
        }
    }

    return __hService;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTickServiceTask(
 *               eosTickServiuceHandle hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *************************************************************************/

void eosTickServiceTask(
    eosTickServiceHandle hService) {
    
    switch (hService->state) {
        
        case serviceInitializing:
            PLIB_TMR_Stop(__timerId);
            PLIB_TMR_ClockSourceSelect(__timerId, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
            PLIB_TMR_PrescaleSelect(__timerId, TMR_PRESCALE_VALUE_16);
            PLIB_TMR_Mode16BitEnable(__timerId);
            PLIB_TMR_Counter16BitClear(__timerId);
            PLIB_TMR_Period16BitSet(__timerId, CLOCK_PERIPHERICAL_HZ / 16 / 1000);
            PLIB_INT_VectorPrioritySet(INT_ID_0, __intVector, __intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, __intVector, __intSubPriority);
            PLIB_TMR_Start(__timerId);
            
            hService->state = serviceRunning;
            eosInterruptSourceEnable(__intSource);
            break;

        case serviceRunning:
            break;
    }
}


/*************************************************************************
 *
 *       Asigna una funcio per disparar
 *
 *       Funcio:
 *           void eosTickRegisterCallback(
 *               eosTickServiceHandle hService
 *               eosTickCallback onTick,
 *               void *onTickContext)
 *
 *       Entrada:
 *           hService      : Handler del servei
 *           onTick        : Callback del event TICK
 *           onTickContext : Contexte del event TICK
 *
 *************************************************************************/

void eosTickRegisterCallback(
    eosTickServiceHandle hService,
    eosTickCallback onTick,
    void *onTickContext) {

    if (hService == NULL)
        hService = __hService;
    
    if (hService != NULL) {
        eosTickHandle hTick = eosAlloc(sizeof(eosTick));
        if (hTick != NULL) {

            hTick->hService = hService;
            hTick->onTick = onTick;
            hTick->onTickContext = onTickContext;

            bool enabled = eosInterruptSourceDisable(__intSource);
            
            hTick->hNextItem = hService->hFirstItem;
            hService->hFirstItem = hTick;

            eosInterruptSourceRestore(__intSource, enabled);
        }
    }
}


/*************************************************************************
 *
 *       Bloqueja el servei
 * 
 *       Funcio:
 *           bool eosTickServiceLock(void) 
 *
 *************************************************************************/

bool eosTickServiceLock(void) {

    return eosInterruptSourceDisable(__intSource);
}


/*************************************************************************
 *
 *       Desbloqueja el servei
 * 
 *       Funcio:
 *           bool eosTickServiceUnlock(bool lock) 
 *
 *************************************************************************/

void eosTickServiceUnlock(bool lock) {
    
    eosInterruptSourceRestore(__intSource, lock);
}


/*************************************************************************
 *
 *       Funcio ISR del modul TMRx
 *
 *       Funcio:
 *          void eosTickServiceISR(void)
 *
 *************************************************************************/

void __isrAttributes eosTickServiceISR(void) {

    eosTickHandle hTick = __hService->hFirstItem;
    while (hTick != NULL) {
        if (hTick->onTick != NULL)
            hTick->onTick(hTick->onTickContext);
        hTick = hTick->hNextItem;
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, __intSource);
}
