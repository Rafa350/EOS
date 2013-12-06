#include "eos.h"


#if defined(EOS_USE_OUTPUTS)


#if !defined(EOS_NUM_OUTPUTS) || (EOS_NUM_OUTPUTS < 1) || (EOS_NUM_OUTPUTS > 32)
#error 'EOS_NUM_OUTPUTS' ha de estar en el intervalo 1..16
#endif

typedef struct {             // Estat del port
    UINT16 timeout;          // -Contador de temps pels pulsos en ms
    unsigned state:1;        // -Indica si esta actiu o no
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

    __halOutInitialize();

    UINT8 out = EOS_NUM_OUTPUTS - 1;
    do {
        PORTINFO *p = &ports[out];
        p->timeout = 0;
        p->state = 0;
    } while (out--);
}


/*************************************************************************
 *
 *       Interrupcio Tick
 *
 *       Funcio:
 *           void eosOutTickInterrupt(void)
 *
 *************************************************************************/

void sysOutTickInterrupt(void) {

    // Actualitza les sortides temporitzades
    //
    UINT8 out = EOS_NUM_OUTPUTS - 1;
    do {
        PORTINFO *p = &ports[out];
        UINT16 to = p->timeout;
        if (to != 0) {
            to -= 1;
            if (to == 0)
                p->state = !p->state;
            p->timeout = to;
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

    eosDisableInterrupts();
    
    UINT8 out = EOS_NUM_OUTPUTS - 1;
    do {
      __halOutWrite(out, ports[out].state);
    } while (out--);
    
    eosEnableInterrupts();
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

        eosDisableInterrupts();

        PORTINFO *p = &ports[out];
        p->state = s;
        p->timeout  = 0;

        eosEnableInterrupts();
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

        eosDisableInterrupts();

        BOOL result = ports[out].state;
        eosEnableInterrupts();

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

        eosDisableInterrupts();
        
        PORTINFO *p = &ports[out];
        if (p->timeout == 0)
            p->state = !p->state;
        p->timeout = time;

        eosEnableInterrupts();
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

        eosDisableInterrupts();

        PORTINFO *p = &ports[out];
        p->state = !p->state;
        p->timeout = 0;

        eosEnableInterrupts();
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

        PORTINFO *p = &ports[out];
        p->state = 0;
        p->timeout = 0;

    } while (out--);
}


#endif