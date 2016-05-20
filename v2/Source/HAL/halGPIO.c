#include "xc.h"
#include "hal/halGPIO.h"


typedef struct {                       // Configuracio dels pins
    volatile uint32_t *trisCLR;        // -Adressa TRISxCLR
    volatile uint32_t *trisSET;        // -Adressa TRISxSET
    volatile uint32_t *odcCLR;         // -Addrese ODCxCLR
    volatile uint32_t *odcSET;         // -Addresa ODCxSET
    volatile uint32_t *port;           // -Addresa PORTx
    volatile uint32_t *latCLR;         // -Adressa LATxCLR
    volatile uint32_t *latSET;         // -Adressa LATxSET
    volatile uint32_t *latINV;         // -Adressa LATxINV
    uint32_t mask;                     // -Mascara del pin
    int analog;                        // -Port analogic (-1 cap))
} PinInfo;


#if defined(HARDWARE_PINGUINO)
#define NUM_PINS 33
static const PinInfo pinInfoTbl[NUM_PINS] = {
/* PIN1   RB0  */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV,  1 << 0, -1 },
/* PIN2   RB1  */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV,  1 << 1, -1 },
/* PIN3   RB2  */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV,  1 << 2, -1 },
/* PIN4   RB3  */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV,  1 << 3, -1 },
/* PIN5   RB4  */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV,  1 << 4, -1 },
/* PIN6   RB8  */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV,  1 << 8, -1 },
/* PIN7   RB9  */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV,  1 << 9, -1 },
/* PIN8   RB10 */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV, 1 << 10, -1 },
/* PIN9   RB11 */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV, 1 << 11, -1 },
/* PIN10  RB12 */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV, 1 << 12, -1 },
/* PIN11  RB14 */ { &TRISBCLR, &TRISBSET, &ODCBCLR, &ODCBSET, &PORTB, &LATBCLR, &LATBSET, &LATBINV, 1 << 14, -1 },

/* PIN12  RC13 */ { &TRISCCLR, &TRISCSET, &ODCCCLR, &ODCCSET, &PORTC, &LATCCLR, &LATCSET, &LATCINV, 1 << 13, -1 },
/* PIN13  RC14 */ { &TRISCCLR, &TRISCSET, &ODCCCLR, &ODCCSET, &PORTC, &LATCCLR, &LATCSET, &LATCINV, 1 << 14, -1 },

/* PIN14  RD1  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 1, -1 },
/* PIN15  RD2  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 2, -1 },
/* PIN16  RD3  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 3, -1 },
/* PIN17  RD4  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 4, -1 },
/* PIN18  RD5  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 5, -1 },
/* PIN19  RD6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 6, -1 },
/* PIN20  RD7  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 7, -1 },
/* PIN21  RD8  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV,  1 << 8, -1 },
/* PIN22  RD11 */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 11, -1 },

/* PIN23  RE0  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 0, -1 },
/* PIN24  RE1  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 1, -1 },
/* PIN25  RE2  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 2, -1 },
/* PIN26  RE3  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 3, -1 },
/* PIN27  RE4  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 4, -1 },
/* PIN28  RE5  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 5, -1 },
/* PIN29  RE6  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 6, -1 },
/* PIN30  RE7  */ { &TRISECLR, &TRISESET, &ODCECLR, &ODCESET, &PORTE, &LATECLR, &LATESET, &LATEINV,  1 << 7, -1 },
           
/* PIN31  RF1  */ { &TRISFCLR, &TRISFSET, &ODCGCLR, &ODCFSET, &PORTF, &LATFCLR, &LATFSET, &LATFINV,  1 << 1, -1 },

/* PIN32  RG6  */ { &TRISGCLR, &TRISGSET, &ODCGCLR, &ODCGSET, &PORTG, &LATGCLR, &LATGSET, &LATGINV,  1 << 6, -1 },
/* PIN33  RG9  */ { &TRISGCLR, &TRISGSET, &ODCGCLR, &ODCGSET, &PORTG, &LATGCLR, &LATGSET, &LATGINV,  1 << 9, -1 },
};
#elif defined(HARDWARE_PIC32_USK)
#define NUM_PINS 6
static const PinInfo pinInfoTbl[NUM_PINS] = {
/* PIN1   RG6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 0, -1 },
/* PIN2   RG6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 1, -1 },
/* PIN3   RG6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 2, -1 },
/* PIN4   RG6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 6, -1 },
/* PIN5   RG6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 7, -1 },
/* PIN6   RG6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 13, -1 }
};
#else
#error Hardware no soportado
#endif


/// ----------------------------------------------------------------------
/// \brief Configura un port com a sortida digital.
/// \param pin: Numero de pin.
/// \param openDrain: True si la sortida es tipos OC.
///
void halGPIOPinSetModeOutput(
    uint8_t pin,
    bool openDrain) {
   
    const PinInfo *p = &pinInfoTbl[pin];
    *p->trisCLR = p->mask;
    
    if (openDrain)
        *p->odcSET = p->mask;
    else
        *p->odcCLR = p->mask;
    
    if (p->analog != -1) 
        AD1PCFGSET = 1 << p->analog;
}


/// ----------------------------------------------------------------------
/// \brief Configura un port com a entrada digital.
/// \param pin: Numero de pin.
///
void halGPIOPinSetModeInput(
    uint8_t pin) {

    const PinInfo *p = &pinInfoTbl[pin];
    *p->trisSET = p->mask;

    if (p->analog != -1)
        AD1PCFGSET = 1 << p->analog;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'estat d'un port digital.
/// \param pin: Numero del pin.
///
bool halGPIOPinGetState(
    uint8_t pin) {

    const PinInfo *p = &pinInfoTbl[pin];
    return (*p->port & p->mask) != 0;

}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat d'un port de sortida digital.
/// \param pin: Numero de pin.
/// \param state: El nou estat.
///
void halGPIOPinSetState(
    uint8_t pin, 
    bool state) {

    const PinInfo *p = &pinInfoTbl[pin];
    if (state)
        *p->latSET = p->mask;
    else
        *p->latCLR = p->mask;
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'un port de sortida digital.
/// \param pin: Numero de pin.
///
void halGPIOPinToggleState(
    uint8_t pin) {

    const PinInfo *p = &pinInfoTbl[pin];
    *p->latINV = p->mask;
}
