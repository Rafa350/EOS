#include "Modules/Plc/eosPlc.h"


#ifdef eosPLC_UseOutputs


#if !defined(eosPLC_NumOutputs) || (eosPLC_NumOutputs < 1) || (eosPLC_NumOutputs > 32)
#error 'EOS_NUM_OUTPUTS' ha de estar en el intervalo 1..32
#endif

typedef struct {             // Estat del port
    unsigned counter;        // -Contador de temps ms
    unsigned blink;          // -Temps de cicle ON/OFF
    unsigned state:1;        // -Indica si esta actiu o no
} PORTINFO;

static PORTINFO ports[eosPLC_NumOutputs];


extern void halOutInitialize(void);
extern void halOutPortWrite(UINT8 id, BOOL state);


/*************************************************************************
 *
 *       Inicialitza la gestio de les sortides
 *
 *       Funcio:
 *           void eosOutInitialize(void)
 *
 *************************************************************************/

void sysOutInitialize(void) {

    halOutInitialize();

    UINT8 outputId =  eosPLC_NumOutputs - 1;
    do {
        PORTINFO *p = &ports[outputId];
        p->state = FALSE;
        p->counter = 0;
        p->blink = 0;
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
    UINT8 outputId = eosPLC_NumOutputs - 1;
    do {
        PORTINFO *p = &ports[outputId];
        unsigned counter = p->counter;
        if (counter) {
            counter--;
            if (!counter) {
                p->state = !p->state;
                counter = p->blink;
            }
            p->counter = counter;
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

    UINT8 outputId = eosPLC_NumOutputs - 1;
    do {

        PORTINFO *p = &ports[outputId];

        eosDisableInterrupts();
        halOutPortWrite(outputId, p->state);
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

    if (outputId < eosPLC_NumOutputs) {

        PORTINFO *p = &ports[outputId];

        eosDisableInterrupts();
        p->state = state;
        p->counter = 0;
        p->blink = 0;
        eosEnableInterrupts();
    }
}


/*************************************************************************
 *
 *       Genera un puls
 *
 *       Funcio:
 *           void eosOutPulse(UINT8 id, unsigned time)
 *
 *       Entrada:
 *           id  : Numero de sortida
 *           time: Llargada del puls en ms
 *
 *       Notes:
 *           Si el puls encara es actiu, simplement l'allarga el temps
 *           especificat
 *
 *************************************************************************/

void eosOutPulse(UINT8 id, unsigned time) {

    if ((id < eosPLC_NumOutputs) && (time != 0)) {

        PORTINFO *p = &ports[id];

        eosDisableInterrupts();
        if (!p->counter)
            p->state = !p->state;
        p->counter = time;
        p->blink = 0;
        eosEnableInterrupts();
    }
}


/*************************************************************************
 *
 *       Genera un puls periodic
 *
 *       Funcio:
 *           void eosOutBlink(UINT8 id, unsigned time)
 *
 *       Entrada:
 *           id  : Numero de sortida
 *           time: Llargada del puls en ms
 *
 *       Notes:
 *           Si el puls encara es actiu, simplement l'allarga el temps
 *           especificat
 *
 *************************************************************************/

void eosOutBlink(UINT8 id, unsigned time) {

    if ((id < eosPLC_NumOutputs) && (time != 0)) {

        PORTINFO *p = &ports[id];

        eosDisableInterrupts();
        if (!p->counter)
            p->state = !p->state;
        p->counter = time;
        p->blink = time;
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

    if (outputId < eosPLC_NumOutputs) {

        PORTINFO *p = &ports[outputId];

        eosDisableInterrupts();
        p->state = !p->state;
        p->counter = 0;
        p->blink = 0;
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

    UINT8 outputId = eosPLC_NumOutputs - 1;
    do {

        PORTINFO *p = &ports[outputId];

        eosDisableInterrupts();
        p->state = 0;
        p->counter = 0;
        p->blink = 0;
        eosEnableInterrupts();

    } while (outputId--);
}


#endif