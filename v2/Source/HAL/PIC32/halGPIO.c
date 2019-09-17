#include "eos.h"
#include "HAL/PIC32/halGPIO.h"


const GPIOPortRegs gpioPortRegs[] = {
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
/// \brief Inicialitza una llista de pins.
/// \param[in] pInfo: Parametres d'inicialitzacio.
/// \param[in] count: Numero de pins a inicialitzar;
///
void halGPIOInitializePins(
    const GPIOInitializePinInfo *pInfo, 
    unsigned count) {
    
    for (unsigned i = 0; i < count; i++) {
        const GPIOInitializePinInfo *p = &pInfo[i];
        halGPIOInitializePin(p->port, p->pin, p->options, p->alt);
    }
}


/// ----------------------------------------------------------------------
/// \brief Initialitza un pin individual.
/// \param[in] port: Identificador del port.
/// \param[in] pin: Identificador del pin.
/// \param[in] options: Opcions de configuracio.
/// \param[in] alt: Funcio alternativa del pin.
///
void halGPIOInitializePin(
    GPIOPort port, 
    GPIOPin pin, 
    GPIOOptions options, 
    GPIOAlt alt) {
   
    halGPIOInitializePort(port, 1 << pin, options, alt);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza una llista de ports.
/// \param[in] pInfo: Parametres d'inicialitzacio.
/// \param[in] count: Numero de ports a inicialitzar.
///
void halGPIOInitializePorts(
    const GPIOInitializePortInfo *pInfo,
    unsigned count) {
    
    for (unsigned i = 0; i < count; i++) {
        const GPIOInitializePortInfo *p = &pInfo[i];
        halGPIOInitializePort(p->port, p->mask, p->options, p->alt);
    }
}


/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param[in] port: Identificador del port.
/// \param[in] mask: Mascara de pins.
/// \param[in] options: Opcions de configuracio.
/// \param[in] alt: Funcio alternativa dels pins.
///
void halGPIOInitializePort(
    GPIOPort port,
    GPIOMask mask,
    GPIOOptions options,
    GPIOAlt alt) {
    
    if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
        ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)) {
        
        // Selecciona el valor inicial del port
        //
        switch (options & HAL_GPIO_INIT_mask) {
            case HAL_GPIO_INIT_SET:
                *gpioPortRegs[port].latSET = mask;
                break;
                
            case HAL_GPIO_INIT_CLR:
                *gpioPortRegs[port].latCLR = mask;
                break;
        }

        // El configura com sortida
        //
        *gpioPortRegs[port].trisCLR = mask; 
     
        // Configura com OPEN-DRAIN o PUSH-PULL
        //
        if ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)
            *gpioPortRegs[port].odcSET = mask;
        else
            *gpioPortRegs[port].odcCLR = mask;        
    }  
    
    else if ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_INPUT) {
       
        // El configura com entrada
        //
        *gpioPortRegs[port].trisSET = mask;
    }
}
