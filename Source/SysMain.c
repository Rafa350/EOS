#include "eos.h"


#if defined(_PIC18)
extern void usrInitialize(void);
extern void usrSetup(void);
void usrTick(void);
void usrLoop(void);

#elif defined(__PIC32MX)
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
 *           void eosTickInterrupt(void)
 *
 *************************************************************************/

void eosTickInterrupt(void) {

#ifdef EOS_USE_OUTPUTS
    sysOutTickInterrupt();
#endif

#ifdef EOS_USE_INPUTS
    sysInpTickInterrupt();
#endif

#ifdef EOS_USE_TIMERS
    sysTimTickInterrupt();
#endif

#ifdef EOS_USE_LEDSTATUS
    sysLedTickInterrupt();
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

    __halInitialize();

#ifdef EOS_USE_OUTPUTS
    sysOutInitialize();
#endif

#ifdef EOS_USE_INPUTS
    sysInpInitialize();
#endif

#ifdef EOS_USE_TIMERS
    sysTimInitialize();
#endif

#ifdef EOS_USE_LEDSTATUS
    sysLedInitialize();
#endif

#if !defined(__DEBUG) && defined(EOS_USE_WATCHDOG)
    eosEnableWatchdog();
#endif

    usrSetup();
    eosEnableInterrupts();
 
    while (TRUE) {

#ifdef EOS_USE_OUTPUTS
        sysOutLoop();
#endif

#ifdef EOS_USE_INPUTS
        sysInpLoop();
#endif

#ifdef EOS_USE_TIMERS
        sysTimLoop();
#endif

        usrLoop();

#if !defined(__DEBUG) && defined(EOS_USE_WATCHDOG)
        eosClearWatchdog();
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