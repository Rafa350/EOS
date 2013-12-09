#include "eos.h"


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
    OSCCONbits.IRCF = 6;          // 8MHz
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
    T2CONbits.T2OUTPS = 0;        // Divisor per 1
    T2CONbits.TMR2ON = 1;         // Inicia el conteig
    TMR2IF = 0;                   // Borra el flag d'interrupcions
    TMR2IE = 1;                   // Autoritza interrupcions de TMR2

    // Inicialitza els ports d'entrada
    //
    TRISB |= 0b11111111;
    TRISE |= 0b00000011;
    WPUB |= 0b11111111;
    ANSELB &= 0b11000000;
    ANSELE &= 0b11111100;
    RBPU = 0;

    // Inicialitza els ports de sortida
    //
    LATA &= 0b11000000;
    LATC &= 0b11110000;
    ANSELA &= 0b11010000;
    ANSELC &= 0b11110011;
    TRISA &= 0b11000000;
    TRISC &= 0b11110000;

    // Inicialitzacio del port LED
    //
    ANSELDbits.ANSD5 = 0;
    LATDbits.LATD5 = 0;
    TRISDbits.TRISD5 = 0;

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
 *           void halOutWrite(UINT8 id, BOOL state)
 *
 *       Entrada:
 *           id   : Numero de sortida
 *           state: Estat a aplicar
 *
 *************************************************************************/

void halOutPortWrite(UINT8 id, BOOL state) {

    BOOL s = state;
    if (id == 0)
        LATAbits.LATA5 = s;
    else if (id == 1)
        LATAbits.LATA4 = s;
    else if (id == 2)
        LATAbits.LATA1 = s;
    else if (id == 3)
        LATAbits.LATA3 = s;
    else if (id == 4)
        LATAbits.LATA2 = s;
    else if (id == 5)
        LATAbits.LATA0 = s;
    else if (id == 6)
        LATCbits.LATC1 = s;
    else if (id == 7)
        LATCbits.LATC3 = s;
    else if (id == 8)
        LATCbits.LATC2 = s;
    else if (id == 9)
        LATCbits.LATC0 = s;
}


BOOL halInpPortRead(UINT8 id) {

    return FALSE;
}


/*************************************************************************
 *
 *       Canvia l'estar del indicador LED
 *
 *       Funcio:
 *           void halLedPortWrite(BOOL state)
 *
 *       Entrada:
 *           state: El nou estat del led
 *
 *************************************************************************/

void halLedPortWrite(BOOL state) {

    LATDbits.LATD5 = state;
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