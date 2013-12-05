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

#elif defined(__XC32)
void usrInitialize(void) {
    SYSTEMConfigPerformance(GetSystemClock());
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
}

#else
#error Hardware no soportado
#endif


void usrSetup(void) {

}

void usrLoop(void) {

    eosOutSet(0, 1);
}