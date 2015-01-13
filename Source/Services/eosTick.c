#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


// Definicions depenens del temporitzador utilitzat
//
#if eosOPTIONS_TICK_TMR == 1
#define TICK_TIMER_ID             TMR_ID_1
#define TICK_TIMER_INT_VECTOR     INT_VECTOR_T1
#define TICK_TIMER_INT_SOURCE     INT_SOURCE_TIMER_1
#define TICK_TIMER_CORE_VECTOR    _TIMER_1_VECTOR
#elif eosOPTIONS_TICK_TMR == 2
#elif eosOPTIONS_TICK_TMR == 3
#elif eosOPTIONS_TICK_TMR == 4
#define TICK_TIMER_ID             TMR_ID_4
#define TICK_TIMER_INT_VECTOR     INT_VECTOR_T4
#define TICK_TIMER_INT_SOURCE     INT_SOURCE_TIMER_4
#define TICK_TIMER_CORE_VECTOR    _TIMER_4_VECTOR
#else
#error No de declaro la opcion eosOPTIONS_TICK_TMR
#endif


typedef struct __eosTickAttach *eosTickAttachHandle;

typedef enum  {                        // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -Execucio
} eosTickServiceState;

typedef struct __eosTickAttach {       // Funcio adjunta
    eosTickServiceHandle hService;     // -Handler del servei
    eosTickAttachHandle hNextAttach;   // -Seguent adjunt
    eosTickCallback onTick;            // -Event TICK
    void *onTickContext;               // -Parametres del event TICK
} eosTickAttach;

typedef struct __eosTickService {      // Dades internes del servei
    eosTickServiceState state;         // -Estat
    eosTickAttachHandle hFirstAttach;  // -Primer adjunt
} eosTickService;


static eosTickServiceHandle hService = NULL;


static void timerInitialize(void);
static void timerStart(void);
static void timerStop(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           bool eosTickServiceInitialize(
 *               eosTickServiceParams *params)
 *
 *       Entrada:
 *           params : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           True si tot es correcte, false en cas contrari
 *
 *************************************************************************/

bool eosTickServiceInitialize(
    eosTickServiceParams *params) {

    // Comprova que no estigui inicialitzat
    //
    if (hService)
        return false;

    hService = eosAlloc(sizeof(eosTickService));
    if (!hService)
        return false;

    hService->state = serviceInitializing;
    hService->hFirstAttach = NULL;

    return true;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTickServiceTask(void)
 *
 *************************************************************************/

void eosTickServiceTask(void) {

    switch (hService->state) {
        
        case serviceInitializing:
            timerInitialize();
            timerStart();
            hService->state = serviceRunning;
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
 *           bool eosTickAttachFunction(
 *               eosTickCallback onTick,
 *               void *onTickContext)
 *
 *       Entrada:
 *           onTick        : Callback del event TICK
 *           onTickContext : Contexte del event TICK
 *
 *************************************************************************/

bool eosTickAttachFunction(
    eosTickCallback onTick,
    void *onTickContext) {

    eosTickAttachHandle hAttach = eosAlloc(sizeof(eosTickAttach));
    if (hAttach == NULL)
        return false;

    hAttach->hService = hService;
    hAttach->onTick = onTick;
    hAttach->onTickContext = onTickContext;

    bool intState = eosInterruptSourceDisable(TICK_TIMER_INT_SOURCE);
    hAttach->hNextAttach = hService->hFirstAttach;
    hService->hFirstAttach = hAttach;
    eosInterruptSourceRestore(TICK_TIMER_INT_SOURCE, intState);

    return true;
}


/*************************************************************************
 *
 *       Inicialitza el temporitzador
 *
 *       Funcio:
 *           void timerInitialize(void)
 *
 *************************************************************************/

static void timerInitialize(void) {

    PLIB_TMR_Stop(TICK_TIMER_ID);

    // Inicialitza el temporitzador per genera una interrupcio a 1KHz (1ms)
    //
    PLIB_TMR_ClockSourceSelect(TICK_TIMER_ID, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TICK_TIMER_ID, TMR_PRESCALE_VALUE_16);
    PLIB_TMR_Mode16BitEnable(TICK_TIMER_ID);
    PLIB_TMR_Counter16BitClear(TICK_TIMER_ID);
    PLIB_TMR_Period16BitSet(TICK_TIMER_ID, CLOCK_PERIPHERICAL_HZ / 16 / 1000);

    // Configura les interrupcions del temporitzador
    //
    PLIB_INT_VectorPrioritySet(INT_ID_0, TICK_TIMER_INT_VECTOR, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, TICK_TIMER_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
}


/*************************************************************************
 *
 *       Activa el temporitzador, i comença a generar interrupcions
 *
 *       Funcio:
 *           void timerStart(void)
 *
 *************************************************************************/

static void timerStart(void) {

    PLIB_INT_SourceEnable(INT_ID_0, TICK_TIMER_INT_SOURCE);
    PLIB_TMR_Start(TICK_TIMER_ID);
}


/*************************************************************************
 *
 *       Descativa el temporitzador
 *
 *       Funcio:
 *           void timerStop(void)
 *
 *************************************************************************/

static void timerStop(void) {

    PLIB_TMR_Stop(TICK_TIMER_ID);
    PLIB_INT_SourceDisable(INT_ID_0, TICK_TIMER_INT_SOURCE);
}


/*************************************************************************
 *
 *       Gestiona la interrupcio del temporitzador
 *
 *************************************************************************/

void __ISR(TICK_TIMER_CORE_VECTOR, IPL2SOFT) __ISR_Entry(TICK_TIMER_CORE_VECTOR) {

    if (hService->state == serviceRunning) {

        eosTickAttachHandle hAttach = hService->hFirstAttach;
        while (hAttach) {
            if (hAttach->onTick != NULL)
                hAttach->onTick(hAttach->onTickContext);
            hAttach = hAttach->hNextAttach;
        }
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, TICK_TIMER_INT_SOURCE);
}
