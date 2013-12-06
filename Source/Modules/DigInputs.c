#include "eos.h"


#ifdef EOS_USE_INPUTS


#if !defined(EOS_NUM_INPUTS) || (EOS_NUM_INPUTS < 1) || (EOS_NUM_INPUTS > 32)
#error 'EOS_NUM_INPUTS' ha de estar en el intervalo 1..32
#endif


typedef struct {
    UINT16 pattern;
    unsigned state:1;
    unsigned posEdge:1;
    unsigned negEdge:1;
} PORTINFO;

static PORTINFO ports[EOS_NUM_INPUTS];


/*************************************************************************
 *
 *       Inicialitza la gestio de les entrades
 *
 *       Funcio:
 *           void sysInpInitialize(void)
 *
 *************************************************************************/

void sysInpInitialize(void) {

    __halInpInitialize();

    UINT8 inputId = EOS_NUM_INPUTS - 1;
    do {

        PORTINFO *p = &ports[inputId];
        p->pattern = 0;
        p->state = FALSE;
        p->posEdge = FALSE;
        p->negEdge = FALSE;

    } while (inputId--);
}


/*************************************************************************
 *
 *       Interrupcio Tick
 *
 *       Funcio:
 *           void sysInpTickInterrupt(void)
 *
 *************************************************************************/

void sysInpTickInterrupt(void) {

    UINT8 inputId = EOS_NUM_INPUTS - 1;
    do {

        PORTINFO *p = &ports[inputId];
        p->pattern = (p->pattern << 1) | __halInpRead(inputId);

    } while (inputId--);
}


/*************************************************************************
 *
 *       Tasca de control de les entrades. Es crida cada cicle
 *
 *       Funcio:
 *           void sysInpLoop(void)
 *
 *************************************************************************/

void sysInpLoop(void) {

    UINT8 inputId = EOS_NUM_INPUTS - 1;
    do {

        eosDisableInterrupts();

        PORTINFO *p = &ports[inputId];
        if (p->pattern == 0xFF00) {
            p->state = FALSE;
            p->negEdge = TRUE;
        }
        else if (p->pattern == 0x00FF) {
            p->state = TRUE;
            p->posEdge = TRUE;
        }

        eosEnableInterrupts();

    } while (inputId--);
}


/*************************************************************************
 *
 *       Obte l'estat d'una entrada
 *
 *       Funcio:
 *           BOOL eosInpGet(UINT8 inputId)
 *
 *       Entrada:
 *           inputId: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si esta en estat actiu (ON), FALSE en cas contrari
 *
 *************************************************************************/

BOOL eosInpGet(UINT8 inputId) {

    if (inputId < EOS_NUM_INPUTS)
        return ports[inputId].state;
    else
        return FALSE;
}


/*************************************************************************
 *
 *       Detecta si ha arribat un flanc positiu a una entrada
 *
 *       Funcio:
 *           BOOL eosInpPosEdge(UINT8 inputId)
 *
 *       Entrada:
 *           inputId: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si s'ha detectat un flanc positiu
 *
 *       Notes:
 *           Un cop es crida a la funcio, aquesta no retornara TRUE, fins
 *           que arribi un altre flanc positiu
 *
 *************************************************************************/

BOOL eosInpPosEdge(UINT8 inputId) {

    if (inputId < EOS_NUM_INPUTS) {

        PORTINFO *p = &ports[inputId];
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
 *           BOOL eosInpNegEdge(UINT8 inputId)
 *
 *       Entrada:
 *           inputId: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si s'ha detectat un flanc negatiu
 *
 *       Notes:
 *           Un cop es crida a la funcio, aquesta no retornara TRUE, fins
 *           que arribi un altre flanc negatiu
 *
 *************************************************************************/

BOOL eosInpNegEdge(UINT8 inputId) {

    if (inputId < EOS_NUM_INPUTS) {

        PORTINFO *p = &ports[inputId];
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
 *           void eosInpClearEdge(UINT8 inputId)
 *
 *       Entrada:
 *           inputId: Numero d'entrada
 *
 *************************************************************************/

void eosInpClearEdge(UINT8 inputId) {

    if (inputId < EOS_NUM_INPUTS) {
        
        PORTINFO *p = &ports[inputId];
        p->posEdge = FALSE;
        p->negEdge = FALSE;
    }
}


#endif
