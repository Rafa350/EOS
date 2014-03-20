#include "Modules/Plc/eosPlc.h"


#ifdef eosUSE_OUTPUTS


#if !defined(eosCFG_OUTPUTS_NumOutputs) || (eosCFG_OUTPUTS_NumOutputs < 1) || (eosCFG_OUTPUTS_NumOutputs > 32)
#error 'EOS_NUM_OUTPUTS' ha de estar en el intervalo 1..32
#endif

typedef struct {             // Estat del port
    unsigned counter;        // -Contador de temps ms
    unsigned blink;          // -Temps de cicle ON/OFF
    unsigned state:1;        // -Indica si esta actiu o no
} PORTINFO;

static PORTINFO ports[eosCFG_OUTPUTS_NumOutputs];


extern void halPortWrite(UINT8 id, BOOL state);


/*************************************************************************
 *
 *       Inicialitza la gestio de les sortides
 *
 *       Funcio:
 *           void eosOutInitialize(void)
 *
 *************************************************************************/

void sysOutInitialize(void) {

    UINT8 id = eosCFG_OUTPUTS_NumOutputs - 1;
    do {

        PORTINFO *p = &ports[id];
        p->state = FALSE;
        p->counter = 0;
        p->blink = 0;

    } while (id--);
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
    UINT8 id = eosCFG_OUTPUTS_NumOutputs - 1;
    do {
    
        PORTINFO *p = &ports[id];
        unsigned counter = p->counter;
        if (counter) {
            counter--;
            if (!counter) {
                p->state = !p->state;
                counter = p->blink;
            }
            p->counter = counter;
        }
        
    } while (id--);
}


/*************************************************************************
 *
 *       Tasca de control de les sortides. Es crida en cada cicle
 *
 *       Funcio:
 *           void eosOutLoop(void)
 *
 *************************************************************************/

void sysOutLoop(void) {

    UINT8 id = eosCFG_OUTPUTS_NumOutputs - 1;
    do {

        PORTINFO *p = &ports[id];

        eosDisableInterrupts();
        halPortWrite(id, p->state);
        eosEnableInterrupts();

    } while (id--);
}


/*************************************************************************
 *
 *       Asigna l'estat a una sortida
 *
 *       Funcio:
 *           void eosOutSet(UINT8 id, BOOL state)
 *
 *       Entrada:
 *           id   : Numero de sortida
 *           state: El nou estat a asignar
 *
 *************************************************************************/

void eosOutSet(UINT8 id, BOOL state) {

    if (id < eosCFG_OUTPUTS_NumOutputs) {

        PORTINFO *p = &ports[id];

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

    if ((id < eosCFG_OUTPUTS_NumOutputs) && (time != 0)) {

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

    if ((id < eosCFG_OUTPUTS_NumOutputs) && (time != 0)) {

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
 *           void eosOutToggle(UINT8 id)
 *
 *       Entrada:
 *           id: El numero de sortida
 *
 *************************************************************************/

void eosOutToggle(UINT8 id) {

    if (id < eosCFG_OUTPUTS_NumOutputs) {

        PORTINFO *p = &ports[id];

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

    UINT8 id = eosCFG_OUTPUTS_NumOutputs - 1;
    do {

        PORTINFO *p = &ports[id];

        eosDisableInterrupts();
        p->state = 0;
        p->counter = 0;
        p->blink = 0;
        eosEnableInterrupts();

    } while (id--);
}


#endif