#include "eos.h"


#ifdef EOS_USE_INPUTS


#if !defined(EOS_NUM_INPUTS) || (EOS_NUM_INPUTS < 1) || (EOS_NUM_INPUTS > 32)
#error 'EOS_NUM_INPUTS' ha de estar en el intervalo 1..32
#endif


#define MASK_STATE     0b00000001  // Bit d'estat de l'entrada
#define MASK_POSEDGE   0b00000010  // Indicador de flanc positiu
#define MASK_NEGEDGE   0b00000100  // Indicador de flanc negatiu

#define MIN_PULSE      20          // Emplada minim de senyal en ms

typedef struct {
    UINT16 debounce;
    UINT16 minPulse;
    UINT16 oldPort;
    UINT8 state:1;
    UINT8 posEdge:1;
    UINT8 negEdge:1;
} PORTINFO;

static PORTINFO ports[EOS_NUM_INPUTS];


/*
 ###############################################################
 Modificar per treballar amb deteccio de canvis per interrupcio
 ###############################################################
 */


/*************************************************************************
 *
 *       Comprova les entrades
 *
 *       Funcio:
 *           void CheckInput(UINT8 port, UINT8 inp)
 *
 *       Entrada:
 *           port: Valor del port fisic
 *           inp : Numero d'entrada
 *
 *************************************************************************/

static void CheckInput(UINT8 port, UINT8 inp) {

    UINT8 st;

    port &= 1;
    if (port != oldPort[inp]) {
        oldPort[inp] = port;
        debounce[inp] = minPulse[inp];
    }
    else if (debounce[inp] == 0) {
        st = state[inp];
        if (port) {
            if ((st & MASK_STATE) != 0) {
                st |= MASK_NEGEDGE;
                st &= ~MASK_POSEDGE;
            }
            st &= ~MASK_STATE;
        }
        else {
            if ((st & MASK_STATE) == 0) {
                st |= MASK_POSEDGE;
                st &= ~MASK_NEGEDGE;
            }
            st |= MASK_STATE;
        }
        state[inp] = st;
    }
}


/*************************************************************************
 *
 *       Inicialitza la gestio de les entrades
 *
 *       Funcio:
 *           void sysInpInitialize(void)
 *
 *************************************************************************/

void sysInpInitialize(void) {

    UINT8 inp;

#if defined (usrInpInitialize)
    usrInpInitialize();
#else
#error "No se definio PHY_INP_Initialize"
#endif

    inp = EOS_NUM_INPUTS - 1;
    do {
        ports[inp].state = FALSE;
        ports[inp].posEdge = FALSE;
        ports[inp].negEdge = FALSE;
        ports[inp].debounce = MIN_PULSE;
        ports[inp].minPulse = MIN_PULSE;
    } while (inp--);
}


/*************************************************************************
 *
 *       Tasca de control de les entrades. Es crida cada 1ms
 *
 *       Funcio:
 *           void sysInpTick(void)
 *
 *************************************************************************/

void sysInpTick(void) {

    UINT8 inp = EOS_NUM_INPUTS - 1;
    do {
        if (ports[inp].debounce != 0)
            ports[inp].debounce--;
    } while (inp--);
}


/*************************************************************************
 *
 *       Tasca de control de les entrades. Es crida cada cicle
 *
 *       Funcio:
 *           void inpService(void)
 *
 *************************************************************************/

void inpService(void) {

    di();
    CheckInput(PHY_INP0_Read(), 0);
#if NUM_INPUTS > 1
    CheckInput(PHY_INP1_Read(), 1);
#endif
#if NUM_INPUTS > 2
    CheckInput(PHY_INP2_Read(), 2);
#endif
#if NUM_INPUTS > 3
    CheckInput(PHY_INP3_Read(), 3);
#endif
#if NUM_INPUTS > 4
    CheckInput(PHY_INP4_Read(), 4);
#endif
#if NUM_INPUTS > 5
    CheckInput(PHY_INP5_Read(), 5);
#endif
#if NUM_INPUTS > 6
    CheckInput(PHY_INP6_Read(), 6);
#endif
#if NUM_INPUTS > 7
    CheckInput(PHY_INP7_Read(), 7);
#endif
#if NUM_INPUTS > 8
    CheckInput(PHY_INP8_Read(), 8);
#endif
#if NUM_INPUTS > 9
    CheckInput(PHY_INP9_Read(), 9);
#endif
#if NUM_INPUTS > 10
    CheckInput(PHY_INP10_Read(), 10);
#endif
#if NUM_INPUTS > 11
    CheckInput(PHY_INP11_Read(), 11);
#endif
#if NUM_INPUTS > 12
    CheckInput(PHY_INP12_Read(), 12);
#endif
#if NUM_INPUTS > 13
    CheckInput(PHY_INP13_Read(), 13);
#endif
#if NUM_INPUTS > 14
    CheckInput(PHY_INP14_Read(), 14);
#endif
#if NUM_INPUTS > 15
    CheckInput(PHY_INP15_Read(), 15);
#endif
    ei();
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
        di();
        BOOL result = (state[inp] & MASK_POSEDGE) != 0;
        state[inp] &= ~MASK_POSEDGE;
        ei();
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

    if (inp < NUM_INPUTS) {
        di();
        BOOL result = (state[inp] & MASK_NEGEDGE) != 0;
        state[inp] &= ~MASK_NEGEDGE;
        ei();
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

    if (inp < NUM_INPUTS) {
        di();
        state[inp] &= ~MASK_NEGEDGE;
        state[inp] &= ~MASK_POSEDGE;
        ei();
    }
}

/*************************************************************************
 *
 *       Asigna l'amplada minima d'una senyal d'entrada per
 *       que es conti com a tal
 *
 *       Funcio:
 *           void eosInpMinPulse(UINT8 inp, UINT8 time) {
 *
 *       Entrada:
 *          inp : Numero d'entrada
 *          time: Temps minim en ms
 *
 *************************************************************************/

void eosInpMinPulse(UINT8 inp, UINT8 time) {

    if (inp < NUM_INPUTS) {
        debounce[inp] = time;
        minPulse[inp] = time;
    }
}


#endif
