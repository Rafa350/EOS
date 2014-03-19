#include "Modules/Plc/eosPlc.h"


#ifdef eosUSE_TIMERS

#if !defined(eosCFG_TIMERS_NumTimers) || (eosCFG_TIMERS_NumTimers < 1) || (eosCFG_TIMERS_NumTimers > 64)
#error 'eosPLC_NumTimers' ha de estar en el intervalo 1..64
#endif


typedef struct {
    unsigned counter;
    unsigned state:1;
    unsigned pause:1;
} TIMERINFO;

static TIMERINFO timers[eosCFG_TIMERS_NumTimers];


/*************************************************************************
 *
 *       Inicialitza els temporitzadors
 *
 *       Funcio:
 *           void sysTimInitialize(void)
 *
 *************************************************************************/

void sysTimInitialize(void){

    UINT8 id = eosCFG_TIMERS_NumTimers - 1;
    do {

        TIMERINFO *t = &timers[id];
        t->counter = 0;
        t->state = FALSE;
        t->pause = FALSE;
    
    } while (id--);
}


/*************************************************************************
 *
 *       Tasca de control dels temporitzadors. Es crida cada 1ms
 *
 *       Funcio:
 *           void sysTimTickInterrupt(void)
 *
 *************************************************************************/

void sysTimTickInterrupt(void) {

    UINT8 id = eosCFG_TIMERS_NumTimers - 1;
    do {

        TIMERINFO *t = &timers[id];
        if (!t->pause && t->counter)
            t->counter--;

    } while (id--);
}


/*************************************************************************
 *
 *       Tasca de control dels temporitzadors. Es crida en cada cicle
 *
 *       Funcio:
 *           void sysTimLoop(void)
 *
 *************************************************************************/

void sysTimLoop(void) {

    UINT8 id = eosCFG_TIMERS_NumTimers - 1;
    do {

        TIMERINFO *t = &timers[id];

        eosDisableInterrupts();

        if (!t->counter)
            t->state = TRUE;

        eosEnableInterrupts();
        
    } while (id--);
}


/*************************************************************************
 *
 *       Inicia un temporitzador
 *
 *       Funcio:
 *           void eosTimStart(UINT8 timerId, unsigned time)
 *
 *       Entrada:
 *           id  : Numero de temporitzador
 *           time: Temps en milsegons
 *
 *************************************************************************/

void eosTimStart(UINT8 id, unsigned time) {

    if (id < eosCFG_TIMERS_NumTimers) {

        eosDisableInterrupts();
        
        TIMERINFO *t = &timers[id];
        t->counter = time;
        t->state = FALSE;
        t->pause = FALSE;
        
        eosEnableInterrupts();
    }
}


/*************************************************************************
 *
 *       Posa un temporitzador en pausa
 *
 *       Funcio:
 *           void eosTimPause(UINT8 id)
 *
 *       Entrada:
 *           id: Numero de temporitzador
 *
 *************************************************************************/

void eosTimPause(UINT8 id) {

    if (id < eosCFG_TIMERS_NumTimers) {

        eosDisableInterrupts();

        timers[id].pause = TRUE;

        eosEnableInterrupts();
    }
}


/*************************************************************************
 *
 *       Treu el temporitzador del estat pausat
 *
 *       Funcio:
 *           void eosTimContinue(UINT8 id)
 *
 *       Entrada:
 *           id: Numero de temporitzador
 *
 *************************************************************************/

void eosTimContinue(UINT8 id) {

    if (id < eosCFG_TIMERS_NumTimers) {

        eosDisableInterrupts();

        timers[id].pause = FALSE;
        
        eosEnableInterrupts();
    }
}


/*************************************************************************
 *
 *       Obte l'estat d'un temporitzador
 *
 *       Funcio:
 *           BOOL eosTimGet(UINT8 id)
 *
 *       Entrada:
 *           id: Numero de temporitzador
 *
 *       Retorn:
 *           TRUE si ha pasat el temps programat. FALSE en cas contrari
 *
 *************************************************************************/

BOOL eosTimGet(UINT8 id) {

    if (id < eosCFG_TIMERS_NumTimers)
        return timers[id].state;
    else
        return FALSE;
}


#endif
