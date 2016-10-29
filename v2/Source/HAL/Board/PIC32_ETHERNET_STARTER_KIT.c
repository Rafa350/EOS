#include "xc.h"
#include "hal/halGPIO.h"


const PinInfo pinInfoTbl[] = {
/* PIN1   RD0  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 0, -1 },
/* PIN2   RD1  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 1, -1 },
/* PIN3   RD2  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 2, -1 },
/* PIN4   RD6  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 6, -1 },
/* PIN5   RD7  */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 7, -1 },
/* PIN6   RD13 */ { &TRISDCLR, &TRISDSET, &ODCDCLR, &ODCDSET, &PORTD, &LATDCLR, &LATDSET, &LATDINV, 1 << 13, -1 }
};


/// ----------------------------------------------------------------------
/// \brief Inicialitza la placa PIC32-ETHERNET-STARTER-KIT
///
void halGPIOInitializeBoard() {
    
    halGPIOInitialize(pinInfoTbl, sizeof(pinInfoTbl) / sizeof(pinInfoTbl[0]));
}
