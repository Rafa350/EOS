#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "HardwareProfile.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


// Definicions depenens del temporitzador utilitzat
//
#if eosOPTIONS_TICK_TMR == 1
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


typedef enum  {                        // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -Execucio
} ServiceStates;

typedef struct __Attach {              // Funcio adjunta
    eosHTickService hService;          // -Servei al que pertany
    struct __Attach *nextAttach;       // -Seguent adjunt
    eosTickCallback onTick;            // -Event TICK
    void *onTickContext;               // -Parametres del event TICK
} Attach;

typedef struct __eosTickService {      // Dades internes del servei
    ServiceStates state;               // -Estat
    unsigned maxAttaches;              // -Numero maxim d'adjunts
    Attach *firstAttach;               // -Primer adjunt
} TickService;


// Definicio de functions locals
//
static void timerInitialize(void);
static void timerStart(void);
static void timerStop(void);
static bool disableInterrupt(void);
static void enableInterrupt(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosHTickService eosTickServiceInitialize(
 *               eosTickServiceParams *params)
 *
 *       Entrada:
 *           params : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosHTickService eosTickServiceInitialize(
    eosTickServiceParams *params) {

    eosHTickService hService = (eosHTickService) eosAlloc(sizeof(TickService));
    if (hService) {

        hService->state = serviceInitializing;
        hService->firstAttach = NULL;

        timerInitialize();
    }
    return hService;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTickServiceTask(
 *               eosHTickService hService)
 *
 *       Entrada:
 *           service : El handler del servei
 *
 *************************************************************************/

void eosTickServiceTask(
    eosHTickService hService) {

    switch (hService->state) {
        case serviceInitializing:
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
 *           void eosTickAttach(
 *               eosHTickService hService
 *               eosTickCallback onTick,
 *               void *onTickContext)
 *
 *       Entrada:
 *           hService      : El servei
 *           onTick        : Callback del event TICK
 *           onTickContext : Contexte del event TICK
 *
 *************************************************************************/

void eosTickAttach(
    eosHTickService hService,
    eosTickCallback onTick,
    void *onTickContext) {

    Attach *attach = eosAlloc(sizeof(Attach));
    if (attach) {

        attach->onTick = onTick;
        attach->onTickContext = onTickContext;

        // Entra en la seccio critica
        //
        BOOL intFlag = disableInterrupt();

        attach->hService = hService;
        attach->nextAttach = hService->firstAttach;
        hService->firstAttach = attach;

        // Surt de la seccio critica
        //
        if (intFlag)
            enableInterrupt();
    }
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

    eosHTickService hService = eosGetTickServiceHandle();
    if (hService != NULL) {
        Attach *attach = hService->firstAttach;
        while (attach) {
            if (attach->onTick != NULL)
                attach->onTick(attach->onTickContext);
            attach = attach->nextAttach;
        }
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, TICK_TIMER_INT_SOURCE);
}


/*************************************************************************
 *
 *       Desactiva la interrupcio
 *
 *       Funcio:
 *           bool disableInterrupt(void)
 *
 *       Retorn:
 *           Estat anterior de la interrupcio
 *
 *************************************************************************/

static bool disableInterrupt(void) {
    
    bool intFlag = PLIB_INT_SourceIsEnabled(INT_ID_0, TICK_TIMER_INT_SOURCE);
    PLIB_INT_SourceDisable(INT_ID_0, TICK_TIMER_INT_SOURCE);
    return intFlag;
}


/*************************************************************************
 *
 *       Activa la interrupcio
 *
 *       Funcio:
 *           void enableInterrupt(void)
 *
 *************************************************************************/

static void enableInterrupt(void) {

    PLIB_INT_SourceEnable(INT_ID_0, TICK_TIMER_INT_SOURCE);
}
