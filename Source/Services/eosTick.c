#include "Services/__eosTick.h"
#include "System/eosMemory.h"
#include "HardwareProfile.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


// Definicions depenens del temporitzador utilitzat
//
#define TIMER_ID             TMR_ID_4
#define TIMER_INT_VECTOR     INT_VECTOR_T4
#define TIMER_INT_SOURCE     INT_SOURCE_TIMER_4
#define TIMER_CORE_VECTOR    _TIMER_4_VECTOR



// Definicio de variables locals
//
static eosTickService* isrService = NULL;


// Definicio de functions locals
//
static void InitTimer(void);
static void StartTimer(void);
static void StopTimer(void);
static BOOL DisableInterrupt(void);
static void EnableInterrupt(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosTickService* eosTickServiceInitialize(
 *               eosTickServiceParams *params)
 *
 *       Entrada:
 *           params : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El servei, NULL en cas d'error
 *
 *************************************************************************/

eosTickService* eosTickServiceInitialize(eosTickServiceParams *params) {

    eosTickService* service = eosAlloc(sizeof(eosTickService) + sizeof(struct __ATTACH) * params->maxAttaches);
    if (service) {

        service->state = SS_INITIALIZING;
        service->maxAttaches = params->maxAttaches;
        service->attaches = (struct __ATTACH*)((BYTE*) service + sizeof(eosTickService));

        unsigned i;
        for (i = 0; i < service->maxAttaches; i++)
            service->attaches[i].callback = NULL;

        InitTimer();
    }

    return service;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosTickServiceTask(
 *               eosTickService* service)
 *
 *       Entrada:
 *           service : El servei
 *
 *************************************************************************/

void eosTickServiceTask(eosTickService* service) {

    switch (service->state) {
        case SS_INITIALIZING:
            isrService = service;
            StartTimer();
            service->state = SS_RUNNING;
            break;

        case SS_RUNNING:
            break;
    }
}


/*************************************************************************
 *
 *       Asigna una funcio per disparar
 *
 *       Funcio:
 *           void eosTickAttach(
 *               eosTickService* service
 *               eosCallback callback,
 *               void *context,
 *               eosHandle *hAttach)
 *
 *       Entrada:
 *           service  : El servei
 *           callback : Funcio a asignar
 *           context  : Contexte
 *
 *************************************************************************/

void eosTickAttach(eosTickService* service, eosCallback callback, void *context) {


    // Entra en la seccio critica
    //
    BOOL intFlag = DisableInterrupt();

    // Asigna la funcio
    //
    unsigned i;
    for (i = 0; i < service->maxAttaches; i++) {
        struct __ATTACH *attach = &service->attaches[i];
        if (attach->callback == NULL) {
            attach->callback = callback;
            attach->context = context;
            break;
        }
    }
    
    // Surt de la seccio critica
    //
    if (intFlag)
        EnableInterrupt();
}


/*************************************************************************
 *
 *       Inicialitza el temporitzador
 *
 *       Funcio:
 *           void InitTimer(void)
 *
 *************************************************************************/

static void InitTimer(void) {

    PLIB_TMR_Stop(TIMER_ID);

    // Inicialitza el temporitzador per genera una interrupcio a 1KHz (1ms)
    //
    PLIB_TMR_ClockSourceSelect(TIMER_ID, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TIMER_ID, TMR_PRESCALE_VALUE_16);
    PLIB_TMR_Mode16BitEnable(TIMER_ID);
    PLIB_TMR_Counter16BitClear(TIMER_ID);
    PLIB_TMR_Period16BitSet(TIMER_ID, CLOCK_PERIPHERICAL_HZ / 16 / 1000);

    // Configura les interrupcions del temporitzador
    //
    PLIB_INT_VectorPrioritySet(INT_ID_0, TIMER_INT_VECTOR, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, TIMER_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
}


/*************************************************************************
 *
 *       Activa el temporitzador, i comença a generar interrupcions
 *
 *       Funcio:
 *           void StartTimer(void) 
 *
 *************************************************************************/

static void StartTimer(void) {

    PLIB_INT_SourceEnable(INT_ID_0, TIMER_INT_SOURCE);
    PLIB_TMR_Start(TIMER_ID);
}


/*************************************************************************
 *
 *       Descativa el temporitzador
 *
 *       Funcio:
 *           void StopTimer(void)
 *
 *************************************************************************/

static void StopTimer(void) {

    PLIB_TMR_Stop(TIMER_ID);
    PLIB_INT_SourceDisable(INT_ID_0, TIMER_INT_SOURCE);
}


/*************************************************************************
 *
 *       Gestiona la interrupcio del temporitzador
 *
 *       Funcio:
 *           void eosTickTMRInterruptService(void)
 *
 *************************************************************************/

void __ISR(TIMER_CORE_VECTOR, ipl2) eosTickTMRInterruptService(void) {

    if (isrService != NULL) {
        int i;
        for (i = 0; i < isrService->maxAttaches; i++) {
            struct __ATTACH *attach = &isrService->attaches[i];
            if (attach->callback != NULL)
                attach->callback(attach->context);
        }
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, TIMER_INT_SOURCE);
}


/*************************************************************************
 *
 *       Desactiva la interrupcio
 *
 *       Funcio:
 *           BOOL DisableInterrupt(void)
 *
 *       Retorn:
 *           Estat anterior de la interrupcio
 *
 *************************************************************************/

static BOOL DisableInterrupt(void) {
    
    BOOL intFlag = PLIB_INT_SourceIsEnabled(INT_ID_0, TIMER_INT_SOURCE);
    PLIB_INT_SourceDisable(INT_ID_0, TIMER_INT_SOURCE);
    return intFlag;
}


/*************************************************************************
 *
 *       Activa la interrupcio
 *
 *       Funcio:
 *           void EnableInterrupt(void)
 *
 *************************************************************************/

static void EnableInterrupt(void) {

    PLIB_INT_SourceEnable(INT_ID_0, TIMER_INT_SOURCE);
}
