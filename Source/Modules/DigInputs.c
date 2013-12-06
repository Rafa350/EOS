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

    UINT8 inp = EOS_NUM_INPUTS - 1;
    do {

        PORTINFO *p = &ports[inp];
        p->pattern = 0;
        p->state = FALSE;
        p->posEdge = FALSE;
        p->negEdge = FALSE;

    } while (inp--);
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

    UINT8 inp = EOS_NUM_INPUTS - 1;
    do {

        PORTINFO *p = &ports[inp];
        p->pattern = (p->pattern << 1) | __halInpRead(inp);

    } while (inp--);
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

    eosDisableInterrupts();

    UINT8 inp = EOS_NUM_INPUTS - 1;
    do {

        PORTINFO *p = &ports[inp];
        if (p->pattern == 0xFF00) {
            p->state = FALSE;
            p->negEdge = TRUE;
        }
        else if (p->pattern == 0x00FF) {
            p->state = TRUE;
            p->posEdge = TRUE;
        }

    } while (inp--);

    eosEnableInterrupts();
}


/*************************************************************************
 *
 *       Obte l'estat d'una entrada
 *
 *       Funcio:
 *           BOOL eosInpGet(UINT8 inp)
 *
 *       Entrada:
 *           inp: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si esta en estat actiu (ON), FALSE en cas contrari
 *
 *************************************************************************/

BOOL eosInpGet(UINT8 inp) {

    if (inp < EOS_NUM_INPUTS)
        return ports[inp].state;
    else
        return FALSE;
}


/*************************************************************************
 *
 *       Detecta si ha arribat un flanc positiu a una entrada
 *
 *       Funcio:
 *           BOOL eosInpPosEdge(UINT8 inp)
 *
 *       Entrada:
 *           inp: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si s'ha detectat un flanc positiu
 *
 *       Notes:
 *           Un cop es crida a la funcio, aquesta no retornara TRUE, fins
 *           que arribi un altre flanc positiu
 *
 *************************************************************************/

BOOL eosInpPosEdge(UINT8 inp) {

    if (inp < EOS_NUM_INPUTS) {

        eosDisableInterrupts();

        PORTINFO *p = &ports[inp];
        BOOL result = p->posEdge;
        p->posEdge = FALSE;

        eosEnableInterrupts();

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
 *           BOOL eosInpNegEdge(UINT8 inp)
 *
 *       Entrada:
 *           inp: Numero d'entrada
 *
 *       Retorn:
 *           TRUE si s'ha detectat un flanc negatiu
 *
 *       Notes:
 *           Un cop es crida a la funcio, aquesta no retornara TRUE, fins
 *           que arribi un altre flanc negatiu
 *
 *************************************************************************/

BOOL eosInpNegEdge(UINT8 inp) {

    if (inp < EOS_NUM_INPUTS) {

        eosDisableInterrupts();

        PORTINFO *p = &ports[inp];
        BOOL result = p->negEdge;
        p->negEdge = FALSE;

        eosEnableInterrupts();

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
 *           void eosInpClearEdge(UINT8 inp)
 *
 *       Entrada:
 *           inp: Numero d'entrada
 *
 *************************************************************************/

void eosInpClearEdge(UINT8 inp) {

    if (inp < EOS_NUM_INPUTS) {
        
        eosDisableInterrupts();

        PORTINFO *p = &ports[inp];
        p->posEdge = FALSE;
        p->negEdge = FALSE;

        eosDisableInterrupts();
    }
}


#endif
