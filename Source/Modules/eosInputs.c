#include "Modules/Plc/eosPlc.h"


#ifdef eosUSE_INPUTS


#if !defined(eosCFG_INPUTS_NumInputs) || (eosCFG_INPUTS_NumInputs < 1) || (eosCFG_INPUTS_NumInputs > 32)
#error 'eosCFG_INPUTS_NumInputs' ha de estar en el intervalo 1..32
#endif


#define PATTERN_ON    0x7FFF
#define PATTERN_OFF   0x8000
#define PATTERN_MASK  0xFFFF

typedef struct {
    UINT16 pattern;
    unsigned state:1;
    unsigned posEdge:1;
    unsigned negEdge:1;
} PORTINFO;

static PORTINFO ports[eosCFG_INPUTS_NumInputs];

extern void halInpInitialize(void);
extern BOOL halInpPortRead(UINT8 id);


/*************************************************************************
 *
 *       Inicialitzacio del modul
 *
 *       Funcio:
 *           void sysInpInitialize(void)
 *
 *************************************************************************/

void sysInpInitialize(void) {

    halInpInitialize();

    UINT8 id = eosCFG_INPUTS_NumInputs - 1;
    do {

        PORTINFO *p = &ports[id];
        p->pattern = 0;
        p->state = FALSE;
        p->posEdge = FALSE;
        p->negEdge = FALSE;

    } while (id--);
}


/*************************************************************************
 *
 *       Interrupcio Tick del modul
 *
 *       Funcio:
 *           void sysInpTickInterrupt(void)
 *
 *************************************************************************/

void sysInpTickInterrupt(void) {

    UINT8 id = eosCFG_INPUTS_NumInputs - 1;
    do {

        PORTINFO *p = &ports[id];
        p->pattern = (p->pattern << 1) | (halInpPortRead(id) ? 1 : 0);
    
    } while (id--);
}


/*************************************************************************
 *
 *       Gestio del modul
 *
 *       Funcio:
 *           void sysInpLoop(void)
 *
 *************************************************************************/

void sysInpLoop(void) {

    UINT8 id = eosCFG_INPUTS_NumInputs - 1;
    do {

        eosDisableInterrupts();

        PORTINFO *p = &ports[id];
        UINT16 pattern = p->pattern & PATTERN_MASK;
        if (pattern == PATTERN_OFF) {
            p->state = FALSE;
            p->negEdge = TRUE;
        }
        else if (pattern == PATTERN_ON) {
            p->state = TRUE;
            p->posEdge = TRUE;
        }

        eosEnableInterrupts();

    } while (id--);
}


/*************************************************************************
 *
 *       Obte l'estat d'una entrada
 *
 *       Funcio:
 *           BOOL eosInpGet(UINT8 id)
 *
 *       Entrada:
 *           id: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si esta en estat actiu (ON), FALSE en cas contrari
 *
 *************************************************************************/

BOOL eosInpGet(UINT8 id) {

    if (id < eosCFG_INPUTS_NumInputs)
        return ports[id].state;
    else
        return FALSE;
}


/*************************************************************************
 *
 *       Detecta si ha arribat un flanc positiu a una entrada
 *
 *       Funcio:
 *           BOOL eosInpPosEdge(UINT8 id)
 *
 *       Entrada:
 *           id: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si s'ha detectat un flanc positiu
 *
 *       Notes:
 *           Un cop es crida a la funcio, aquesta no retornara TRUE, fins
 *           que arribi un altre flanc positiu
 *
 *************************************************************************/

BOOL eosInpPosEdge(UINT8 id) {

    if (id < eosCFG_INPUTS_NumInputs) {

        PORTINFO *p = &ports[id];
        BOOL result = p->posEdge;
        p->posEdge = FALSE;

        return result;
    }
    else
        return FALSE;
}


/*************************************************************************
 *
 *       Detecta si ha arribat un flanc negatiu a una entrada
 *
 *       Funcio:
 *           BOOL eosInpNegEdge(UINT8 id)
 *
 *       Entrada:
 *           id: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si s'ha detectat un flanc negatiu
 *
 *       Notes:
 *           Un cop es crida a la funcio, aquesta no retornara TRUE, fins
 *           que arribi un altre flanc negatiu
 *
 *************************************************************************/

BOOL eosInpNegEdge(UINT8 id) {

    if (id < eosCFG_INPUTS_NumInputs) {

        PORTINFO *p = &ports[id];
        BOOL result = p->negEdge;
        p->negEdge = FALSE;

        return result;
    }
    else
        return FALSE;
}


/*************************************************************************
 *
 *       Reseteja el detector de flancs per aquesta entrada
 *
 *       Funcio:
 *           void eosInpClearEdge(UINT8 id)
 *
 *       Entrada:
 *           id: Numero d'entrada
 *
 *************************************************************************/

void eosInpClearEdge(UINT8 id) {

    if (id < eosCFG_INPUTS_NumInputs) {
        
        PORTINFO *p = &ports[id];
        p->posEdge = FALSE;
        p->negEdge = FALSE;
    }
}


#endif