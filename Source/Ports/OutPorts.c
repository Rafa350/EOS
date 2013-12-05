#include "eos.h"


#if defined(EOS_USE_OUTPUTS)


#if !defined(EOS_NUM_OUTPUTS) || (EOS_NUM_OUTPUTS < 1) || (EOS_NUM_OUTPUTS > 32)
#error 'EOS_NUM_OUTPUTS' ha de estar en el intervalo 1..16
#endif

typedef struct {             // Estat del port
    UINT16 timeout;          // -Contador de temps pels pulsos
    UINT8 state:1;           // -Indica si esta actiu o no
} PORTINFO;

static PORTINFO ports[EOS_NUM_OUTPUTS];


/*************************************************************************
 *
 *       Inicialitza la gestio de les sortides
 *
 *       Funcio:
 *           void eosOutInitialize(void)
 *
 *************************************************************************/

void sysOutInitialize(void) {

#if defined(usrOutInitialize)
    usrOutInitialize();
#else
#error No se definio 'usrOutInitialize'
#endif

    UINT8 out = EOS_NUM_OUTPUTS - 1;
    do {
        ports[out].timeout = 0;
        ports[out].state = 0;
    } while (out--);
}


/*************************************************************************
 *
 *       Tasca de control de les sortides. Es crida cada 1ms
 *
 *       Funcio:
 *           void eosOutTick(void)
 *
 *************************************************************************/

void sysOutTick(void) {

    // Actualitza les sortides temporitzades
    //
    UINT8 out = EOS_NUM_OUTPUTS - 1;
    do {
        UINT16 to = ports[out].timeout;
        if (to != 0) {
            to -= 1;
            if (to == 0)
                ports[out].state = !ports[out].state;
            ports[out].timeout = to;
        }
    } while (out--);
}


/*************************************************************************
 *
 *       Tasca de control de les sortides. Es crida en cada cicle
 *
 *       Funcio:
 *           void eosOutLoop(void)
 *
 *************************************************************************/

void sysOutLoop(void){

    di();
    
    UINT8 out = EOS_NUM_OUTPUTS - 1;
    do {
#ifdef usrOutWrite
      usrOutWrite(out, ports[out].state);
#else
#error No se definio 'usrOutWrite'
#endif
    } while (out--);
    
    ei();
}


/*************************************************************************
 *
 *       Asigna l'estat a una sortida
 *
 *       Funcio:
 *           void eosOutSet(UINT8 out, BOOL s)
 *
 *       Entrada:
 *           out: Numero de sortida
 *           s  : El nou estat a asignar
 *
 *************************************************************************/

void eosOutSet(UINT8 out, BOOL s) {

    if (out < EOS_NUM_OUTPUTS) {
        di();
        ports[out].state = s;
        ports[out].timeout  = 0;
        ei();
    }
}


/*************************************************************************
 *
 *       Llegeix l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutGet(UINT8 out)
 *
 *       Entrada:
 *           out: Numero de sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

BOOL eosOutGet(UINT8 out) {

    if (out < EOS_NUM_OUTPUTS) {
        di();
        BOOL result = ports[out].state;
        ei();
        return result;
    }
    else
        return FALSE;
}


/*************************************************************************
 *
 *       Genera un puls
 *
 *       Funcio:
 *           void eosOutPulse(UINT8 out, UINT16 time)
 *
 *       Entrada:
 *           out : Numero de sortida
 *           time: Llargada del puls en ms
 *
 *       Notes:
 *           Si el puls encara es actiu, simplement l'allarga el temps
 *           especificat
 *
 *************************************************************************/

void eosOutPulse(UINT8 out, UINT16 time) {

    if ((out < EOS_NUM_OUTPUTS) && (time != 0)) {
        di();
        if (ports[out].timeout == 0) {
            ports[out].state = !ports[out].state;
        }
        ports[out].timeout = time;
        ei();
    }
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void eosOutToggle(UINT8 out)
 *
 *       Entrada:
 *           out: El numero de sortida
 *
 *************************************************************************/

void eosOutToggle(UINT8 out) {

    if (out < EOS_NUM_OUTPUTS) {
        di();
        ports[out].state = !ports[out].state;
        ports[out].timeout = 0;
        ei();
    }
}


/*************************************************************************
 *
 *       Posa totes les sortides a OFF
 *
 *       Funcio:
 *           void eosOutAllOFF(void)
 *
 *************************************************************************/

void eosOutAllOFF(void) {

    UINT8 out = EOS_NUM_OUTPUTS - 1;
    do {
        ports[out].state = 0;
        ports[out].timeout = 0;
    } while (out--);
}


#endif