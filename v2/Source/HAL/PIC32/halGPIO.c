#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halGPIO.h"


/// ----------------------------------------------------------------------
/// \brief    Inicialitza una llista de pins.
/// \param    info: Parametres d'inicialitzacio.
/// \param    count: Numero de pins a inicialitzar;
///
void halGPIOInitializePins(
    const halGPIOPinSettings *settings,
    int count) {

    for (int i = 0; i < count; i++) {
        const halGPIOPinSettings *p = &settings[i];
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
    halGPIOPort port,
    halGPIOPin pin,
    halGPIOOptions options,
    halGPIOAlt alt) {

    halGPIOInitializePort(port, 1 << pin, options, alt);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza una llista de ports.
/// \param    info: Parametres d'inicialitzacio.
/// \param    count: Numero de ports a inicialitzar.
///
void halGPIOInitializePorts(
    const halGPIOPortSettings *settings,
    int count) {

    for (int i = 0; i < count; i++) {
        const halGPIOPortSettings *p = &settings[i];
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
    halGPIOPort port,
    halGPIOMask mask,
    halGPIOOptions options,
    halGPIOAlt alt) {

    halGPIORegisters* regs = (halGPIORegisters*) port;

    if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
        ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)) {

        // Selecciona el valor inicial del port
        //
        switch (options & HAL_GPIO_INIT_mask) {
            case HAL_GPIO_INIT_SET:
                regs->LATxSET = mask;
                break;

            case HAL_GPIO_INIT_CLR:
                regs->LATxCLR = mask;
                break;
        }

        // El configura com sortida
        //
        regs->TRISxCLR = mask;

        // Configura com OPEN-DRAIN o PUSH-PULL
        //
        if ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)
            regs->ODCxSET = mask;
        else
            regs->ODCxCLR = mask;
    }

    else if ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_INPUT) {

        // El configura com entrada
        //
        regs->TRISxSET = mask;
    }
}
