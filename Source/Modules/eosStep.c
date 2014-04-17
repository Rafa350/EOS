#include "eos.h"


#ifdef eosUSE_STEP

#if !defined(eosCFG_STEP_NumMotors) || (eosCFG_STEP_NumMotors < 1) || (eosCFG_STEP_NumMotors > 8)
#error 'eosCFG_STEP_NumMotors' ha de estar en el intervalo 1..8
#endif

#define C0         1000
#define C_MIN      25

typedef enum {
    rampUp,
    rampDown,
    rampLast,
    rampMax,
    rampIdle
} RAMPSTATE;

typedef struct {
    INT16 c;
    INT32 c32;
    INT16 denom;
    INT16 steps;                  // Numero de pasos del moviment
    INT16 step_no;                // Numero de pas actual
    INT16 mid_pt;                 // Punt mitja del moviment
    INT16 step_down;              // Punt per decelerer
    UINT16 timer;                 // Temporitzador
    RAMPSTATE state;              // Estat de la rampa
} MOTORINFO;

static MOTORINFO motors[eosCFG_STEP_NumMotors];


/*************************************************************************
 *
 *       Inicialitza les entrades analoguiques
 *
 *       Funcio:
 *           void sysStpInitialize(void)
 *
 *************************************************************************/

void sysStpInitialize(void) {

    UINT8 id = eosCFG_STEP_NumMotors - 1;
    do {
        MOTORINFO *p = &motors[id];
        p->state = rampIdle;
    } while (id--);
}


/*************************************************************************
 *
 *       Procesa la interrupcio Tick
 *
 *       Funcio:
 *           void sysStpTickInterupt(void)
 *
 *************************************************************************/

void sysStpTickInterrupt(void) {

    UINT8 id =  0; // eosCFG_STEP_NumMotors - 1;
    do {

        MOTORINFO *p = &motors[id];

        if (p->timer)
            p->timer--;

        else {
            p->timer += p->c;
            switch (p->state) {
                case rampUp:
                    if (p->step_no == p->mid_pt) {
                        p->state = rampDown;
                        p->denom = ((p->step_no - p->steps) << 2) + 1;
                        if (!(p->steps & 1)) {
                            // even move: repeat last delay before decel
                            p->denom +=4;
                            break;
                        }
                    }
                    // no break: share code for ramp algo

                case rampDown:
                    if (p->step_no == p->steps - 1) {
                        // next irq is cleanup (no step)
                        p->state = rampLast;
                        break;
                    }
                    p->denom += 4;
                    p->c32 -= (p->c32 << 1) / p->denom; // ramp algorithm
                    // beware confict with foreground code if long div not reentrant
                    p->c = (p->c32 + 128) >> 8; // round 24.8format->int16
                    if (p->c <= C_MIN) {
                        // go to constant speed
                        p->state = rampMax;
                        p->step_down = p->steps - p->step_no;
                        p->c = C_MIN;
                        break;
                    }
                    break;

                case rampMax:
                    if (p->step_no == p->step_down) {
                        // start decel
                        p->state = rampDown;
                        p->denom = ((p->step_no - p->steps) << 2) + 5;
                    }
                    break;

                default: // last step: cleanup
                    p->state = rampIdle;
                    //current_off(); // reduce motor current to holding value
                    //disable_interrupts(INT_CCP1);
                    break;
            }

            if (p->state != rampIdle) {
                p->step_no++;
                LATDbits.LATD6 = !LATDbits.LATD6;
            }
        }
        
    } while (id--);
}


/*************************************************************************
 *
 *       Realitza un moviment 
 *
 *       Funcio:
 *           void eosStpMove(UINT8 id, unsigned upRamp, unsigned dnRamp,
 *               unsigned speed, int steps)
 *
 *       Entrada:
 *           id    : Identificador del motor
 *           upRamp: Rampa d'acceleracio
 *           dwRamp: Rampa de frenada
 *           speed : Velocitat maxima
 *           steps : Numero de pasos a realitzar
 *
 *       Notes:
 *           Totes les mesures en pasos/segon
 *
 *************************************************************************/

void eosStpMove(UINT8 id, unsigned upRamp, unsigned dnRamp, unsigned speed, int steps) {
    
    if (id < eosCFG_STEP_NumMotors) {

        MOTORINFO *p = &motors[id];
        p->c = C0;
        p->c32 = ((INT32) p->c) << 8;
        p->denom = 1;
        p->step_no = 0;
        p->steps = steps;
        p->mid_pt = (steps - 1) >> 1;
        p->state = rampUp;
        p->timer = 10;
    }
}


BOOL eosStpIsBusy(UINT8 id) {

    if (id < eosCFG_STEP_NumMotors) {
        MOTORINFO *p = &motors[id];
        return p->state != rampIdle;
    }
    else
        return TRUE;
}


#endif