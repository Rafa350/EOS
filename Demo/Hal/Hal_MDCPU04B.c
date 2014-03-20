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
    TMR0L = 125;                  // Conta fins a 125
    T0CONbits.T08BIT = 1;         // Modus 8 bits
    T0CONbits.T0CS = 0;           // Fosc/4
    T0CONbits.PSA = 0;            // Divisor activat
    T0CONbits.T0PS = 5;           // Divisor 1:64
    T0CONbits.TMR0ON = 1;         // Temporitzador activat
    TMR0IF = 0;
    TMR0IE = 1;                   // Permet interrupcions en TMR0

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

#ifdef EOS_USE_WATCHDOG
    WDTCONbits.WDTPS = 0x0A;      // Es dispara cada segon
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

void halPortWrite(UINT8 id, BOOL state) {

    BOOL s = state;
    switch (id) {
        case 0:
            LATAbits.LATA5 = s;
            break;

        case 1:
            LATAbits.LATA4 = s;
            break;


        case 2:
            LATAbits.LATA1 = s;
            break;

        case 3:
            LATAbits.LATA3 = s;
            break;

        case 4:
            LATAbits.LATA2 = s;
            break;

        case 5:
            LATAbits.LATA0 = s;
            break;

        case 6:
            LATCbits.LATC1 = s;
            break;

        case 7:
            LATCbits.LATC3 = s;
            break;

        case 8:
            LATCbits.LATC2 = s;
            break;

        case 9:
            LATCbits.LATC0 = s;
            break;
    }
}


/*************************************************************************
 *
 *       Lectura d'un port d'entrada
 *
 *       Funcio:
 *           BOOL halPortRead(UINT8 id)
 *
 *       Entrada:
 *           id: Identificador del port
 *
 *       Retorn:
 *           Estst del port
 *
 *************************************************************************/

BOOL halPortRead(UINT8 id) {

    switch (id) {
        case 0:
            return PORTBbits.RB1;
        
        case 1:
            return PORTBbits.RB0;
        
        case 2:
            return PORTBbits.RB3;
        
        case 3:
            return PORTBbits.RB2;
        
        case 4:
            return PORTBbits.RB5;
        
        case 5:
            return PORTBbits.RB4;
        
        case 6:
            return PORTBbits.RB7;
        
        case 7:
            return PORTBbits.RB6;
        
        case 8:
            return PORTEbits.RE0;
        
        case 9:
            return PORTEbits.RE1;
        
        default:
            return FALSE;
    }
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

    if (TMR0IF && TMR0IE) {
        eosTickInterrupt();
        TMR0IF = 0;
    }
}