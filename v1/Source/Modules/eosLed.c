#include "eos.h"


#ifdef eosUSE_LED


#define INI_TICK   1000      // 1000 cicles de interrupcio de 1mS

static UINT16 tick;          // Contador de temps


extern void halLedWrite(BOOL state);


/*************************************************************************
 *
 *       Inicialitza el led indicador
 *
 *       Funcio:
 *           void sysLedInitialize(void)
 *
 *************************************************************************/

void sysLedInitialize(void) {

    tick = INI_TICK;
}


/*************************************************************************
 *
 *       Procesa la interrupcio TMR
 *
 *       Funcio:
 *           void sysLedTickInterrupt(void)
 *
 *************************************************************************/

void sysLedTickInterrupt(void) {
    
    if (!--tick)
        tick = INI_TICK;

    halLedWrite(tick < 25);
}


#endif

