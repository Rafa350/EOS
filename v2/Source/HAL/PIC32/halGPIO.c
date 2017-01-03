#include "hal/halGPIO.h"

#include <xc.h>


GPIOPortRegs gpioPortRegs[] = {
#if defined(PORTA)
    { &TRISASET, &TRISACLR, &ODCASET, &ODCACLR, ,&LATASET, &LATACLR, &LATAINV, &LATA, &PORTA}, 
#else
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#endif    
#if defined(PORTB)
    { &TRISBSET, &TRISBCLR, &ODCBSET, &ODCBCLR, &LATBSET, &LATBCLR, &LATBINV, &LATB, &PORTB}, 
#else
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#endif    
#if defined(PORTC)
    { &TRISCSET, &TRISCCLR, &ODCCSET, &ODCCCLR, &LATCSET, &LATCCLR, &LATCINV, &LATC, &PORTC}, 
#else
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#endif    
#if defined(PORTD)
    { &TRISDSET, &TRISDCLR, &ODCDSET, &ODCDCLR, &LATDSET, &LATDCLR, &LATDINV, &LATD, &PORTD}, 
#else
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#endif    
#if defined(PORTE)
    { &TRISESET, &TRISECLR, &ODCESET, &ODCECLR, &LATESET, &LATECLR, &LATEINV, &LATE, &PORTE}, 
#else
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#endif    
#if defined(PORTF)
    { &TRISFSET, &TRISFCLR, &ODCFSET, &ODCFCLR, &LATFSET, &LATFCLR, &LATFINV, &LATF, &PORTF}, 
#else
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#endif    
#if defined(PORTG)
    { &TRISGSET, &TRISGCLR, &ODCGSET, &ODCGCLR, &LATGSET, &LATGCLR, &LATGINV, &LATG, &PORTG}, 
#else
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
#endif    
};



/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param options: Opcions
///
void halGPIOInitializePin(
    GPIOPort port,
    GPIOPin pin,
    GPIOOptions options) {
   
    if (options & HAL_GPIO_DIRECTION_OUTPUT)
        *gpioPortRegs[port].trisCLR = 1 << pin;
    else 
        *gpioPortRegs[port].trisSET = 1 << pin;
    
    if (options & HAL_GPIO_OPENDRAIN_ENABLED)
        *gpioPortRegs[port].odcSET = 1 << pin;
    else
        *gpioPortRegs[port].odcCLR = 1 << pin;        
}


/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param port: Identificador del port.
/// \param options: Opcions
/// \param mask: Mascara.
///
void halGPIOInitializePort(
    GPIOPort port,
    GPIOOptions options,
    uint16_t mask) {

    if (options & HAL_GPIO_DIRECTION_OUTPUT)
        *gpioPortRegs[port].trisCLR = mask;
    else
        *gpioPortRegs[port].trisSET = mask;

    if (options & HAL_GPIO_OPENDRAIN_ENABLED)
        *gpioPortRegs[port].odcSET = mask;        
    else
        *gpioPortRegs[port].odcCLR = mask;             
}
