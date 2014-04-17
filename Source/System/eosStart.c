#include "eos.h"


extern void halInitialize(void);


#if defined(_PIC18)
extern void usrSetup(void);
extern void usrLoop(void);

#elif defined(__PIC32MX)
__attribute__((weak)) void usrSetup(void) {
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

#ifdef eosUSE_OUTPUTS
    sysOutTickInterrupt();
#endif

#ifdef eosUSE_INPUTS
    sysInpTickInterrupt();
#endif

#ifdef eosUSE_STEP
    sysStpTickInterrupt();
#endif

#ifdef eosUSE_TIMERS
    sysTimTickInterrupt();
#endif

#ifdef eosUSE_LED
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

    halInitialize();

#ifdef eosUSE_OUTPUTS
    sysOutInitialize();
#endif

#ifdef eosUSE_INPUTS
    sysInpInitialize();
#endif

#ifdef eosUSE_STEP
    sysStpInitialize();
#endif

#ifdef eosUSE_TIMERS
    sysTimInitialize();
#endif

#ifdef eosUSE_VARIABLES
    sysVarInitialize();
#endif

#ifdef eosUSE_LED
    sysLedInitialize();
#endif

#ifdef eosUSE_USBHOST
    sysUsbHostInitialize();
#endif

#if !defined(__DEBUG) && defined(eosOPT_WATCHDOG)
    eosEnableWatchdog();
#endif

    usrSetup();
    eosEnableInterrupts();
 
    while (TRUE) {

#ifdef eosUSE_OUTPUTS
        sysOutLoop();
#endif

#ifdef eosUSE_INPUTS
        sysInpLoop();
#endif

#ifdef eosUSE_TIMERS
        sysTimLoop();
#endif

#ifdef eosUSE_USBHOST
        sysUsbHostLoop();
#endif

        usrLoop();

#if !defined(__DEBUG) && defined(eosOPT_WATCHDOG)
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

#ifdef eosOPT_SYSMAIN
void main(void) {

    eosMain();
}
#endif