#include "HAL/PIC32/halGPIO.h"
#include <xc.h>


GPIOPortRegs gpioPortRegs[] = {
#if defined(PORTA)
    { &TRISASET, &TRISACLR, &ODCASET, &ODCACLR, &LATASET, &LATACLR, &LATAINV, &LATA, &PORTA}, 
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
/// \param info: Parametres d'inicialitzacio.
///
void halGPIOInitializePin(
    const GPIOInitializePinInfo *info) {
   
    uint16_t mask = 1 << info->pin;
    
    if (((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_PP) ||
        ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD)) {
        
        if ((info->options & HAL_GPIO_INIT_MASK) == HAL_GPIO_INIT_SET)
            *gpioPortRegs[info->port].latSET = mask;
        else
            *gpioPortRegs[info->port].latCLR = mask;

        *gpioPortRegs[info->port].trisCLR = mask; 
     
        if ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD)
            *gpioPortRegs[info->port].odcSET = mask;
        else
            *gpioPortRegs[info->port].odcCLR = mask;        
    }  
    
    else if ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_INPUT) {
       
        *gpioPortRegs[info->port].trisSET = mask;
    }
}


/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param port: Parametres d'inicialitzacio
///
void halGPIOInitializePort(
    const GPIOInitializePortInfo *info) {
        
    if (((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_PP) ||
        ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD)) {

        if ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD) 
            *gpioPortRegs[info->port].odcSET = info->mask;        
        else
            *gpioPortRegs[info->port].odcCLR = info->mask;                     
        
        *gpioPortRegs[info->port].trisCLR = info->mask;
    }
    
    else if ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_INPUT) {
        
        *gpioPortRegs[info->port].trisSET = info->mask;
    }
}


void halGPIOInitialize(
    uint8_t port, 
    uint8_t pin, 
    uint32_t options, 
    uint8_t alt) {
    
    GPIOInitializePinInfo info;
    info.port = port;
    info.pin = pin;
    info.options = options;
    info.alt = alt;
    
    halGPIOInitializePin(&info);
}