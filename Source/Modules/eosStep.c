#include "eos.h"


#ifdef eosUSE_STEP



/*************************************************************************
 *
 *       Inicialitza les entrades analoguiques
 *
 *       Funcio:
 *           void sysStpInitialize(void)
 *
 *************************************************************************/

void sysStpInitialize(void) {
}


/*************************************************************************
 *
 *       Tasca s. Es crida
 *       cada 1ms
 *
 *       Funcio:
 *           void sysStepTickInterupt(void)
 *
 *************************************************************************/

void sysStpTickInterrupt(void) {

}


/*************************************************************************
 *
 *       Realitza un moviment 
 *
 *       Funcio:
 *           void eosStpMove()
 *
 *************************************************************************/

void eosStepMove(unsigned upRamp, unsigned dnRamp, unsigned speed, int steps) {
}


BOOL eosStepBussy(void) {

    return FALSE;
}


#endif