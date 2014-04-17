#include "eos.h"


#if !defined(HARDWARE_PICKIT3)
#error Hardware incorrecto
#endif


/*************************************************************************
 *
 *       Inicialitza el hardware
 *
 *       Funcio:
 *           void halInitialize(void)
 *
 *************************************************************************/

void halInitialize(void) {

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
    OSCCONbits.SCS = 0;           // Oscilador primari definit en CONFIG.FOSC
#endif

    // Espera que s'estabilitzi l'oscilador
    //
#ifdef USE_OSC_INTERNAL
    while (!OSCCONbits.IOFS)
        continue;
#endif

    // Configura el temporitzador TMR2
    // -Genera una interrupcio cada 1ms
    //
    PR2 = 125;                    // Conta fins a 125
    T2CONbits.T2CKPS = 3;         // Divisor per 64 --> (Fosc / 4) / 64 = 125KHz
    T2CONbits.T2OUTPS = 1;        // Divisor per 2
    T2CONbits.TMR2ON = 1;         // Inicia el conteig
    TMR2IF = 0;                   // Borra el flag d'interrupcions
    TMR2IE = 1;                   // Autoritza interrupcions de TMR2

    // Inicialitza el port del indicador LED
    //
#ifdef eosUSE_LED
    TRISDbits.TRISD7 = 0;
#endif

    // Inicialitza els ports d'entrada
    //
#ifdef eosUSE_INPUTS
#endif

    // Inicialitza els ports de sortida
    //
#ifdef eosUSE_OUTPUTS
    TRISD &= 0b10000000;
#endif

    // Configura les interrupcions
    //
    IPEN = 0;                     // Interrupcions sense prioritats
    PEIE = 1;                     // Autoritza interrupcions dels periferics
}


/*************************************************************************
 *
 *       Escriptura en el port de sortida
 *
 *       Funcio:
 *           void halPortWrite(UINT8 id, BOOL state)
 *
 *       Entrada:
 *           id   : Numero de sortida
 *           state: Estat a aplicar
 *
 *************************************************************************/

#ifdef eosUSE_OUTPUTS
void halPortWrite(UINT8 id, BOOL state) {

    if (id < 7) {
        if (state)
            LATD |= (1 << id);
        else
            LATD &= ~(1 << id);
    }
}
#endif


#ifdef eosUSE_INPUTS
BOOL halPortRead(UINT8 id) {

    return FALSE;
}
#endif


/*************************************************************************
 *
 *       Canvia l'estar del indicador LED
 *
 *       Funcio:
 *           void halLedWrite(BOOL state)
 *
 *       Entrada:
 *           state: El nou estat del led
 *
 *************************************************************************/

void halLedWrite(BOOL state) {

    LATDbits.LATD7 = state;
}


/*************************************************************************
 *
 *       Procesa les interrupcions d'alta prioritat
 *
 *       Funcio:
 *           void interrupt ISR(void)
 *
 *************************************************************************/

void interrupt ISR(void) {

    if (TMR2IF && TMR2IE) {
        eosTickInterrupt();
        TMR2IF = 0;
    }
}