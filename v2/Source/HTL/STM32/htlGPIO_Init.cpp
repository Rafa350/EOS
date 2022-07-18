#include "eos.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a entrada.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    pull: Opcions pull up/down.
///
void GPIO_initInput(
    GPIO_TypeDefs *regs,
    unsigned pn,
    unsigned pull) {

    uint32_t temp;

    // Configura el registre MODER (Mode Register)
    //
    temp = regs->MODER;
    temp &= ~(0b11 << (pn * 2));
    regs->MODER = temp;

    // Configura el registre PUPDR (Pull Up/Down Register)
    //
    temp = regs->PUPDR;
    temp &= ~(0b11 << (pn * 2));
    temp |= (pull & 0x11) << (pn * 2);
    regs->PUPDR = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a sortida.
/// \param    reg: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    driver: Opcions del driver.
/// \param    speed: Opcions de velocitat.

void GPIO_initOutput(
    GPIO_TypeDefs *regs,
    unsigned pn,
    unsigned driver,
    unsigned speed) {

    uint32_t temp;

    // Configura el registre MODER (Mode Register)
    //
    temp = regs->MODER;
    temp &= ~(0b11 << (pn * 2));
    temp |= 0b01 << (pn * 2);
    regs->MODER = temp;

    // Configura el registre OTYPER (Output Type Register)
    //
    temp = regs->OTYPER;
    temp &= ~(0b1 << pn);
    temp |= (driver & 0b1) << pn;
    regs->OTYPER = temp;

    // Configura el registre OSPEEDR (Output Speed Register)
    //
    temp = regs->OSPEEDR;
    temp &= ~(0b11 << (pn * 2));
    temp |= (speed & 0b11) << (pn * 2);
    regs->OSPEEDR = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a sortida alternativa.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    driver: Opcions del driver de sortida.
/// \param    speed: Opcions de velocitat.
/// \param    alt: Funcio alternativa.
///
void GPIO_initAlt(
    GPIO_TypeDefs *regs,
    unsigned pn,
    unsigned driver,
    unsigned speed,
    unsigned alt) {
        
    uint32_t temp;

    // Configura el registre MODER (Mode Register)
    //
    temp = regs->MODER;
    temp &= ~(0b11 << (pn * 2));
    temp |= 0b10 << (pn * 2);
    regs->MODER = temp;

    // Configura el registre OTYPER (Output Type Register)
    //
    temp = regs->OTYPER;
    temp &= ~(0b1 << pn);
    temp |= (driver & 0b1) << pn;
    regs->OTYPER = temp;

    // Configura el registre OSPEEDR (Output Speed Register)
    //
    temp = regs->OSPEEDR;
    temp &= ~(0b11 << (pn * 2));
    temp |= (speed & 0b11) << (pn * 2);
    regs->OSPEEDR = temp;

    // Configura el registre AFR (Alternate Funcion Register)
    //
    temp = regs->AFR[pn >> 3];
    temp &= ~(0b1111 << ((pn & 0x07) * 4)) ;
    temp |= (alt & 0b1111) << ((pn & 0x07) * 4);
    regs->AFR[pn >> 3] = temp;
}