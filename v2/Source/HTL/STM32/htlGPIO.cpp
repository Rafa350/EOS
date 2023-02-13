#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Selecciona el driver de sortida.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
/// \param    driver: El driver a seleccionar.
///
static void setDriver(
	GPIO_TypeDef *regs,
	uint32_t pn,
	GPIODriver driver) {

    // Configura el registre OTYPER (Output Type Register)
    //
	if (driver != GPIODriver::noChange) {
		uint32_t tmp = regs->OTYPER;
		tmp &= ~(1 << pn);
		if (driver == GPIODriver::openDrain)
			tmp |= 1 << pn;
		regs->OTYPER = tmp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la velocitat de sortida.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
/// \param    speed: La velocitat a seleccionar.
///
static void setSpeed(
	GPIO_TypeDef *regs,
	uint32_t pn,
	GPIOSpeed speed) {

	if (speed != GPIOSpeed::noChange) {

		uint32_t value = 1; // Per defecte medium

		switch (speed) {
			case GPIOSpeed::low:
				value = 0;
				break;

			case GPIOSpeed::high:
				value = 2;
				break;

			case GPIOSpeed::fast:
				value = 3;
				break;

			default:
				break;
		}

		// Configura el registre OSPEEDR (Output Speed Register)
		//
		uint32_t tmp = regs->OSPEEDR;
		tmp &= ~(0b11 << (pn * 2));
		tmp |= value << (pn * 2);
		regs->OSPEEDR = tmp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la opcio pull.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
/// \param    pull: El pull a seleccionar.
///
static void setPull(
	GPIO_TypeDef *regs,
	uint32_t pn,
	GPIOPull pull) {

	if (pull != GPIOPull::noChange) {

		uint32_t value = 0; // Per defecte sense PU/PD

		switch (pull) {
			case GPIOPull::down:
				value = 2;
				break;

			case GPIOPull::up:
				value = 1;
				break;

			default:
				break;
		}

		// Configura el registre PUPDR (Pull Up/Down Register)
		//
		uint32_t tmp = regs->PUPDR;
		tmp &= ~(0b11 << (pn * 2));
		tmp |= value << (pn * 2);
		regs->PUPDR = tmp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la funcio alternariva del pin.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
/// \param    alt: Identificador de la funcio alternativa.
///
static void setAlt(
	GPIO_TypeDef *regs,
	uint32_t pn,
	GPIOAlt alt) {

    // Configura el registre AFR (Alternate Funcion Register)
    //
    uint32_t tmp = regs->AFR[pn >> 3];
    tmp &= ~(0b1111 << ((pn & 0x07) * 4)) ;
    tmp |= (uint32_t(alt) & 0b1111) << ((pn & 0x07) * 4);
    regs->AFR[pn >> 3] = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a entrada.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    pull: Opcions pull up/down.
///
void GPIOBase_x::initInput(
    GPIO_TypeDef *regs,
    uint32_t pn,
    GPIOPull pull) {

    // Configura el registre MODER (Mode Register)
    //
    uint32_t tmp = regs->MODER;
    tmp &= ~(0b11 << (pn * 2));
    regs->MODER = tmp;

    setPull(regs, pn, pull);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a sortida.
/// \param    reg: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    driver: Opcions del driver.
/// \param    speed: Opcions de velocitat.

void GPIOBase_x::initOutput(
    GPIO_TypeDef *regs,
    uint32_t pn,
    GPIODriver driver,
    GPIOSpeed speed) {

    // Configura el registre MODER (Mode Register)
    //
    uint32_t tmp = regs->MODER;
    tmp &= ~(0b11 << (pn * 2));
    tmp |= 0b01 << (pn * 2);
    regs->MODER = tmp;

    setDriver(regs, pn, driver);
    setSpeed(regs, pn, speed);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a sortida alternativa.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    driver: Opcions del driver de sortida.
/// \param    speed: Opcions de velocitat.
/// \param    alt: Funcio alternativa.
///
void GPIOBase_x::initAlt(
    GPIO_TypeDef *regs,
    uint32_t pn,
    GPIODriver driver,
    GPIOSpeed speed,
    GPIOAlt alt) {
        
    // Configura el registre MODER (Mode Register)
    //
    uint32_t tmp = regs->MODER;
    tmp &= ~(0b11 << (pn * 2));
    tmp |= 0b10 << (pn * 2);
    regs->MODER = tmp;

    setDriver(regs, pn, driver);
    setSpeed(regs, pn, speed);
    setAlt(regs, pn, alt);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a entrada/sortida analogica.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
///
void GPIOBase_x::initAnalogic(
	GPIO_TypeDef *regs,
	uint32_t pn) {

    // Configura el registre MODER (Mode Register)
    //
    uint32_t tmp = regs->MODER;
    tmp &= ~(0b11 << (pn * 2));
    tmp |= 0b11 << (pn * 2);
    regs->MODER = tmp;
}
