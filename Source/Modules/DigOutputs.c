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

    UINT8 outputId = EOS_NUM_OUTPUTS - 1;
    do {
        PORTINFO *p = &ports[outputId];
        p->timeout = 0;
        p->state = FALSE;
    } while (outputId--);
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
    UINT8 outputId = EOS_NUM_OUTPUTS - 1;
    do {
        PORTINFO *p = &ports[outputId];
        UINT16 to = p->timeout;
        if (to != 0) {
            to -= 1;
            if (to == 0)
                p->state = !p->state;
            p->timeout = to;
        }
    } while (outputId--);
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

    UINT8 outputId = EOS_NUM_OUTPUTS - 1;
    do {

        eosDisableInterrupts();
        __halOutWrite(outputId, ports[outputId].state);
        eosEnableInterrupts();

    } while (outputId--);
}


/*************************************************************************
 *
 *       Asigna l'estat a una sortida
 *
 *       Funcio:
 *           void eosOutSet(UINT8 outputId, BOOL state)
 *
 *       Entrada:
 *           outputId: Numero de sortida
 *           state   : El nou estat a asignar
 *
 *************************************************************************/

void eosOutSet(UINT8 outputId, BOOL state) {

    if (outputId < EOS_NUM_OUTPUTS) {

        eosDisableInterrupts();

        PORTINFO *p = &ports[outputId];
        p->state = state;
        p->timeout  = 0;

        eosEnableInterrupts();
    }
}


/*************************************************************************
 *
 *       Llegeix l'estat d'una sortida
 *
 *       Funcio:
 *           BOOL eosOutGet(UINT8 outputId)
 *
 *       Entrada:
 *           outputId: Numero de sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

BOOL eosOutGet(UINT8 outputId) {

    if (outputId < EOS_NUM_OUTPUTS) {

        eosDisableInterrupts();
        BOOL result = ports[outputId].state;
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
 *           void eosOutPulse(UINT8 outputId, UINT16 time)
 *
 *       Entrada:
 *           outputId: Numero de sortida
 *           time    : Llargada del puls en ms
 *
 *       Notes:
 *           Si el puls encara es actiu, simplement l'allarga el temps
 *           especificat
 *
 *************************************************************************/

void eosOutPulse(UINT8 outputId, UINT16 time) {

    if ((outputId < EOS_NUM_OUTPUTS) && (time != 0)) {

        eosDisableInterrupts();
        
        PORTINFO *p = &ports[outputId];
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
 *           void eosOutToggle(UINT8 outputId)
 *
 *       Entrada:
 *           outputId: El numero de sortida
 *
 *************************************************************************/

void eosOutToggle(UINT8 outputId) {

    if (outputId < EOS_NUM_OUTPUTS) {

        eosDisableInterrupts();

        PORTINFO *p = &ports[outputId];
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

    UINT8 outputId = EOS_NUM_OUTPUTS - 1;
    do {

        PORTINFO *p = &ports[outputId];
        p->state = 0;
        p->timeout = 0;

    } while (outputId--);
}


#endif