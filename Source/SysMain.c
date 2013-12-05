#include "eos.h"


#if defined(__XC8)
extern void usrInitialize(void);
extern void usrSetup(void);
void usrTick(void);
void usrLoop(void);
#endif

#if defined(__XC32)
__attribute__((weak)) void usrInitialize(void) {
}

__attribute__((weak)) void usrSetup(void) {
}

__attribute__((weak)) void usrTick(void) {
}

__attribute__((weak)) void usrLoop(void) {
   
}
#endif


/*************************************************************************
 *
 *       Interrupcio TICK del EOS, cal cridarla cada 1ms
 *
 *       Funcio:
 *           void eosTick(void)
 *
 *************************************************************************/

void eosTick(void) {

#ifdef EOS_USE_OUTPUTS
    sysOutTick();
#endif

#ifdef EOS_USE_INPUTS
    sysInpTick();
#endif
}


/*************************************************************************
 *
 *       Interrupcio general del EOS
 *
 *       Funcio:
 *           void eosInterrupt(void)
 * 
 *       Notes:
 *          Per millorar el rendiment es millor cridar des de
 *          l'aplicacio del usuari, a cada gestor d'interrupcio
 *          individualment
 *
 *************************************************************************/

void eosInterrupt(void) {
    
#ifdef EOS_USE_OUTPUTS
    sysOutInterrupt();
#endif

#ifdef EOS_USE_INPUTS
    sysInpInterrupt();
#endif
}


/*************************************************************************
 *
 *       Entrada a l'aplicacio. Inicialitza el sistema, i executa
 *       el bucle d'usuari
 *
 *       Funcio:
 *           void eosMain(void)
 *
 *************************************************************************/

void eosMain(void) {

    usrInitialize();

#ifdef EOS_USE_OUTPUTS
    sysOutInitialize();
#endif

#ifdef EOS_USE_INPUTS
    sysInpInitialize();
#endif

#if !defined(__DEBUG) && defined(EOS_USE_WATCHDOG)
    EnableWDT();
#endif

    usrSetup();
    while (TRUE) {

#ifdef EOS_USE_OUTPUTS
        sysOutLoop();
#endif

#ifdef EOS_USE_INPUTS
        sysInpLoop();
#endif
        usrLoop();

#if !defined(__DEBUG) && defined(EOS_USE_WATCHDOG)
        ClearWDT();
#endif
    }
}
 

/*************************************************************************
 *
 *       Entrada a l'aplicacio desde el compilador
 *
 *       Funcio:
 *           void main(void)
 *
 *************************************************************************/

#ifdef EOS_USE_SYSMAIN
void main(void) {

    eosMain();
}
#endif