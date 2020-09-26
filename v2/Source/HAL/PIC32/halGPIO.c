#include "eos.h"
#include "HAL/PIC32/halGPIO.h"


/// ----------------------------------------------------------------------
/// \brief    Inicialitza una llista de pins.
/// \param    info: Parametres d'inicialitzacio.
/// \param    count: Numero de pins a inicialitzar;
///
void halGPIOInitializePins(
    const GPIOInitializePinInfo* info,
    unsigned count) {

    for (unsigned i = 0; i < count; i++) {
        const GPIOInitializePinInfo* p = &info[i];
        halGPIOInitializePin(p->port, p->pin, p->options, p->alt);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Initialitza un pin individual.
/// \param    port: Identificador del port.
/// \param    pin: Identificador del pin.
/// \param    options: Opcions de configuracio.
/// \param    alt: Funcio alternativa del pin.
///
void halGPIOInitializePin(
    GPIOPort port,
    GPIOPin pin,
    GPIOOptions options,
    GPIOAlt alt) {

    halGPIOInitializePort(port, 1 << pin, options, alt);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza una llista de ports.
/// \param    info: Parametres d'inicialitzacio.
/// \param    count: Numero de ports a inicialitzar.
///
void halGPIOInitializePorts(
    const GPIOInitializePortInfo* info,
    unsigned count) {

    for (unsigned i = 0; i < count; i++) {
        const GPIOInitializePortInfo* p = &info[i];
        halGPIOInitializePort(p->port, p->mask, p->options, p->alt);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Configura un port.
/// \param    port: Identificador del port.
/// \param    mask: Mascara de pins.
/// \param    options: Opcions de configuracio.
/// \param    alt: Funcio alternativa dels pins.
///
void halGPIOInitializePort(
    GPIOPort port,
    GPIOMask mask,
    GPIOOptions options,
    GPIOAlt alt) {
    
    GPIORegisters* gpio = halGPIOGetRegisterPtr(port);
       
    if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
        ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)) {

        // Selecciona el valor inicial del port
        //
        switch (options & HAL_GPIO_INIT_mask) {
            case HAL_GPIO_INIT_SET:
                gpio->LATxSET = mask;
                break;

            case HAL_GPIO_INIT_CLR:
                gpio->LATxCLR = mask;
                break;
        }

        // El configura com sortida
        //
        gpio->TRISxCLR = mask;

        // Configura com OPEN-DRAIN o PUSH-PULL
        //
        if ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)
            gpio->ODCxSET = mask;
        else
            gpio->ODCxCLR = mask;
    }

    else if ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_INPUT) {

        // El configura com entrada
        //
        gpio->TRISxSET = mask;
    }
}
