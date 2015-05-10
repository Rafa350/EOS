#include "Services/eosTick.h"
#include "System/eosMemory.h"
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
    unsigned timer;                    // -Temporitzador
} eosTickService;


static eosTickServiceHandle serviceMap[5];
static eosTickServiceHandle hDefaultService = NULL;
static bool initialized = false;


static void timerInitialize(unsigned timer);
static void timerInterruptCallback(unsigned timer);


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

    // Comprova que no estigui inicialitzat
    //
    if (initialized)
        return NULL;

    eosTickServiceHandle hService = eosAlloc(sizeof(eosTickService));
    if (!hService)
        return NULL;

    hService->timer = params->timer;
    hService->state = serviceInitializing;
    hService->hFirstItem = NULL;

    initialized = true;

    serviceMap[hService->timer] = hService;
    if (hDefaultService == NULL)
        hDefaultService = hService;

    return hService;
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
            timerInitialize(hService->timer);
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
 *           bool eosTickRegisterCallback(
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

bool eosTickRegisterCallback(
    eosTickServiceHandle hService,
    eosTickCallback onTick,
    void *onTickContext) {

    if (hService == NULL)
        hService = hDefaultService;

    eosTickHandle hTick = eosAlloc(sizeof(eosTick));
    if (hTick == NULL)
        return false;

    hTick->hService = hService;
    hTick->onTick = onTick;
    hTick->onTickContext = onTickContext;

    bool intState = eosInterruptSourceDisable(TICK_TIMER_INT_SOURCE);
    hTick->hNextItem = hService->hFirstItem;
    hService->hFirstItem = hTick;
    eosInterruptSourceRestore(TICK_TIMER_INT_SOURCE, intState);

    return true;
}


/*************************************************************************
 *
 *       Inicialitza el temporitzador
 *
 *       Funcio:
 *           void timerInitialize(
 *               unsigned timer)
 *
 *       Entrada:
 *           timer: Identificador del temporitzador
 *
 *************************************************************************/

static void timerInitialize(
    unsigned timer) {

    halTimerStop(timer);

    // Inicialitza el temporitzador per genera una interrupcio a 1KHz (1ms)
    //
    PLIB_TMR_ClockSourceSelect(TICK_TIMER_ID, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TICK_TIMER_ID, TMR_PRESCALE_VALUE_16);
    PLIB_TMR_Mode16BitEnable(TICK_TIMER_ID);
    PLIB_TMR_Counter16BitClear(TICK_TIMER_ID);
    PLIB_TMR_Period16BitSet(TICK_TIMER_ID, CLOCK_PERIPHERICAL_HZ / 16 / 1000);

    // Configura les interrupcions del temporitzador
    //
    halTimerSetInterruptPriority(timer, 2, 0);
    halTimerSetInterruptEnable(timer, true);
    halTimerSetInterruptCallback(timer, timerInterruptCallback);
    halTimerStart(timer);
}


/*************************************************************************
 *
 *       Gestiona la interrupcio del temporitzador
 *
 *       Funcio:
 *           void timerInterruptCallback(
 *               unsigned timer)
 *
 *       Entrada:
 *           timer: Identificador del temporitzador
 *
 *************************************************************************/

static void timerInterruptCallback(unsigned timer) {

    eosTickServiceHandle hService = serviceMap[timer];
    if (hService && (hService->state == serviceRunning)) {

        eosTickHandle hTick = hService->hFirstItem;
        while (hTick) {
            if (hTick->onTick != NULL)
                hTick->onTick(hTick->onTickContext);
            hTick = hTick->hNextItem;
        }
    }
}
