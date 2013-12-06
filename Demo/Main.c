#include "eos.h"


/*************************************************************************
 *
 *       Inicialitza el hardware
 *
 *       Funcio:
 *           void usrInitialize(void) 
 *
 **************************************************************************/

#if defined(_12F1822) || defined(_16F1823) || defined(_16F1825) || defined(_16F1829)
void usrInitialize(void) {

    // Configuracio del oscilador (Fosc = 32MHz)
    // -Oscilador intern HS a 8MHz
    // -PLL x4 --> 8MHz x 4 = 32MHz
    // -Oscilador primari seleccionat en CONFIG
    //
    OSCCONbits.SPLLEN = 1;        // Activa PLLx4 (Esta OFF en CONFIG2)
    OSCCONbits.SCS = 0;           // Oscilador primari en CONFIG.FOSC
    OSCCONbits.IRCF = 0x0E;       // 8MHz a la entrada del PLL

    // Espera que s'estabilitzi l'oscilador
    //
    while (!OSCSTATbits.HFIOFS)
        continue;
}

#elif defined(_18F23K22) || defined(_18F24K22) || defined(_18F25K22) || defined(_18F26K22) || \
      defined(_18F43K22) || defined(_18F44K22) || defined(_18F45K22) || defined(_18F46K22)
void usrInitialize(void) {

    // Configuracio del oscilador (Fosc = 64MHz)
    // -Oscilador intern HS a 16MHz
    // -PLL x4 --> 16MHz x 4 = 64MHz
    // -Oscilador primari seleccionat en CONFIG
    //
#ifdef __DEBUG
    OSCCONbits.SCS = 0;           // Oscilador primari en CONFIG.FOSC
#else
    OSCTUNEbits.PLLEN = 1;        // PLL enabled (x4)
    OSCCONbits.IRCF = 7;          // 16MHz en HFINTOSC
    OSCTUNEbits.INTSRC = 1;       // 31.25 clock from HS
    OSCCONbits.SCS = 0;           // Oscilador primari en CONFIG.FOSC

    // Espera que s'estabilitzi l'oscilador
    //
#ifdef USE_OSC_INTERNAL
    while (!OSCCONbits.HFIOFS)
        continue;
#endif
#endif
}

#elif defined(__PIC32MX)

#define PB_DIV                2
#define PRESCALE              256
#define TOGGLES_PER_SEC       1000
#define T1_TICK               (GetSystemClock() / PB_DIV / PRESCALE / TOGGLES_PER_SEC)

void usrInitialize(void) {

    SYSTEMConfigPerformance(GetSystemClock());

    // Configura el temporitzador per que generi interrupcions TICK cada 1ms
    //
    OpenTimer1(T1_INT_ON | T1_SOURCE_INT | T1_PS_1_256, T1_TICK);
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2);

    // Activa interrupcions multivector
    //
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
}

void __ISR(_TIMER_1_VECTOR, ipl2) Timer1Handler(void) {

    eosTickInterrupt();
    
    mT1ClearIntFlag();
}


/*void __ISR(_CHANGE_NOTICE_VECTOR, ipl2) ChangePinsHandler(void) {

    sysInpChangeInterrupt();

    mCNClearIntFlag();
}*/

#else
#error Hardware no soportado
#endif


void usrSetup(void) {

    eosOutPulse(2, 10000);
}

void usrLoop(void) {

    eosOutSet(0, eosInpGet(0) || eosInpGet(2));
    eosOutSet(1, eosInpGet(1) || eosInpGet(2));
}