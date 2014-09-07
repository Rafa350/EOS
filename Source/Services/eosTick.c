#include "System/eosMemory.h"
#include "Services/eosTick.h"
#include "HardwareProfile.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/tmr/plib_tmr.h"


#define TIMER_ID             TMR_ID_4
#define TIMER_INT_VECTOR     INT_VECTOR_T4
#define TIMER_INT_SOURCE     INT_SOURCE_TIMER_4
#define TIMER_CORE_VECTOR    _TIMER_4_VECTOR

#define MAX_ATTACHES         10   // Numero maxim de callbacks

typedef enum  {                   // Estat del servei
    STATE_INITIALIZE,             // -Inicialitza
    STATE_TERMINATE,              // -Finalitza
    STATE_ACTIVE,                 // -Actiu
} State;

typedef struct {                  // Funcios adjuntes
    eosTickCallback callback;     // -Funcio
    void *context;                // -Contexte
} Attach, *PAttach;

typedef struct {                  // Dades internes
    State state;                  // -Estat
    BOOL terminate;               // -Indica si cal acabar
    unsigned maxAttaches;         // -Numero maxim d'adjunts
    Attach attaches[MAX_ATTACHES];// -llista d'adjunts
} Data, *PData;


static PData data = NULL;


static void InitTimer(void);
static void StartTimer(void);
static void StopTimer(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosResult eosTickInitialize(void)
 *
 *       Retorn:
 *           eos_RETURN_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickInitialize(void) {

    data = eosAlloc(sizeof(Data));
    if (data == NULL)
        return eos_ERROR_ALLOC;

    data->state = STATE_INITIALIZE;
    data->terminate = FALSE;
    data->maxAttaches = MAX_ATTACHES;
    memset(data->attaches, 0, sizeof(data->attaches));

    InitTimer();

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Finalitza el servei
 *
 *       Funcio:
 *           eosResult eosTimerTerminate(void)
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickTerminate(void) {

    data->terminate = TRUE;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           eosResult eosTickTask(void)
 *
 *       Return:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickTask(void) {

    switch (data->state) {
        case STATE_INITIALIZE:
            StartTimer();
            data->state = STATE_ACTIVE;
            break;

        case STATE_TERMINATE:
            //eosFree(data);
            break;

        case STATE_ACTIVE: {
            if (data->terminate) {
                StopTimer();
                data->state = STATE_TERMINATE;
            }
            break;
        }
    }

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Asigna una funcio per disparar
 *
 *       Funcio:
 *           eosResult eosTickAttach(eosTickCallback callback, void *context)
 *
 *       Entrada:
 *           callback: Funcio a asignar
 *           context : Contexte
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *       Notes:
 *           La funcio es crida en el contexte ISR
 *
 *************************************************************************/

eosResult eosTickAttach(eosTickCallback callback, void *context) {

    int i;

    if (callback == NULL)
        return eos_ERROR_PARAMS;

    eosDisableInterrupts();
    for (i = 0; i < data->maxAttaches; i++) {
        PAttach pAttach = &data->attaches[i];
        if (pAttach->callback == NULL) {
            pAttach->callback = callback;
            pAttach->context = context;
            break;
        }
    }
    eosEnableInterrupts();

    return i == data->maxAttaches ? eos_ERROR_INVALID : eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Desasigna una funcio
 *
 *       Funcio:
 *           eosResult eosTickUnAttach(eosTickCallback callback)
 *
 *       Entrada:
 *           callback: La funcio
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosTickUnAttach(eosTickCallback callback) {

    int i;
    
    if (callback == NULL)
        return eos_ERROR_PARAMS;

    eosDisableInterrupts();
    for (i = 0; i < data->maxAttaches; i++) {
        PAttach pAttach = &data->attaches[i];
        if (pAttach->callback == callback) {
            pAttach->callback = NULL;
            return eos_RESULT_SUCCESS;
        }
    }
    eosEnableInterrupts();

    return eos_ERROR_INVALID;
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
    PLIB_INT_SourceEnable(INT_ID_0, TIMER_INT_SOURCE);
    PLIB_INT_VectorPrioritySet(INT_ID_0, TIMER_INT_VECTOR, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, TIMER_INT_VECTOR, INT_SUBPRIORITY_LEVEL0);
}


/*************************************************************************
 *
 *       Activa el temporitzador, i comença a generar interrupcions
 *
 *       Funcio:
 *           void StartTimer(void) {
 *
 *************************************************************************/

static void StartTimer(void) {

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
}


/*************************************************************************
 *
 *       Gestiona la interrupcio del temporitzador
 *
 *       Funcio:
 *           eosTickTMRInterruptService(void)
 *
 *************************************************************************/

void __ISR(TIMER_CORE_VECTOR, ipl2) eosTickTMRInterruptService(void) {

    int i;
    for (i = 0; i < data->maxAttaches; i++) {
        PAttach pAttach = &data->attaches[i];
        if (pAttach->callback != NULL)
            pAttach->callback(pAttach->context);
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, TIMER_INT_SOURCE);
}
