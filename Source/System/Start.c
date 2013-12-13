#include "eos.h"


#if defined(_PIC18)
extern void usrSetup(void);
void usrLoop(void);

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

#ifdef eosPLC_UseOutputs
    sysOutTickInterrupt();
#endif

#ifdef eosPLC_UseInputs
    sysInpTickInterrupt();
#endif

#ifdef eosPLC_UseTimers
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

#ifdef eosPLC_UseOutputs
    sysOutInitialize();
#endif

#ifdef eosPLC_UseInputs
    sysInpInitialize();
#endif

#ifdef eosPLC_UseTimers
    sysTimInitialize();
#endif

#ifdef eosPLC_UseVariables
    sysVarInitialize();
#endif

#ifdef EOS_USE_LEDSTATUS
    sysLedInitialize();
#endif

#ifdef EOS_USE_USBHOST
    sysUsbHostInitialize();
#endif

#if !defined(__DEBUG) && defined(EOS_USE_WATCHDOG)
    eosEnableWatchdog();
#endif

    usrSetup();
    eosEnableInterrupts();
 
    while (TRUE) {

#ifdef eosPLC_UseOutputs
        sysOutLoop();
#endif

#ifdef eosPLC_UseInputs
        sysInpLoop();
#endif

#ifdef eosPLC_UseTimers
        sysTimLoop();
#endif

#ifdef EOS_USE_USBHOST
        sysUsbHostLoop();
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