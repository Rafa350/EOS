#ifndef __HARDWAREPROFILE_H
#define	__HARDWAREPROFILE_H


#ifdef HARDWARE_CPU04B

#define USE_OSC_XTAL

// Definicions pel modul d'entrades digitals
//
#define usrInpInitialize() {      \
    TRISB |= 0b11111111;          \
    TRISE |= 0b00000011;          \
    WPUB |= 0b11111111;           \
    ANSELB &= 0b11000000;         \
    ANSELE &= 0b11111100;         \
    RBPU = 0;                     \
}

#define usrInpWrite(inp, s) {     \
}

#define usrInpRead(inp) {         \
}


// Definicions pel modul de sortides digitals
//
#define usrOutInitialize()  {     \
    LATA &= 0b11000000;           \
    LATC &= 0b11110000;           \
    ANSELA &= 0b11010000;         \
    ANSELC &= 0b11110011;         \
    TRISA &= 0b11000000;          \
    TRISC &= 0b11110000;          \
}

#define usrOutWrite(out, s) {     \
    UINT8 v = s;                  \
    if (out == 0)                 \
        PORTAbits.RA5 = v;        \
    else if (out == 1)            \
        PORTAbits.RA4 = v;        \
    else if (out == 2)            \
        PORTAbits.RA1 = v;        \
    else if (out == 3)            \
        PORTAbits.RA3 = v;        \
    else if (out == 4)            \
        PORTAbits.RA2 = v;        \
    else if (out == 5)            \
        PORTAbits.RA0 = v;        \
    else if (out == 6)            \
        PORTCbits.RC1 = v;        \
    else if (out == 7)            \
        PORTCbits.RC3 = v;        \
    else if (out == 8)            \
        PORTCbits.RC2 = v;        \
    else if (out == 9)            \
        PORTCbits.RC0 = v;        \
}

#elif defined(HARDWARE_PIC32_ESK)

// Definicions per PLIB32
//
#define GetSystemClock()          (80000000L)


// Definicions pel modul d'entrades digitals
//
#define usrInpInitialize() {      \
}

#define usrInpWrite(inp, s) {     \
}

#define usrInpRead(inp) {         \
}

// Definicions pel modul de sortides digitals
//
#define LED1  0
#define LED2  1
#define LED3  2

#endif

#endif

